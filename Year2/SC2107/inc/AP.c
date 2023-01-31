// AP.c
// Runs on either MSP432 or TM4C123
// see GPIO.c file for hardware connections 
// Student version, 
// The CC2650 is running with SimpleNP 2.2 (Powersave, MRDY, SRDY signals). 
// Tested with CC2650 BoosterPack
//    cc2650bp_simple_np_uart_pm_xsbl_mooc_custom.hex
//    simple_np_cc2650bp_uart_pm_sbl.hex
// Tested with CC2650 LaunchPad
//    cc2650lp_simple_np_uart_pm_xsbl_mooc_custom.hex 
//    simple_np_cc2650lp_uart_pm_sbl.hex
// It doesn't matter if bootloadmode is enabled (sbl) or not enabled (xsbl)
// Transmit and receive interrupts are implemented in UART1.c on UCA2.
// GPIO pins are implemented in GPIO.c
// Daniel Valvano and Jonathan Valvano
// February 28, 2017

/* This example accompanies the books
   "Embedded Systems: Introduction to the MSP432 Microcontroller",
       ISBN: 978-1512185676, Jonathan Valvano, copyright (c) 2017
   "Embedded Systems: Real-Time Interfacing to the MSP432 Microcontroller",
       ISBN: 978-1514676585, Jonathan Valvano, copyright (c) 2017
   "Embedded Systems: Real-Time Operating Systems for ARM Cortex-M Microcontrollers",
       ISBN: 978-1466468863, , Jonathan Valvano, copyright (c) 2017
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/

Simplified BSD License (FreeBSD License)
Copyright (c) 2017, Jonathan Valvano, All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are
those of the authors and should not be interpreted as representing official
policies, either expressed or implied, of the FreeBSD Project.
*/

// CC2650 booster or CC2650 LaunchPad, CC2650 needs to be running SimpleNP 2.2 (POWERSAVE)
// UART serial from CC2650 to TM4C123/MSP432 
// UART serial from TM4C123/MSP432 to CC2650
// MRDY, an output from TM4C123/MSP432 and an input to CC2650
// SRDY, an input to TM4C123/MSP432 and an output from CC2650
// Reset, an output from TM4C123/MSP432 to hardware reset to CC2650
// MRDY is a GPIO pin whose logic level indicates the state of the master processor. 
// MRDY is an active low (low true) signal. 
// An MRDY event indicates that the master processor is ready to send or receive data.
// SRDY is a GPIO pin whose logic level indicates the state of the slave processor. 
// SRDY is an active low (low true) signal. 
// An SRDY event indicates that the slave processor is ready to send or receive data. 
// see GPIO.c file for hardware connections 

#include <stdint.h>
#include "../inc/CortexM.h"
#include "../inc/UART0.h"
#include "../inc/UART1.h"
#include "../inc/AP.h"
#include "../inc/Clock.h"
#include "msp.h"
#include "../inc/GPIO.h"


#define RECVSIZE 128
uint8_t RecvBuf[RECVSIZE];

uint32_t fcserr;      // debugging counts of errors
uint32_t TimeOutErr;  // debugging counts of no response errors
uint32_t NoSOFErr;    // debugging counts of no SOF errors

#define APTIMEOUT 40000   // 10 ms
/* If you define APDEBUG then all LP-SNP traffic is displayed on UART0.
   If you do not define APDEBUG then no UART0 output is performed, and thus it runs faster.
 */
#define APDEBUG 1
//**debug macros**********
#ifdef APDEBUG
#define OutString(STRING) UART0_OutString(STRING)
#define OutUHex(NUM) UART0_OutUHex(NUM)
#define OutUHex2(NUM) UART0_OutUHex2(NUM)
#define OutChar(N) UART0_OutChar(N)
#else
#define OutString(STRING)
#define OutUHex(NUM)
#define OutUHex2(NUM)
#define OutChar(N)
#endif

//------------AP_Reset------------
// reset the Bluetooth module
// with MRDY high, clear RESET low for 10 ms
// Input: none
// Output: none
void AP_Reset(void){
  ClearReset();   // RESET=0    
  SetMRDY();      // MRDY=1  
  Clock_Delay1ms(10);
  SetReset();     // RESET=1  
}
//*************message and message fragments**********
const uint8_t HCI_EXT_ResetSystemCmd[] = {SOF,0x03,0x00,0x55,0x04,0x1D,0xFC,0x01,0xB2};
const uint8_t NPI_GetStatus[] =   {SOF,0x00,0x00,0x55,0x06,0x53};
const uint8_t NPI_GetVersion[] =  {SOF,0x00,0x00,0x35,0x03,0x36};
uint8_t NPI_AddService[] = {
  SOF,3,0x00,     // length = 3
  0x35,0x81,      // SNP Add Service
  0x01,           // Primary Service
  0xF0,0xFF,
  0xB9};          // FCS (calculated by AP_SendMessageResponse)

const uint8_t NPI_Register[] = {   
  SOF,0x00,0x00,  // length = 0
  0x35,0x84,      // SNP Register Service
  0x00};          // FCS (calculated by AP_SendMessageResponse)

// call Set Advertisement twice 0, 2
const uint8_t NPI_SetAdvertisement1[] = {   
  SOF,11,0x00,    // length = 11
  0x55,0x43,      // SNP Set Advertisement Data
  0x01,           // Not connected Advertisement Data
  0x02,0x01,0x06, // GAP_ADTYPE_FLAGS,DISCOVERABLE | no BREDR
  0x06,0xFF,      // length, manufacturer specific
  0x0D ,0x00,     // Texas Instruments Company ID
  0x03,           // TI_ST_DEVICE_ID
  0x00,           // TI_ST_KEY_DATA_ID
  0x00,           // Key state
  0xEE};          // FCS (calculated by AP_SendMessageResponse)


const uint8_t NPI_SetAdvertisementSAP[] = {   
  SOF,31,0x00,    // length = 31
  0x55,0x43,      // SNP Set Advertisement Data
  0x00,           // Scan Response Data
  20,0x09,        // length, type=LOCAL_NAME_COMPLETE
  'S','h','a','p','e',' ','t','h','e',' ','W','o','r','l','d',' ','S','A','P',
// connection interval range
  0x05,           // length of this data
  0x12,           // GAP_ADTYPE_SLAVE_CONN_INTERVAL_RANGE
  0x50,0x00,      // DEFAULT_DESIRED_MIN_CONN_INTERVAL
  0x20,0x03,      // DEFAULT_DESIRED_MAX_CONN_INTERVAL
// Tx power level
  0x02,           // length of this data
  0x0A,           // GAP_ADTYPE_POWER_LEVEL
  0x00,           // 0dBm
  0x77};          // FCS (calculated by AP_SendMessageResponse)

uint8_t NPI_GATTSetDeviceName[] = {   
  SOF,22,0x00,    // length = 22
  0x35,0x8C,      // SNP Set GATT Parameter (0x8C)
  0x01,           // Generic Access Service
  0x00,0x00,      // Device Name
  'S','h','a','p','e',' ','t','h','e',' ','W','o','r','l','d',' ','0','0','1',
  0x77};          // FCS (calculated by AP_SendMessageResponse)
uint8_t NPI_GATTSetDeviceNameJacki[] = {
// students need to write this as part of Lab 19
};          // FCS (calculated by AP_SendMessageResponse)
uint8_t NPI_SetAdvertisementData[] = {   
  SOF,31,0x00,    // length = 31
  0x55,0x43,      // SNP Set Advertisement Data
  0x00,           // Scan Response Data
  20,0x09,        // length, type=LOCAL_NAME_COMPLETE
  'S','h','a','p','e',' ','t','h','e',' ','W','o','r','l','d',' ','0','0','1',
// connection interval range
  0x05,           // length of this data
  0x12,           // GAP_ADTYPE_SLAVE_CONN_INTERVAL_RANGE
  0x50,0x00,      // DEFAULT_DESIRED_MIN_CONN_INTERVAL
  0x20,0x03,      // DEFAULT_DESIRED_MAX_CONN_INTERVAL
// Tx power level
  0x02,           // length of this data
  0x0A,           // GAP_ADTYPE_POWER_LEVEL
  0x00,           // 0dBm
  0x77};          // FCS (calculated by AP_SendMessageResponse)

uint8_t NPI_SetAdvertisementDataJacki[] = {
// students need to write this as part of Lab 19
};          // FCS (calculated by AP_SendMessageResponse)

const uint8_t NPI_StartAdvertisement[] = {   
  SOF,14,0x00,    // length = 14
  0x55,0x42,      // SNP Start Advertisement
  0x00,           // Connectable Undirected Advertisements
  0x00,0x00,      // Advertise infinitely.
  0x64,0x00,      // Advertising Interval (100 * 0.625 ms=62.5ms)
  0x00,           // Filter Policy RFU
  0x00,           // Initiator Address Type RFU
  0x00,0x01,0x00,0x00,0x00,0xC5, // RFU
  0x02,           // Advertising will restart with connectable advertising when a connection is terminated
  0xBB};          // FCS (calculated by AP_SendMessageResponse)
uint8_t NPI_ReadConfirmation[] = {   
  SOF,0x08,0x00,  // length = 8 (7+data length, filled in dynamically)
  0x55,0x87,      // SNP Characteristic Read Confirmation (0x87)
  0x00,           // Success
  0x00,0x00,      // handle of connection always 0
  0x00,0x00,      // Handle of the characteristic value attribute being read (filled in dynamically
  0x00,0x00,      // offset, ignored, assumes small chucks of data
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // actual data (filled in dynamically)
  0x00};          // FCS (calculated by AP_SendMessageResponse)
uint8_t NPI_WriteConfirmation[] = {   
  SOF,0x03,0x00,  // length = 3
  0x55,0x88,      // SNP Characteristic Write Confirmation
  0x00,           // Success
  0x00,0x00,      // handle of connection always 0
  0xDE};          // FCS (calculated by AP_SendMessageResponse)
uint8_t NPI_CCCDUpdatedConfirmation[] = {   
  SOF,0x03,0x00,  // length = 3
  0x55,0x8B,      // SNP CCCD Updated Confirmation (0x8B)
  0x00,           // Success
  0x00,0x00,      // handle of connection always 0
  0xDD};          // FCS (calculated by AP_SendMessageResponse)
uint8_t NPI_SendNotificationIndication[] = {   
  SOF,0x07,0x00,  // length = 7 to 14 depending on data size
  0x55,0x89,      // SNP Send Notification Indication (0x89))
  0x00,0x00,      // handle of connection always 0
  0x00,0x00,      // Handle of the characteristic value attribute to notify / indicate (filled in dynamically
  0x00,           // RFU
  0x01,           // Indication Request type
  0x00,0,0,0,0,0,0,0, // 1 to 8 bytes of data filled in dynamically
  0xDD};      // FCS (calculated by AP_SendMessageResponse)

uint8_t NPI_AddCharValue[] = {   
  SOF,0x08,0x00,  // length = 8
  0x35,0x82,      // SNP Add Characteristic Value Declaration
  0x03,           // 0=none,1=read,2=write, 3=Read+write, GATT Permission
  0x0A,0x00,      // 2=read,8=write,0x0A=read+write,0x10=notify, GATT Properties
  0x00,           // RFU
  0x00,0x02,      // Maximum length of the attribute value=512
  0xF1,0xFF,      // UUID
  0xBA};          // FCS (calculated by AP_SendMessageResponse)
uint8_t NPI_AddCharDescriptor[] = {   
  SOF,0x17,0x00,  // length determined at run time 6+string length
  0x35,0x83,      // SNP Add Characteristic Descriptor Declaration
  0x80,           // User Description String
  0x01,           // GATT Read Permissions
  0x11,0x00,      // Maximum Possible length of the user description string
  0x11,0x00,      // Initial length of the user description string
  'C','h','a','r','a','c','t','e','r','i','s','t','i','c',' ','0',0, // Initial user description string
  0x0C,0,0,0};    // FCS (calculated by AP_SendMessageResponse)

//------------AP_Init------------
// Initialize serial link and GPIO to Bluetooth module
// see GPIO.c file for hardware connections 
// reset the Bluetooth module and initialize connection
// Input: none
// Output: APOK on success, APFAIL on timeout
int AP_Init(void){int bwaiting;   int count = 0;
  GPIO_Init(); // MRDY, SRDY, reset
#ifdef APDEBUG
  if(UCA0CTLW0 != 0x00C0){
    UART0_Init(); // if not on, enable
  }
  UART0_OutString("\n\rReset CC2650");
#endif
  UART1_Init();
  fcserr = 0;     // number of packets with FCS errors
  TimeOutErr = 0; // debugging counts of no response error
  NoSOFErr =0 ;   // debugging counts of no SOF error
  bwaiting = 1; // waiting for reset
  while(bwaiting){
    AP_Reset();
    count = 0;  // should get SNP power up within 30 ms (duration is arbitrary and 'count' value is uncalibrated)
    while(count < 600000){
      if(AP_RecvStatus()){
        AP_RecvMessage(RecvBuf,RECVSIZE);
        if((RecvBuf[3]==0x55)&&(RecvBuf[4]==0x01)){
          count = 600000;
          bwaiting = 0; // success
        }
      }
      count = count + 1;
    }
  } 
  AP_SendMessageResponse((uint8_t*)HCI_EXT_ResetSystemCmd,RecvBuf,RECVSIZE); 
  count = 0;  // should get SNP power up within 120 ms (duration is arbitrary and 'count' value is uncalibrated)
  bwaiting = 1; // waiting for SNP power up
  while(count < 6000000){
    if(AP_RecvStatus()){
      AP_RecvMessage(RecvBuf,RECVSIZE);
      if((RecvBuf[3]==0x55)&&(RecvBuf[4]==0x01)){
        count = 6000000;
        bwaiting = 0; // success
      }
    }
    count = count + 1;
  } 
  if(bwaiting){
    TimeOutErr++;  // no response error
    return APFAIL;
  }  
  return APOK;
}
//***********AP_GetSize***************
// returns the size of an NPI message
// Inputs:  pointer to NPI message
// Outputs: size of the message
// extracted little Endian from byte 1 and byte 2
uint32_t AP_GetSize(uint8_t *pt){
  uint8_t msb,lsb;
  uint32_t size;
  lsb = (uint8_t)pt[1];
  msb = (uint8_t)pt[2];
  size = (msb<<8)+lsb;
  return size;
}

#ifdef APDEBUG
// *****AP_EchoSendMessage**************
// For debugging, sends message to UART0
// Inputs:  pointer to message 
// Outputs: none
void AP_EchoSendMessage(uint8_t *sendMsg){ int i;uint32_t fcs;
  uint32_t size=AP_GetSize(sendMsg);
  fcs = 0;
  for(i=1;i<size+5;i++)fcs = fcs^sendMsg[i];
  OutString("\n\rLP->SNP ");
  for(i=0; i<=(4+size); i++){ 
    OutUHex2(sendMsg[i]); OutChar(',');
  }
  OutUHex2(fcs); //  FCS, calculated and not in messsage
}
// *****AP_EchoReceived**************
// for debugging, sends RecvBuf from SNP to UART0
// Inputs:  result APOK or APFAIL
// Outputs: none
void AP_EchoReceived(int response){ uint32_t size; int i;
  if(response==APOK){
    OutString("\n\rSNP->LP ");
    size = AP_GetSize(RecvBuf);
    for(i=0; i<=(4+size); i++){ 
      OutUHex2(RecvBuf[i]); OutChar(',');
    }
    OutUHex2(RecvBuf[i]); // FCS
  }else{
    OutString("\n\rfrom SNP fail");
  }
}
#else
#define AP_EchoSendMessage(MESSAGE)
#define AP_EchoReceived(R)
#endif
//------------AP_SendMessage------------
// sends a message to the Bluetooth module
// calculates/sends FCS at end 
// FCS is the 8-bit EOR of all bytes except SOF and FCS itself
// 1) Send NPI package (it will calculate fcs)
// 2) Wait for entire message to be sent
// Input: pointer to NPI encoded array
// Output: APOK on success, APFAIL on timeout
int AP_SendMessage(uint8_t *pt){
  uint8_t fcs; uint32_t waitCount; uint8_t data; uint32_t size;
// 1) Make MRDY=0
  ClearMRDY();
// 2) wait for SRDY to be low
  waitCount = 0;
  while(ReadSRDY()){
    waitCount++;
    if(waitCount>APTIMEOUT){
      TimeOutErr++;  // no response error
      return APFAIL; // timeout??
    } 
  }
// 3) Send NPI package
  size = AP_GetSize(pt);
  fcs=0;
  UART1_OutChar(SOF); pt++;
  data=*pt; UART1_OutChar(data); fcs=fcs^data; pt++;   // LSB length
  data=*pt; UART1_OutChar(data); fcs=fcs^data; pt++;   // MSB length
  data=*pt; UART1_OutChar(data); fcs=fcs^data; pt++;   // CMD0
  data=*pt; UART1_OutChar(data); fcs=fcs^data; pt++;   // CMD1
  for(int i=0;i<size;i++){
    data=*pt; UART1_OutChar(data); fcs=fcs^data; pt++; // payload
  }
  UART1_OutChar(fcs);                                  // FCS
  
// 4) Wait for entire message to be sent
  UART1_FinishOutput();
// 5) Make MRDY=1
  SetMRDY();        //   MRDY=1  
// 6) wait for SRDY to be high
  waitCount = 0;
  while(ReadSRDY()==0){
    waitCount++;
    if(waitCount>APTIMEOUT){
      TimeOutErr++;  // no response error
      return APFAIL; // timeout??
    } 
  }
  return APOK;
}


  
//------------AP_RecvMessage------------
// receive a message from the Bluetooth module
// 1) receive NPI package
// 2) Wait for entire message to be received
// Input: pointer to empty buffer into which data is returned
//        maximum size (discard data beyond this limit)
// Output: APOK if ok, APFAIL on error (timeout or fcs error)
int AP_RecvMessage(uint8_t *pt, uint32_t max){
  uint8_t fcs; uint32_t waitCount; uint8_t data,cmd0,cmd1; 
  uint8_t msb,lsb;
  uint32_t size,count,SOFcount=10;
// 1) wait for SRDY to be low
  waitCount = 0;
  while(ReadSRDY()){
    waitCount++;
    if(waitCount>APTIMEOUT){
      TimeOutErr++;  // no response error
      return APFAIL; // timeout??
    }      
  }
// 2) Make MRDY=0
  ClearMRDY();
// 3) receive NPI package
  // wait for SOF
  do{
    data = UART1_InChar();
    SOFcount--;
    if(SOFcount==0){
      SetMRDY();     //   MRDY=1  
      NoSOFErr++;    // no SOF error
      return APFAIL;
    }
  }while(data != SOF);
  *pt = data; pt++;
  fcs = 0;
// get size, once we get SOF, it is highly likely for the rest to come
  lsb = UART1_InChar(); *pt = lsb; fcs=fcs^lsb; pt++;
  msb = UART1_InChar(); *pt = msb; fcs=fcs^msb; pt++;
// get command
  cmd0 = UART1_InChar(); *pt = cmd0; fcs=fcs^cmd0; pt++;
  cmd1 = UART1_InChar(); *pt = cmd1; fcs=fcs^cmd1; pt++;
  count = 5;
  size = (msb<<8)+lsb;
// get payload
  for(int i=0;i<size;i++){
    data = UART1_InChar(); 
    fcs = fcs^data; 
    count++;
    if(count <= max){
      *pt = data; 
      pt++; // payload
    }
  }
// get FCB
  data = UART1_InChar(); 
  count++;
  if(count <= max){
    *pt = data; 
  }    
  if(data != fcs){ 
    fcserr++;
    SetMRDY();        //   MRDY=1  
    return APFAIL;
  }
// 4) Make MRDY=1
  SetMRDY();        //   MRDY=1  
// 5) wait for SRDY to be high
  waitCount = 0;
  while(ReadSRDY()==0){
    waitCount++;
  }
  return APOK;
}

//------------AP_RecvStatus------------
// check to see if Bluetooth module wishes to send packet
// Inputs: none
// Outputs: 0 if no communication needed, 
//          nonzero for communication ready 
uint32_t AP_RecvStatus(void){
  return (ReadSRDY()==0);
}

//------------AP_SendMessageResponse------------
// send a message to the Bluetooth module
// and receive a response from the Bluetooth module
// 1) send outgoing message
// 2) wait at least 10ms to receive NPI package
// 3) Wait for entire message to be received
// Input: msgPt points to message to send
//        responsePt points to empty buffer into which data is returned
//        maximum size (discard data beyond this limit)
// Output: APOK if ok, APFAIL on error (timeout or fcs error)
int AP_SendMessageResponse(uint8_t *msgPt, uint8_t *responsePt,uint32_t max){
  int result;
//  uint32_t timeout;
  result = AP_SendMessage(msgPt);
  if(result == APFAIL){
    return APFAIL;
  }
//  timeout = APTIMEOUT;
//  while(AP_RecvStatus()==0){
//    timeout--;
//    if(timeout==0){
//      return APFAIL; // 10 ms
//    }
//  }
  result = AP_RecvMessage(responsePt,max);
#ifdef APDEBUG
    AP_EchoSendMessage(msgPt);  // debugging
    AP_EchoReceived(result);    // debugging
#endif
  if(result == APFAIL){
    return APFAIL;
  }  
  return APOK;
}

typedef struct characteristics{
  uint16_t theHandle;          // each object has an ID
  uint16_t size;               // number of bytes in user data (1,2,4,8)
  uint8_t *pt;                 // pointer to user data, stored little endian
  void (*callBackRead)(void);  // action if SNP Characteristic Read Indication
  void (*callBackWrite)(void); // action if SNP Characteristic Write Indication
}characteristic_t;
#define MAXCHARACTERISTICS 10
uint32_t CharacteristicCount=0;
characteristic_t CharacteristicList[MAXCHARACTERISTICS];
typedef struct NotifyCharacteristics{
  uint16_t uuid;               // user defined 
  uint16_t theHandle;          // each object has an ID (used to notify)
  uint16_t CCCDhandle;         // generated/assigned by SNP
  uint16_t CCCDvalue;          // sent by phone to this object
  uint16_t size;               // number of bytes in user data (1,2,4,8)
  uint8_t *pt;                 // pointer to user data array, stored little endian
  void (*callBackCCCD)(void);  // action if SNP CCCD Updated Indication
}NotifyCharacteristic_t;
#define NOTIFYMAXCHARACTERISTICS 4
uint32_t NotifyCharacteristicCount=0;
NotifyCharacteristic_t NotifyCharacteristicList[NOTIFYMAXCHARACTERISTICS];


//*********AP_GetNotifyCCCD*******
// Return notification CCCD from the communication interface
// this does not perform BLU communication, it reads current CCCD value of notify characteristic
// Inputs:  index into which notify characteristic to return       
// Outputs: 16-bit CCCD value of the notify characteristic
uint16_t AP_GetNotifyCCCD(uint32_t i){
  return (NotifyCharacteristicList[i].CCCDvalue);
}




//*************AP_AddService**************
// Add a service
// Inputs uuid is 0xFFF0, 0xFFF1, ...
// Output APOK if successful,
//        APFAIL if SNP failure
int AP_AddService(uint16_t uuid){ int r;
  OutString("\n\rAdd service");
  NPI_AddService[6] = uuid&0xFF;
  NPI_AddService[7] = uuid>>8;
  r = AP_SendMessageResponse((uint8_t*)NPI_AddService,RecvBuf,RECVSIZE);  
  return r;
}

//*************AP_RegisterService**************
// Register a service
// Inputs none
// Output APOK if successful,
//        APFAIL if SNP failure
int AP_RegisterService(void){ int r;
  OutString("\n\rRegister service");
  r = AP_SendMessageResponse((uint8_t*)NPI_Register,RecvBuf,RECVSIZE);
  return r;
}

//*************AP_AddCharacteristic**************
// Add a read, write, or read/write characteristic
//        for notify properties, call AP_AddNotifyCharacteristic 
// Inputs uuid is 0xFFF0, 0xFFF1, ...
//        thesize is the number of bytes in the user data 1,2,4, or 8 
//        pt is a pointer to the user data, stored little endian
//        permission is GATT Permission, 0=none,1=read,2=write, 3=Read+write 
//        properties is GATT Properties, 2=read,8=write,0x0A=read+write
//        name is a null-terminated string, maximum length of name is 20 bytes
//        (*ReadFunc) called before it responses with data from internal structure
//        (*WriteFunc) called after it accepts data into internal structure
// Output APOK if successful,
//        APFAIL if name is empty, more than 8 characteristics, or if SNP failure
int AP_AddCharacteristic(uint16_t uuid, uint16_t thesize, void *pt, uint8_t permission,
  uint8_t properties, char name[], void(*ReadFunc)(void), void(*WriteFunc)(void)){
  int r; uint16_t handle; int i;
  if(thesize>8) return APFAIL;
  if(CharacteristicCount>=MAXCHARACTERISTICS) return APFAIL; // error
  NPI_AddCharValue[3] = 0x35;   // SNP Add Characteristic Value Declaration
  NPI_AddCharValue[4] = 0x82;  
  NPI_AddCharValue[5] = permission; // 0=none,1=read,2=write, 3=Read+write, GATT Permission
  NPI_AddCharValue[6] = properties; // 2=read,8=write,0x0A=read+write,0x10=notify, GATT Properties
  NPI_AddCharValue[11] = 0xFF&uuid; NPI_AddCharValue[12] = uuid>>8;
  OutString("\n\rAdd CharValue");
  r=AP_SendMessageResponse((uint8_t*)NPI_AddCharValue,RecvBuf,RECVSIZE);
  if(r == APFAIL) return APFAIL;
  handle = (RecvBuf[7]<<8)+RecvBuf[6]; // handle for this characteristic
  OutString("\n\rAdd CharDescriptor");
  i=0;
  while((i<20)&&(name[i])){
    NPI_AddCharDescriptor[11+i] = name[i]; i++;
  }
  if(i==0) return APFAIL;       // empty name

  NPI_AddCharDescriptor[11+i] = 0; i++;
  NPI_AddCharDescriptor[1] = 6+i;  // frame length
  NPI_AddCharDescriptor[3] = 0x35; // SNP Add Characteristic Descriptor Declaration
  NPI_AddCharDescriptor[4] = 0x83;
  NPI_AddCharDescriptor[5] = 0x80; // User Description String
  NPI_AddCharDescriptor[6] = 0x01; // GATT Read Permissions
  NPI_AddCharDescriptor[7] = NPI_AddCharDescriptor[9] = i;  // string length
  NPI_AddCharDescriptor[8] = NPI_AddCharDescriptor[10] = 0; // string length
  r=AP_SendMessageResponse((uint8_t*)NPI_AddCharDescriptor,RecvBuf,RECVSIZE);
  if(r == APFAIL) return APFAIL;
  CharacteristicList[CharacteristicCount].theHandle = handle;
  CharacteristicList[CharacteristicCount].size = thesize;
  CharacteristicList[CharacteristicCount].pt = (uint8_t *) pt;
  CharacteristicList[CharacteristicCount].callBackRead = ReadFunc;
  CharacteristicList[CharacteristicCount].callBackWrite = WriteFunc;
  CharacteristicCount++;
  return APOK; // OK
}  

//*************AP_AddNotifyCharacteristic**************
// Add a notify characteristic
//        for read, write, or read/write characteristic, call AP_AddCharacteristic 
// Inputs uuid is 0xFFF0, 0xFFF1, ...
//        thesize is the number of bytes in the user data 1,2,4, or 8 
//        pt is a pointer to the user data, stored little endian
//        name is a null-terminated string, maximum length of name is 20 bytes
//        (*CCCDfunc) called after it accepts , changing CCCDvalue
// Output APOK if successful,
//        APFAIL if name is empty, more than 4 notify characteristics, or if SNP failure
int AP_AddNotifyCharacteristic(uint16_t uuid, uint16_t thesize, void *pt,   
  char name[], void(*CCCDfunc)(void)){
  int r; uint16_t handle; int i;
  if(thesize>8) return APFAIL;
  if(NotifyCharacteristicCount>=NOTIFYMAXCHARACTERISTICS) return APFAIL; // error
  NPI_AddCharValue[3] = 0x35;   // SNP Add Characteristic Value Declaration
  NPI_AddCharValue[4] = 0x82;  
  NPI_AddCharValue[5] = 0x00;   // GATT no read, no Write GATT Permission
  NPI_AddCharValue[6] = 0x10;   // 0x10=notify, GATT Properties
  NPI_AddCharValue[11] = 0xFF&uuid; NPI_AddCharValue[12] = uuid>>8;
  OutString("\n\rAdd Notify CharValue");
  r=AP_SendMessageResponse((uint8_t*)NPI_AddCharValue,RecvBuf,RECVSIZE);
  if(r == APFAIL) return APFAIL;
  handle = (RecvBuf[7]<<8)+RecvBuf[6]; // handle for this characteristic
  OutString("\n\rAdd CharDescriptor");
  i=0;
  while((i<19)&&(name[i])){
    NPI_AddCharDescriptor[12+i] = name[i]; i++;
  }
  if(i==0) return APFAIL;               // empty name
  NPI_AddCharDescriptor[12+i] = 0; i++; // add null termination
  NPI_AddCharDescriptor[1] = 7+i;       // frame length
  NPI_AddCharDescriptor[3] = 0x35;      // SNP Add Characteristic Descriptor Declaration
  NPI_AddCharDescriptor[4] = 0x83;
  NPI_AddCharDescriptor[5] = 0x84;      // User Description String, and CCCD permissions
  NPI_AddCharDescriptor[6] = 0x03;      // CCCD parameters read+write
  NPI_AddCharDescriptor[7] = 0x01;      // GATT Read Permissions
  NPI_AddCharDescriptor[8] = NPI_AddCharDescriptor[10] = i; // string length
  NPI_AddCharDescriptor[9] = NPI_AddCharDescriptor[11] = 0; // string length
  r=AP_SendMessageResponse((uint8_t*)NPI_AddCharDescriptor,RecvBuf,RECVSIZE);
  if(r == APFAIL) return APFAIL;
  NotifyCharacteristicList[NotifyCharacteristicCount].uuid = uuid;
  NotifyCharacteristicList[NotifyCharacteristicCount].theHandle = handle;
  NotifyCharacteristicList[NotifyCharacteristicCount].CCCDhandle = (RecvBuf[8]<<8)+RecvBuf[7]; // handle for this CCCD
  NotifyCharacteristicList[NotifyCharacteristicCount].CCCDvalue = 0; // notify initially off
  NotifyCharacteristicList[NotifyCharacteristicCount].size = thesize;
  NotifyCharacteristicList[NotifyCharacteristicCount].pt = (uint8_t *) pt;
  NotifyCharacteristicList[NotifyCharacteristicCount].callBackCCCD = CCCDfunc;
  NotifyCharacteristicCount++;
  return APOK; // OK
}
  
//*************AP_SendNotification**************
// Send a notification (will skip if CCCD is 0) 
// Input:  index into notify characteristic to send
// Output: APOK if successful,
//         APFAIL if notification not configured, or if SNP failure
int AP_SendNotification(uint32_t i){ uint16_t handle; uint32_t j;uint8_t thedata;
  int r1; uint32_t s;
  if(i>= NotifyCharacteristicCount) return APFAIL;   // not valid
  if(NotifyCharacteristicList[i].CCCDvalue){         // send only if active
    handle = NotifyCharacteristicList[i].theHandle;
    if(handle == 0) return APFAIL; // not open   
    NPI_SendNotificationIndication[1] = 6+NotifyCharacteristicList[i].size;      // 1 to 8 bytes 
    OutString("\n\rSend data=");
    s = NotifyCharacteristicList[i].size;
    for(j=0; j<s; j++){
      thedata = NotifyCharacteristicList[i].pt[s-j-1]; // fetch data from user little endian to SNP big endian
      OutUHex(thedata); OutString(", ");      
      NPI_SendNotificationIndication[11+j] = thedata;    // copy into message, big endian
    }
    NPI_SendNotificationIndication[7] = handle&0x0FF; // handle
    NPI_SendNotificationIndication[8] = handle>>8; 
    r1=AP_SendMessageResponse(NPI_SendNotificationIndication,RecvBuf,RECVSIZE);
  }else{
    r1 = APOK; // no need to notify
  }
  return r1; // OK or fail depending on SendNotificationIndication
}
//*************AP_StartAdvertisement**************
// Start advertisement
// Input:  none
// Output: APOK if successful,
//         APFAIL if notification not configured, or if SNP failure
int AP_StartAdvertisement(void){volatile int r;
  OutString("\n\rSet Device name");
  r =AP_SendMessageResponse((uint8_t*)NPI_GATTSetDeviceName,RecvBuf,RECVSIZE);
  OutString("\n\rSetAdvertisement1");
  r =AP_SendMessageResponse((uint8_t*)NPI_SetAdvertisement1,RecvBuf,RECVSIZE);
//  OutString("\n\rSetAdvertisementSAP");
//  r =AP_SendMessageResponse((uint8_t*)NPI_SetAdvertisementSAP,RecvBuf,RECVSIZE);
  OutString("\n\rSetAdvertisement Data");
  r =AP_SendMessageResponse((uint8_t*)NPI_SetAdvertisementData,RecvBuf,RECVSIZE);
  OutString("\n\rStartAdvertisement");
  r =AP_SendMessageResponse((uint8_t*)NPI_StartAdvertisement,RecvBuf,RECVSIZE);
  return r;
}
//*************AP_StartAdvertisementJacki**************
// Start advertisement for Jacki
// Input:  none
// Output: APOK if successful,
//         APFAIL if notification not configured, or if SNP failure
int AP_StartAdvertisementJacki(void){
volatile int r=0;
// students need to write this as part of Lab 19
  return r;
}
//*************AP_GetStatus**************
// Get status of connection
// Input:  none
// Output: status 0xAABBCCDD
// AA is GAPRole Status
// BB is Advertising Status
// CC is ATT Status
// DD is ATT method in progress
uint32_t AP_GetStatus(void){volatile int r;
  OutString("\n\rGet Status");
  r = AP_SendMessageResponse((uint8_t*)NPI_GetStatus,RecvBuf,RECVSIZE);
  return (RecvBuf[4]<<24)+(RecvBuf[5]<<16)+(RecvBuf[6]<<8)+(RecvBuf[7]);
}
//*************AP_GetVersion**************
// Get version of the SNP application running on the CC2650
// Input:  none
// Output: version
uint32_t AP_GetVersion(void){volatile int r;
  OutString("\n\rGet Version");
  r = AP_SendMessageResponse((uint8_t*)NPI_GetVersion,RecvBuf,RECVSIZE); 
  return (RecvBuf[5]<<8)+(RecvBuf[6]);
}
// ****AP_BackgroundProcess****
// handle incoming SNP frames
// Inputs:  none
// Outputs: none
void AP_BackgroundProcess(void){
  int count; uint16_t h; int i,j;
  uint32_t s; // size of user data 1,2,4,8
  uint32_t d; // difference between packet size and user data size
  uint8_t responseNeeded;

  if(AP_RecvStatus()){
    if(AP_RecvMessage(RecvBuf,RECVSIZE)==APOK){
      OutString("\n\rRecvMessage");
      AP_EchoReceived(APOK);        
      if((RecvBuf[3]==0x55)&&(RecvBuf[4]==0x88)){// SNP Characteristic Write Indication (0x88)
        h = (RecvBuf[8]<<8)+RecvBuf[7]; // handle for this characteristic
        responseNeeded = RecvBuf[9];
        i = 0;
        while(i<MAXCHARACTERISTICS){
          if(CharacteristicList[i].theHandle == h){
            count = RecvBuf[1]-7;   // number of bytes in message
            s = CharacteristicList[i].size;
            if(count>s)count=s;   // truncate to size
            d = s-count;
            for(j=0;j<s;j++){     // if message is smaller than size
              CharacteristicList[i].pt[j] = 0; // fill MSbytes with 0
            }
            for(j=0;j<count;j++){ // write data
              CharacteristicList[i].pt[s-j-1-d] = RecvBuf[12+j];
            }
            (*CharacteristicList[i].callBackWrite)(); // process Characteristic Write Indication
            i = MAXCHARACTERISTICS;
          }else{
            i++;
          }
        }
        if(responseNeeded){
          AP_SendMessage(NPI_WriteConfirmation);
          AP_EchoSendMessage(NPI_WriteConfirmation);
        }
      }
      if((RecvBuf[3]==0x55)&&(RecvBuf[4]==0x87)){// SNP Characteristic Read Indication (0x87)
        h = (RecvBuf[8]<<8)+RecvBuf[7]; // handle for this characteristic
        i = 0;
        while(i<MAXCHARACTERISTICS){
          if(CharacteristicList[i].theHandle == h){
            (*CharacteristicList[i].callBackRead)(); // process Characteristic Read Indication
            NPI_ReadConfirmation[1] = 7+CharacteristicList[i].size;
            s = CharacteristicList[i].size;
            for(j=0;j<s;j++){ // write data
              NPI_ReadConfirmation[j+12]=CharacteristicList[i].pt[s-j-1];
            }
            i = MAXCHARACTERISTICS;
          }else{
            i++;
          }
        }
        NPI_ReadConfirmation[8] = RecvBuf[7]; // handle
        NPI_ReadConfirmation[9] = RecvBuf[8]; 
        AP_SendMessage(NPI_ReadConfirmation);
        AP_EchoSendMessage(NPI_ReadConfirmation);
      }
      if((RecvBuf[3]==0x55)&&(RecvBuf[4]==0x8B)){// SNP CCCD Updated Indication (0x8B)
        h = (RecvBuf[8]<<8)+RecvBuf[7]; // handle for this characteristic
        responseNeeded = RecvBuf[9];
        for(i=0; i<NOTIFYMAXCHARACTERISTICS;i++){
          if(NotifyCharacteristicList[i].CCCDhandle == h){  // to do
            NotifyCharacteristicList[i].CCCDvalue = (RecvBuf[11]<<8)+RecvBuf[10];
            NotifyCharacteristicList[i].callBackCCCD();
          }
        }
        if(responseNeeded){
          AP_SendMessage(NPI_CCCDUpdatedConfirmation);
          AP_EchoSendMessage(NPI_CCCDUpdatedConfirmation);
        }
      }        
    }
  }
}


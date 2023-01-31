// *****************Texas.c**************
// Open version of TExaS
//
// Runs on MSP432
// Daniel and Jonathan Valvano
// September 5, 2017

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
#include <stdint.h>
#include "..\inc\CortexM.h"
#include "msp.h"
#include "..\inc\TExaS.h"
// bit 7 must be set, so TExaSdisplay can separate characters from LA data
char volatile LogicData; // this is the 7-bit value sent to display
void LogicAnalyzer(void){        // called 10k/sec
  EUSCI_A0->TXBUF = LogicData;   // send data to PC (no synchronization)
}

void LogicAnalyzer_P1(void){        // called 10k/sec
  EUSCI_A0->TXBUF = (P1->IN)|0x80;  // send P1 data to PC (no synchronization)
}
void LogicAnalyzer_P2(void){        // called 10k/sec
  EUSCI_A0->TXBUF = (P2->IN)|0x80;  // send P2 data to PC (no synchronization)
}
void LogicAnalyzer_P2_7654(void){   // called 10k/sec
  EUSCI_A0->TXBUF = ((P2->IN)>>4)|0x80;  // send P2.7, P2.6, P2.5, P2.4 data to PC (no synchronization)
}
void LogicAnalyzer_P3(void){        // called 10k/sec
  EUSCI_A0->TXBUF = (P3->IN)|0x80;  // send P3 data to PC (no synchronization)
}
void LogicAnalyzer_P4(void){        // called 10k/sec
  EUSCI_A0->TXBUF = (P4->IN)|0x80;  // send P4 data to PC (no synchronization)
}
void LogicAnalyzer_P4_765432 (void){   // called 10k/sec
  EUSCI_A0->TXBUF = ((P4->IN)>>2)|0x80;  // send P4.7, P4.6, P4.5, P4.4, P4.3, P4.2 data to PC (no synchronization)
}
void LogicAnalyzer_P4_765320(void){  uint8_t in; // called 10k/sec
  in = P4->IN; // send P4.7, P4.6, P4.5, P4.3, P4.2, P4.0 data to PC (no synchronization)
  EUSCI_A0->TXBUF = ((in&0xE0)>>2)|((in&0x0C)>>1)|(in&0x01)|0x80;
}
void LogicAnalyzer_P5(void){        // called 10k/sec
  EUSCI_A0->TXBUF = (P5->IN)|0x80;  // send P5 data to PC (no synchronization)
}
void LogicAnalyzer_P6(void){        // called 10k/sec
  EUSCI_A0->TXBUF = (P6->IN)|0x80;  // send P6 data to PC (no synchronization)
}
void LogicAnalyzer_P7(void){        // called 10k/sec
  EUSCI_A0->TXBUF = (P7->IN)|0x80;  // send P7 data to PC (no synchronization)
}
void LogicAnalyzer_P8(void){        // called 10k/sec
  EUSCI_A0->TXBUF = (P8->IN)|0x80;  // send P8 data to PC (no synchronization)
}
void LogicAnalyzer_P9(void){        // called 10k/sec
  EUSCI_A0->TXBUF = (P9->IN)|0x80;  // send P9 data to PC (no synchronization)
}
void LogicAnalyzer_P10(void){        // called 10k/sec
  EUSCI_A0->TXBUF = (P10->IN)|0x80;  // send 10 data to PC (no synchronization)
}

// Error counters for scope functionality
uint32_t TExaS_ScopeErrLostData = 0; // error: incremented when any data lost
uint32_t TExaS_ScopeErrConflict = 0; // error: incremented when ADC busy with conversion not started by TExaS during interrupt
uint32_t TExaS_ScopeWrnReconfig = 0; // observation: incremented when ADC was reconfigured but not conflicted
#define TEXASADCSEQUENCER (6)        // ADC sequencer number
#define TEXASADCRESULTLOC (ADC14->MEM[6])// ADC sequencer memory register
void Scope(void){          // called 10k/sec
  if((ADC14->IFGR0&0x40) != 0){
    // conversion result is ready
      EUSCI_A0->TXBUF = (TEXASADCRESULTLOC>>6); // assumes no other program changed ADC out of 14-bit mode in ADC14CTL1
  } else{
    // conversion result is not ready
    TExaS_ScopeErrLostData = TExaS_ScopeErrLostData + 1;
  }
  // try to start the next conversion
  if((ADC14->CTL1&0x001F0000) != (TEXASADCSEQUENCER << 16)){
    // ADC has been reconfigured by another thread
    if(ADC14->CTL0&0x00010000){
      // ADC is currently busy
      // do nothing (next Scope() interrupt will have lost data)
      TExaS_ScopeErrConflict = TExaS_ScopeErrConflict + 1;
    } else{
      // ADC is currently idle
      TExaS_ScopeWrnReconfig = TExaS_ScopeWrnReconfig + 1;
      ADC14->CTL0 &= ~0x00000002;              // 1) ADC14ENC = 0 to allow programming
      while(ADC14->CTL0&0x00010000){};         // 2) wait for BUSY to be zero
      ADC14->CTL1 = (ADC14->CTL1&~0x001F0000)| // clear STARTADDx bit field
                 (TEXASADCSEQUENCER << 16);    // 3) configure for STARTADDx = TEXASADCSEQUENCER
      ADC14->CTL0 |= 0x00000003;               // 4) enable conversions and start single conversion
    }
  } else{
    // ADC is still configured as TExaS left it
    ADC14->CTL0 |= 0x00000001;       // start single conversion
  }
}
void (*PeriodicTask2)(void);   // user function
/* Version 1 uses Timer A3
// ------------PeriodicTask2_Init------------
// Activate an interrupt to run a user task periodically.
// Give it a priority 0 to 6 with lower numbers
// signifying higher priority.  Equal priority is
// handled sequentially.
// Input:  task is a pointer to a user function
//         subs is subsystem clock frequency in Hz
//         freq is number of interrupts per second
//           1 Hz to 10 kHz
//         priority is a number 0 to 6
// Output: none

void PeriodicTask2_Init(void(*task)(void), uint32_t freq, uint8_t priority){
  if((freq == 0) || (freq > 10000)){
    return;                        // invalid input
  }
  if(priority > 6){
    priority = 6;
  }
  PeriodicTask2 = task;            // user function
  // ***************** TimerA3 initialization *****************
  TIMER_A3->CTL &= ~0x0030;               // halt Timer A3
  // bits15-10=XXXXXX, reserved
  // bits9-8=10,       clock source to SMCLK (12,000,000 Hz after BSP_Clock_InitFastest() called)
  // bits7-6=00,       input clock divider /1
  // bits5-4=00,       stop mode
  // bit3=X,           reserved
  // bit2=0,           set this bit to clear
  // bit1=0,           no interrupt on timer
  // bit0=0,           clear interrupt pending
  TIMER_A3->CTL = 0x0200;
  TIMER_A3->EX0 &= ~0x0007;               // configure for input clock divider /1
  // bits15-14=00,     no capture mode
  // bits13-12=XX,     capture/compare input select
  // bit11=X,          synchronize capture source
  // bit10=X,          synchronized capture/compare input
  // bit9=X,           reserved
  // bit8=0,           compare mode
  // bits7-5=XXX,      output mode
  // bit4=1,           enable capture/compare interrupt on CCIFG
  // bit3=X,           read capture/compare input from here
  // bit2=0,           output this value in output mode 0
  // bit1=X,           capture overflow status
  // bit0=0,           clear capture/compare interrupt pending
  TIMER_A3->CCTL[0] = 0x0010;
  TIMER_A3->CCR[0] = (12000000/freq - 1);      // compare match value
// interrupts enabled in the main program after all devices initialized
  NVIC->IP[3] = (NVIC->IP[3]&0xFF00FFFF)|(priority<<21); // priority
  NVIC->ISER[0] = 0x00004000;         // enable interrupt 14 in NVIC
  TIMER_A3->CTL |= 0x0014;            // reset and start Timer A3 in up mode
}

void TA3_0_IRQHandler(void){
  TIMER_A3->CCTL[0] &= ~0x0001;    // acknowledge capture/compare interrupt 0
  (*PeriodicTask2)();              // execute user task
}

// ------------PeriodicTask2_Stop------------
// Deactivate the interrupt running a user task periodically.
// Input: none
// Output: none
void PeriodicTask2_Stop(void){
  TIMER_A3->CCTL[0] &= ~0x0001;    // clear capture/compare interrupt pending
  NVIC->ICER[0] = 0x00004000;      // disable interrupt 14 in NVIC
}

*/
// Version 2 uses Timer32 module 1
void PeriodicTask2_Init(void(*task)(void), uint32_t freq, uint8_t priority){
  if((freq == 0) || (freq > 10000)){
    return;                        // invalid input
  }
  if(priority > 6){
    priority = 6;
  }
  PeriodicTask2 = task;            // user function
  TIMER32_1->LOAD = (48000000/freq - 1); // timer reload value
  TIMER32_1->INTCLR = 0x00000001;    // clear Timer32 Timer 1 interrupt
  // bits31-8=X...X,   reserved
  // bit7=1,           timer enable
  // bit6=1,           timer in periodic mode
  // bit5=1,           interrupt enable
  // bit4=X,           reserved
  // bits3-2=00,       /1 input clock divider
  // bit1=1,           32-bit counter
  // bit0=0,           wrapping mode
  TIMER32_1->CONTROL = 0x000000E2;
// interrupts enabled in the main program after all devices initialized
  NVIC->IP[6] = (NVIC->IP[6]&0xFFFF00FF)|(priority<<13);
  NVIC->ISER[0] = 0x02000000;   // enable interrupt 25 in NVIC
}
void T32_INT1_IRQHandler(void){
  TIMER32_1->INTCLR = 0x00000001;  // acknowledge Timer32 Timer 1 interrupt
  (*PeriodicTask2)();              // execute user task
}
// ------------PeriodicTask2_Stop------------
// Deactivate the interrupt running a user task periodically.
// Input: none
// Output: none
void PeriodicTask2_Stop(void){
  TIMER32_1->INTCLR = 0x00000001; // clear capture/compare interrupt pending
  NVIC->ICER[0] = 0x02000000;     // disable interrupt 25 in NVIC
}

//------------UART_Init------------
// Initialize the UART for 115,200 baud rate (assuming 12 MHz SMCLK)
// 8 bit word length, no parity bits, one stop bit
// Input: none
// Output: none
void UART_Init(void){
  if(((P1->SEL0&0x0C)==0x0C)&&(EUSCI_A0->BRW==104))return; // already on
  EUSCI_A0->CTLW0 = 0x0001;                   // hold the USCI module in reset mode
  // bit15=0,      no parity bits
  // bit14=x,      not used when parity is disabled
  // bit13=0,      LSB first
  // bit12=0,      8-bit data length
  // bit11=0,      1 stop bit
  // bits10-8=000, asynchronous UART mode
  // bits7-6=11,   clock source to SMCLK
  // bit5=0,       reject erroneous characters and do not set flag
  // bit4=0,       do not set flag for break characters
  // bit3=0,       not dormant
  // bit2=0,       transmit data, not address (not used here)
  // bit1=0,       do not transmit break (not used here)
  // bit0=1,       hold logic in reset state while configuring
  EUSCI_A0->CTLW0 = 0x00C1;
                              // set the baud rate
                              // N = clock/baud rate = 12,000,000/115,200 = 104.1666667
  EUSCI_A0->BRW = 104;        // UCBR = baud rate = int(N) = 104
  // actual baud rate is 12,000,000/104 = 115,385 bps (0.16% error)
  EUSCI_A0->MCTLW &= ~0xFFF1; // clear first and second modulation stage bit fields
                              // configure second modulation stage select (from Table 22-4 on p731 of datasheet)
//  UCA0MCTLW |= (0<<8);      // UCBRS = N - int(N) = 0.0417; plug this in Table 22-4
                              // configure first modulation stage select (ignored when oversampling disabled)
//  UCA0MCTLW |= (10<<4);     // UCBRF = int(((N/16) - int(N/16))*16) = 10
//  UCA0MCTLW |= 0x0001;      // enable oversampling mode
  P1->SEL0 |= 0x0C;
  P1->SEL1 &= ~0x0C;          // configure P1.3 and P1.2 as primary module function
  EUSCI_A0->CTLW0 &= ~0x0001; // enable the USCI module
  EUSCI_A0->IE &= ~0x000F;    // disable interrupts (transmit ready, start received, transmit empty, receive full)
}

//------------UART_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed
char UART_InChar(void){
  while((EUSCI_A0->IFG&0x01) == 0);
  return((char)(EUSCI_A0->RXBUF));
}

//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART_OutChar(char data){
  while((EUSCI_A0->IFG&0x02) == 0);
  EUSCI_A0->TXBUF = data;
}

// toggle bit 0 
void TExaS_Task0(void){
  LogicData ^= 0x01;
}
// toggle bit 1 
void TExaS_Task1(void){
  LogicData ^= 0x02;
}
// toggle bit 2 
void TExaS_Task2(void){
  LogicData ^= 0x04;
}
// toggle bit 3 
void TExaS_Task3(void){ 
  LogicData ^= 0x08;
}
// toggle bit 4 
void TExaS_Task4(void){
}
// toggle bit 5 
void TExaS_Task5(void){
  LogicData ^= 0x20;
}
// toggle bit 6 
void TExaS_Task6(void){
  LogicData ^= 0x40;
}
// specify all seven bits of logic analyzer 
void TExaS_Set(uint8_t data){
  LogicData = data|0x80; // bit 7 must be set
}
// set bit 0 
void TExaS_Set0(void){
  LogicData |= 0x01;
}
// set bit 1 
void TExaS_Set1(void){
  LogicData |= 0x02;
}
// set bit 2 
void TExaS_Set2(void){
  LogicData |= 0x04;
}
// set bit 3 
void TExaS_Set3(void){ 
  LogicData |= 0x08;
}
// set bit 4 
void TExaS_Set4(void){
}
// set bit 5 
void TExaS_Set5(void){
  LogicData |= 0x20;
}
// set bit 6 
void TExaS_Set6(void){
  LogicData |= 0x40;
}
// clear bit 0 
void TExaS_Clear0(void){
  LogicData |= 0x01;
}
// clear bit 1 
void TExaS_Clear1(void){
  LogicData |= 0x02;
}
// clear bit 2 
void TExaS_Clear2(void){
  LogicData |= 0x04;
}
// clear bit 3 
void TExaS_Clear3(void){ 
  LogicData |= 0x08;
}
// clear bit 4 
void TExaS_Clear4(void){
}
// clear bit 5 
void TExaS_Clear5(void){
  LogicData |= 0x20;
}
// clear bit 6 
void TExaS_Clear6(void){
  LogicData |= 0x40;
}

// There are six analog inputs on the Educational BoosterPack MKII:
// microphone (J1.6/P4.3/A10)
// joystick X (J1.2/P6.0/A15) and Y (J3.26/P4.4/A9)
// accelerometer X (J3.23/P6.1/A14), Y (J3.24/P4.0/A13), and Z (J3.25/P4.2/A11)
// All six initialization functions can use this general ADC
// initialization.  The joystick uses sequence starting at 0,
// the accelerometer uses sequence starting at 2, and the
// microphone uses sequence starting at 5.
// TExaS adds a seventh sequence starting at 6 and just sampling
// J3.26/P4.4/A9.  As always, it is up to the user to not allow
// more than one thread to use the ADC at the same time.
void ADC_Init(void){
/*reference not used--analog peripherals are 0 to 3.3V
  while(REFCTL0&0x0400){};         // wait for the reference to be idle before reconfiguring (see REF4 in errata)
  // 15-14 reserved                          00b (reserved)
  // 13    REFBGRDY   bandgap voltage ready   0b (read only)
  // 12    REFGENRDY  reference voltage ready 0b (read only)
  // 11    BGMODE     bandgap mode            0b (read only)
  // 10    REFGENBUSY no reconfigure if busy  0b (read only)
  // 9     REFBGACT   bandgap active          0b (read only)
  // 8     REFGENACT  reference active        0b (read only)
  // 7     REFBGOT    trigger bandgap         0b = no software trigger set
  // 6     REFGENOT   trigger reference       0b = no software trigger set
  // 5-4   REFVSEL    voltage level select   11b = 2.5V
  // 3     REFTCOFF   temperature disable     1b = temperature sensor disabled to save power
  // 2     reserved                           0b (reserved)
  // 1     REFOUT     reference output buffer 0b = reference output not on P5.6 (see also REFBURST in ADC14CTL1, P5SEL1, and P5SEL0)
  // 0     REFON      reference enable        1b = reference enabled in static mode
  REFCTL0 = 0x0039;                // 1) configure reference for static 2.5V
  while((REFCTL0&0x1000) == 0){};  // wait for the reference to stabilize before continuing (optional, see REF8 in errata)
*/
  ADC14->CTL0 &= ~0x00000002;        // 2) ADC14ENC = 0 to allow programming
  while(ADC14->CTL0&0x00010000){};   // 3) wait for BUSY to be zero
  // 31-30 ADC14PDIV  predivider,            00b = Predivide by 1
  // 29-27 ADC14SHSx  SHM source            000b = ADC14SC bit
  // 26    ADC14SHP   SHM pulse-mode          1b = SAMPCON the sampling timer
  // 25    ADC14ISSH  invert sample-and-hold  0b = not inverted
  // 24-22 ADC14DIVx  clock divider         000b = /1
  // 21-19 ADC14SSELx clock source select   100b = SMCLK
  // 18-17 ADC14CONSEQx mode select          01b = Sequence-of-channels
  // 16    ADC14BUSY  ADC14 busy              0b (read only)
  // 15-12 ADC14SHT1x sample-and-hold time 0011b = 32 clocks
  // 11-8  ADC14SHT0x sample-and-hold time 0011b = 32 clocks
  // 7     ADC14MSC   multiple sample         1b = continue conversions automatically after first SHI signal trigger
  // 6-5   reserved                          00b (reserved)
  // 4     ADC14ON    ADC14 on                1b = powered up
  // 3-2   reserved                          00b (reserved)
  // 1     ADC14ENC   enable conversion       0b = ADC14 disabled
  // 0     ADC14SC    ADC14 start             0b = No start (yet)
  ADC14->CTL0 = 0x04223390;          // 4) single, SMCLK, on, disabled, /1, 32 SHM
  // 20-16 STARTADDx  start addr          00110b = ADC14MEM6
  // 15-6  reserved                  0000000000b (reserved)
  // 5-4   ADC14RES   ADC14 resolution       11b = 14 bit, 16 clocks
  // 3     ADC14DF    data read-back format   0b = Binary unsigned
  // 2     REFBURST   reference buffer burst  0b = reference on continuously
  // 1-0   ADC14PWRMD ADC power modes        00b = Regular power mode
  ADC14->CTL1 = 0x00060030;          // 5) ADC14MEM6, 14-bit, ref on, regular power
  // 15   ADC14WINCTH Window comp threshold   0b = not used
  // 14   ADC14WINC   Comparator enable       0b = Comparator disabled
  // 13   ADC14DIF    Differential mode       0b = Single-ended mode enabled
  // 12   reserved                            0b (reserved)
  // 11-8 ADC14VRSEL  V(R+) and V(R-)      0000b = V(R+) = AVCC, V(R-) = AVSS
  // 7    ADC14EOS    End of sequence         1b = End of sequence
  // 6-5  reserved                           00b (reserved)
  // 4-0  ADC14INCHx  Input channel       01001b = A9, P4.4
  ADC14->MCTL[6] = 0x00000089;     // 6) 0 to 3.3V, channel 9
  ADC14->IER0 = 0;
  ADC14->IER1 = 0;                 // 7) no interrupts
  P4SEL0 |= 0x10;
  P4SEL1 |= 0x10;                  // 8) analog mode on P4.4/A9
  ADC14->CTL0 |= 0x00000002;       // 9) enable

  // software initiates ADC conversions
  // usually occurs in Scope() function called from periodic interrupt (first timing will be wrong)
  while(ADC14->CTL0&0x00010000){}; // 10) wait for BUSY to be zero
  ADC14->CTL0 |= 0x00000001;       // 11) start single conversion
}

// ************TExaS_Init*****************
// Initialize scope or logic analyzer, triggered by periodic timer
// This needs to be called once
// Inputs: Scope or Logic analyzer
//         subsystem clock frequency in Hz
// Outputs: none
void TExaS_Init(enum TExaSmode mode){
  // 32 bit free running timer
  // 10 kHz periodic interrupt
  // edge triggered interrupt on Profile bits
  // grade mode will collect 10 seconds of profile (4 arrays)
  // logic analyzer will 10 kHz output to serial port (pack 4 bits): 8 bit bit7 set then LA, but 7 ASCII
//  DumpNumber = dump;  // number of profile points to dump
  UART_Init();
  LogicData |= 0x80; // bit 7 means logic data
  if(mode == LOGICANALYZER){
    // enable 10 kHz periodic interrupt
    PeriodicTask2_Init(&LogicAnalyzer,10000,5); // run logic analyzer
  }else if(mode == LOGICANALYZER_P1){
    // enable 10 kHz periodic interrupt
    PeriodicTask2_Init(&LogicAnalyzer_P1,10000,5); // run logic analyzer
  }else if(mode == LOGICANALYZER_P2){
    // enable 10 kHz periodic interrupt
    PeriodicTask2_Init(&LogicAnalyzer_P2,10000,5); // run logic analyzer
  }else if(mode == LOGICANALYZER_P2_7654){
    // enable 10 kHz periodic interrupt
    PeriodicTask2_Init(&LogicAnalyzer_P2_7654,10000,5); // run logic analyzer
  }else if(mode == LOGICANALYZER_P3){
    // enable 10 kHz periodic interrupt
    PeriodicTask2_Init(&LogicAnalyzer_P3,10000,5); // run logic analyzer
  }else if(mode == LOGICANALYZER_P4){
    // enable 10 kHz periodic interrupt
    PeriodicTask2_Init(&LogicAnalyzer_P4,10000,5); // run logic analyzer
  }else if(mode == LOGICANALYZER_P4_765432){
    // enable 10 kHz periodic interrupt
    PeriodicTask2_Init(&LogicAnalyzer_P4_765432,10000,5); // run logic analyzer
  }else if(mode == LOGICANALYZER_P4_765320){
    // enable 10 kHz periodic interrupt
    PeriodicTask2_Init(&LogicAnalyzer_P4_765320,10000,5); // run logic analyzer
  }else if(mode == LOGICANALYZER_P5){
    // enable 10 kHz periodic interrupt
    PeriodicTask2_Init(&LogicAnalyzer_P5,10000,5); // run logic analyzer
  }else if(mode == LOGICANALYZER_P6){
    // enable 10 kHz periodic interrupt
    PeriodicTask2_Init(&LogicAnalyzer_P6,10000,5); // run logic analyzer
  }else if(mode == LOGICANALYZER_P7){
    // enable 10 kHz periodic interrupt
    PeriodicTask2_Init(&LogicAnalyzer_P7,10000,5); // run logic analyzer
  }else if(mode == LOGICANALYZER_P8){
    // enable 10 kHz periodic interrupt
    PeriodicTask2_Init(&LogicAnalyzer_P8,10000,5); // run logic analyzer
  }else if(mode == LOGICANALYZER_P9){
    // enable 10 kHz periodic interrupt
    PeriodicTask2_Init(&LogicAnalyzer_P9,10000,5); // run logic analyzer
  }else if(mode == LOGICANALYZER_P10){
    // enable 10 kHz periodic interrupt
    PeriodicTask2_Init(&LogicAnalyzer_P10,10000,5); // run logic analyzer
  }else if(mode == SCOPE){
    ADC_Init();
    // enable 10 kHz periodic interrupt
    PeriodicTask2_Init(&Scope,10000,5); // run scope at 10k
  }
}

// ************TExaS_Stop*****************
// Stop the transfer
// Inputs:  none
// Outputs: none
void TExaS_Stop(void){
  PeriodicTask2_Stop();
}

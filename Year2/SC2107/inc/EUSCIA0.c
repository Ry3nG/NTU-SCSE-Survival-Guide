// EUSCIA0.c
// Runs on MSP432
// Interrupt-driven device driver for the UART UCA0.
// Daniel and Jonathan Valvano
// October 19, 2017
// Modified by EE345L students Charlie Gough && Matt Hawk
// Modified by EE345M students Agustinus Darmawan && Mingjie Qiu

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

// UCA0RXD (VCP receive) connected to P1.2
// UCA0TXD (VCP transmit) connected to P1.3
#include <stdint.h>
#include "../inc/FIFO0.h"
#include "EUSCIA0.h"
#include "msp.h"


//------------EUSCIA0_Init------------
// Initialize the UART for 115,200 baud rate (assuming 48 MHz bus clock),
// 8 bit word length, no parity bits, one stop bit
// Input: none
// Output: none
void EUSCIA0_Init(void){
  RxFifo0_Init();              // initialize FIFOs
  TxFifo0_Init();
  EUSCI_A0->CTLW0 = 0x0001;         // hold the USCI module in reset mode
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
  // N = clock/baud rate = 12,000,000/115,200 = 104.1667
  EUSCI_A0->BRW = 104;          // UCBR = baud rate = int(N) = 104
  EUSCI_A0->MCTLW &= ~0xFFF1;   // clear first and second modulation stage bit fields

// since TxFifo is empty, we initially disarm interrupts on UCTXIFG, but arm it on OutChar
  P1->SEL0 |= 0x0C;
  P1->SEL1 &= ~0x0C;            // configure P1.3 and P1.2 as primary module function
  NVIC->IP[4] = (NVIC->IP[4]&0xFFFFFF00)|0x00000040; // priority 2
  NVIC->ISER[0] |= 0x00010000;   // enable interrupt 16 in NVIC

  EUSCI_A0->CTLW0 &= ~0x0001;   // enable the USCI module
                                // enable interrupts on receive full
  EUSCI_A0->IE = 0x0001;        // disable interrupts on transmit empty, start, complete
}


//------------EUSCI_A0_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed
// spin if RxFifo is empty
char EUSCIA0_InChar(void){
  char letter;
  while(RxFifo0_Get(&letter) == FIFOFAIL){};
  return(letter);
}

//------------EUSCIA0_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
// spin if TxFifo is full
void EUSCIA0_OutChar(char data){
  while(TxFifo0_Put(data) == FIFOFAIL){}; // spin if full
  EUSCI_A0->IE = 0x0003;     // enable interrupts on transmit empty and receive full
}

// interrupt 16 occurs on either:
// UCTXIFG TX data register is empty
// UCRXIFG RX data register is full
// vector at 0x00000080 in startup_msp432.s
void EUSCIA0_IRQHandler(void){ char data; 
  if(EUSCI_A0->IFG&0x02){             // TX data register empty
    if(TxFifo0_Get(&data) == FIFOFAIL){
      EUSCI_A0->IE = 0x0001;         // disable interrupts on transmit empty
    }else{
      EUSCI_A0->TXBUF = data;        // send data, acknowledge interrupt
    }
  }
  if(EUSCI_A0->IFG&0x01){             // RX data register full
    RxFifo0_Put((char)EUSCI_A0->RXBUF);// clears UCRXIFG
  } 
}

//------------EUSCIA0_OutString------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void EUSCIA0_OutString(char *pt){
  while(*pt){
    EUSCIA0_OutChar(*pt);
    pt++;
  }
}

//------------EUSCIA0_InUDec------------
// InUDec accepts ASCII input in unsigned decimal format
//     and converts to a 32-bit unsigned number
//     valid range is 0 to 4294967295 (2^32-1)
// Input: none
// Output: 32-bit unsigned number
// If you enter a number above 4294967295, it will return an incorrect value
// Backspace will remove last digit typed
uint32_t EUSCIA0_InUDec(void){
uint32_t number=0, length=0;
char character;
  character = EUSCIA0_InChar();
  while(character != CR){ // accepts until <enter> is typed
// The next line checks that the input is a digit, 0-9.
// If the character is not 0-9, it is ignored and not echoed
    if((character>='0') && (character<='9')) {
      number = 10*number+(character-'0');   // this line overflows if above 4294967295
      length++;
      EUSCIA0_OutChar(character);
    }
// If the input is a backspace, then the return number is
// changed and a backspace is output to the screen
    else if((character==BS) && length){
      number /= 10;
      length--;
      EUSCIA0_OutChar(character);
    }
    character = EUSCIA0_InChar();
  }
  return number;
}

//-----------------------EUSCIA0_OutUDec-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// Variable format 1-10 digits with no space before or after
void EUSCIA0_OutUDec(uint32_t n){
// This function uses recursion to convert decimal number
//   of unspecified length as an ASCII string
  if(n >= 10){
    EUSCIA0_OutUDec(n/10);
    n = n%10;
  }
  EUSCIA0_OutChar(n+'0'); /* n is between 0 and 9 */
}

uint32_t Messageindexc;
char Messagec[8];
void static fillmessagec(uint32_t n){
// This function uses recursion to convert decimal number
//   of unspecified length as an ASCII string
  if(n >= 10){
    fillmessagec(n/10);
    n = n%10;
  }
  Messagec[Messageindexc] = (n+'0'); /* n is between 0 and 9 */
  if(Messageindexc<7)Messageindexc++;
}
void static fillmessage4b(uint32_t n){
  if(n>=1000){  // 1000 to 9999
    Messageindexc = 0;
  } else if(n>=100){  // 100 to 999
    Messagec[0] = ' ';
    Messageindexc = 1;
  }else if(n>=10){ //
    Messagec[0] = ' '; /* n is between 10 and 99 */
    Messagec[1] = ' ';
    Messageindexc = 2;
  }else{
    Messagec[0] = ' '; /* n is between 0 and 9 */
    Messagec[1] = ' ';
    Messagec[2] = ' ';
    Messageindexc = 3;
  }
  fillmessagec(n);
}
void static fillmessage5b(uint32_t n){
  if(n>99999)n=99999;
  if(n>=10000){  // 10000 to 99999
    Messageindexc = 0;
  } else if(n>=1000){  // 1000 to 9999
    Messagec[0] = ' ';
    Messageindexc = 1;
  }else if(n>=100){  // 100 to 999
    Messagec[0] = ' ';
    Messagec[1] = ' ';
    Messageindexc = 2;
  }else if(n>=10){ //
    Messagec[0] = ' '; /* n is between 10 and 99 */
    Messagec[1] = ' ';
    Messagec[2] = ' ';
    Messageindexc = 3;
  }else{
    Messagec[0] = ' '; /* n is between 0 and 9 */
    Messagec[1] = ' ';
    Messagec[2] = ' ';
    Messagec[3] = ' ';
    Messageindexc = 4;
  }
  fillmessagec(n);
}

//-----------------------EUSCIA0_OutUDec4-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// Fixed format 4 digits with no space before or after
void EUSCIA0_OutUDec4(uint32_t n){
  if(n>9999){
    EUSCIA0_OutString("****");
  }else{
    Messageindexc = 0;
    fillmessage4b(n);
    Messagec[Messageindexc] = 0; // terminate
    EUSCIA0_OutString(Messagec);
  }
}

//-----------------------EUSCIA0_OutUDec5-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// Fixed format 5 digits with no space before or after
void EUSCIA0_OutUDec5(uint32_t n){
  if(n>99999){
    EUSCIA0_OutString("*****");
  }else{
    Messageindexc = 0;
    fillmessage5b(n);
    Messagec[Messageindexc] = 0; // terminate
    EUSCIA0_OutString(Messagec);
  }
}

//-----------------------EUSCIA0_OutUFix1-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// fixed format <digit>.<digit> with no space before or after
void EUSCIA0_OutUFix1(uint32_t n){
  EUSCIA0_OutUDec(n/10);
  EUSCIA0_OutChar('.');
  EUSCIA0_OutUDec(n%10);
}

//-----------------------EUSCIA0_OutUFix2-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// fixed format <digit>.<digit><digit> with no space before or after
void EUSCIA0_OutUFix2(uint32_t n){
  EUSCIA0_OutUDec(n/100);
  EUSCIA0_OutChar('.');
  n = n%100;
  EUSCIA0_OutUDec(n/10);
  EUSCIA0_OutUDec(n%10);
}

//---------------------EUSCIA0_InUHex----------------------------------------
// Accepts ASCII input in unsigned hexadecimal (base 16) format
// Input: none
// Output: 32-bit unsigned number
// No '$' or '0x' need be entered, just the 1 to 8 hex digits
// It will convert lower case a-f to upper-case A-F
//     and converts to a 16 bit unsigned number
//     value range is 0 to FFFFFFFF
// If you enter a number above FFFFFFFF, it will return an incorrect value
// Backspace will remove last digit typed
uint32_t EUSCIA0_InUHex(void){
uint32_t number=0, digit, length=0;
char character;
  character = EUSCIA0_InChar();
  while(character != CR){
    digit = 0x10; // assume bad
    if((character>='0') && (character<='9')){
      digit = character-'0';
    }
    else if((character>='A') && (character<='F')){
      digit = (character-'A')+0xA;
    }
    else if((character>='a') && (character<='f')){
      digit = (character-'a')+0xA;
    }
// If the character is not 0-9 or A-F, it is ignored and not echoed
    if(digit <= 0xF){
      number = number*0x10+digit;
      length++;
      EUSCIA0_OutChar(character);
    }
// Backspace output and return value changed if a backspace is input
    else if((character==BS) && length){
      number /= 0x10;
      length--;
      EUSCIA0_OutChar(character);
    }
    character = EUSCIA0_InChar();
  }
  return number;
}

//--------------------------EUSCIA0_OutUHex----------------------------
// Output a 32-bit number in unsigned hexadecimal format
// Input: 32-bit number to be transferred
// Output: none
// Variable format 1 to 8 digits with no space before or after
void EUSCIA0_OutUHex(uint32_t number){
// This function uses recursion to convert the number of
//   unspecified length as an ASCII string
  if(number >= 0x10){
    EUSCIA0_OutUHex(number/0x10);
    EUSCIA0_OutUHex(number%0x10);
  }
  else{
    if(number < 0xA){
      EUSCIA0_OutChar(number+'0');
     }
    else{
      EUSCIA0_OutChar((number-0x0A)+'A');
    }
  }
}

//--------------------------EUSCIA0_OutUHex2----------------------------
// Output a 32-bit number in unsigned hexadecimal format
// Input: 32-bit number to be transferred
// Output: none
// Fixed format 2 digits with no space before or after
void EUSCIA0outnibble(uint32_t n){
  if(n < 0xA){
    EUSCIA0_OutChar(n+'0');
  }
  else{
    EUSCIA0_OutChar((n-0x0A)+'A');
  }
}
void EUSCIA0_OutUHex2(uint32_t number){
  EUSCIA0outnibble(number/0x10); // ms digit
  EUSCIA0outnibble(number%0x10); // ls digit
}

//------------EUSCIA0_InString------------
// Accepts ASCII characters from the serial port
//    and adds them to a string until <enter> is typed
//    or until max length of the string is reached.
// It echoes each character as it is input.
// If a backspace is input, the string is modified
//    and the backspace is echoed
// terminates the string with a null character
// uses busy-waiting synchronization on RDRF
// Input: pointer to empty buffer, size of buffer
// Output: Null terminated string
// -- Modified by Agustinus Darmawan + Mingjie Qiu --
void EUSCIA0_InString(char *bufPt, uint16_t max) {
int length=0;
char character;
  character = EUSCIA0_InChar();
  while(character != CR){
    if(character == BS){
      if(length){
        bufPt--;
        length--;
        EUSCIA0_OutChar(BS);
      }
    }
    else if(length < max){
      *bufPt = character;
      bufPt++;
      length++;
      EUSCIA0_OutChar(character);
    }
    character = EUSCIA0_InChar();
  }
  *bufPt = 0;
}

// UARTtestmain.c
// Runs on MSP432
// Test UART and printf functions.
// Daniel and Jonathan Valvano
// September 23, 2017

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

//  UCA0RXD (VCP receive) connected to P1.2
//  UCA0TXD (VCP transmit) connected to P1.3
//  Busy-wait device driver for the EUSCI A0 UART
// to be able to use printf
// 1) add UART0.c to project
// 2) "..\inc\UART0.h"
// 3) Must be running at 48 MHz, Clock_Init48MHz();
// 4) Call UART0_Initprintf()

#include <stdint.h>
#include <stdio.h>
#include "msp.h"
#include "..\inc\Clock.h"
#include "..\inc\UART0.h"

void BookExamples(void){ // examples from the book
  int8_t cc = 0x56; // (‘V’)
  int32_t xx = 100;
  int16_t yy = -100;
  float zz = 3.14159265;

  printf("\nHello world\n");      //Hello world
  printf("cc = %c %d\n",cc,cc); //cc = V 86
  printf("cc = %#x\n",cc);      //cc = 0x56
  printf("xx = %c %d\n",xx,xx); //xx = d 100
  printf("xx = %#x\n",xx);      //xx = 0x64
  printf("yy = %d\n",yy);       //yy = -100
  printf("%#x   \n",yy);        //yy = 0xffffff9c
  printf("%e \n",zz);           //zz = 3.14159e+00
  printf("%E \n",zz);           //zz = 3.14159E+00
  printf("%f     \n",zz);       //zz = 3.14159
  printf("%g     \n",zz);       //zz = 3.14159 (shorter of two, either f or e)
  printf("%3.2f     \n",zz); //zz =  3.14
}

// demonstrates features of the UART driver
int main(void){
  char ch;
  char string[20];
  uint32_t n;
  Clock_Init48MHz();  // makes SMCLK=12 MHz
  UART0_Initprintf(); // initialize UART and printf
  UART0_OutString("\nTest program for UART driver\n\rUART0_OutChar examples\n");
  for(ch='A'; ch<='Z'; ch=ch+1){// print the uppercase alphabet
    UART0_OutChar(ch);
  }
  UART0_OutChar(LF);
  for(ch='a'; ch<='z'; ch=ch+1){// print the lowercase alphabet
    UART0_OutChar(ch);
  }
  BookExamples();
  while(1){
    UART0_OutString("InString: ");
    UART0_InString(string,19); // user enters a string
    UART0_OutString("\r\nOutString="); UART0_OutString(string); UART0_OutChar(LF);

    UART0_OutString("\r\nInUDec: ");   n=UART0_InUDec();
    UART0_OutString("\r\n OutUDec=");  UART0_OutUDec(n); UART0_OutChar(LF);
    UART0_OutString("\r\n OutUFix1="); UART0_OutUFix1(n); UART0_OutChar(LF);
    UART0_OutString("\r\n OutUFix2="); UART0_OutUFix2(n); UART0_OutChar(LF);
    printf("\r\n Using printf= %d, %2d.%.1d,\n",n,n/10,n%10);

    UART0_OutString("InUHex: ");   n=UART0_InUHex();
    UART0_OutString("\r\n OutUHex=");  UART0_OutUHex(n); UART0_OutChar(LF);
    printf(" Using printf= %#x\n",n);

  }
}


// TExaSmain.c
// Runs on MSP432
// Basic TExaS scope operation
// a 10 kHz 8-bit oscilloscope on J3.26/P4.4/A9
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

// This main program outputs a squarewave on P4.5
// TExaS scope uses P4.4 as input to scope
// To see the squarewave connect P4.4 to P4.5

#include <stdint.h>
#include "msp.h"
#include "..\inc\TExaS.h"
#include "..\inc\Clock.h"
#include "..\inc\SysTick.h"
#include "..\inc\LaunchPad.h"
int scopeMain(void){ //scopeMain(void){
  Clock_Init48MHz();  // makes bus clock 48 MHz
  TExaS_Init(SCOPE);
  P4->SEL0 &= ~0x20;  // configure P4.5 GPIO output
  P4->SEL1 &= ~0x20;
  P4->DIR |= 0x20;    // P4.5 output
  while(1){
    P4->OUT ^= 0x20;  // toggle
    Clock_Delay1us(1000); // wait 1 ms
  }
}

//int LogicAnalyzerMain(void){
int main(void){
uint32_t status,delay,data;
  Clock_Init48MHz(); // makes bus clock 48 MHz
  LaunchPad_Init();  // use buttons to step through frequencies
  TExaS_Init(LOGICANALYZER_P1);
  data = 0;
  while(1){
    status = LaunchPad_Input();
    switch(status){           // switches are negative logic on P1.1 and P1.4
      case 0x00: delay=1000; break;  // neither switch pressed
      case 0x01: delay=2000; break;  // SW1 pressed
      case 0x02: delay=3000; break;  // SW2 pressed
      case 0x03: delay=4000; break;  // both switches pressed
      //default: break;
    }
    Clock_Delay1us(delay);
    data = data ^0x01;
    LaunchPad_LED(data); // toggle red LED
  }
}



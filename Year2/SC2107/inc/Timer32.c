// Timer32.c
// Runs on MSP432
// Use Timer32 in periodic mode to request interrupts at a particular
// period.
// Daniel Valvano
// August 13, 2017

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
#include "msp.h"
#include "../inc/Timer32.h"

void (*PeriodicTask32)(void);   // user function

// ***************** Timer32_1_Init ****************
// Activate Timer32 Timer 1 interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in units (1/(bus clock)/div), 32 bits
//          div is clock divider for Timer32 Timer 1
//            T32DIV1   for input clock divider /1
//            T32DIV16  for input clock divider /16
//            T32DIV256 for input clock divider /256
// Outputs: none
void Timer32_Init(void(*task)(void), uint32_t period, enum timer32divider div){
  PeriodicTask32 = task;             // user function
  TIMER32_1->LOAD = (period - 1);    // timer reload value
  TIMER32_1->INTCLR = 0x00000001;    // clear Timer32 Timer 1 interrupt
  // bits31-8=X...X,   reserved
  // bit7=1,           timer enable
  // bit6=1,           timer in periodic mode
  // bit5=1,           interrupt enable
  // bit4=X,           reserved
  // bits3-2=??,       input clock divider according to parameter
  // bit1=1,           32-bit counter
  // bit0=0,           wrapping mode
  TIMER32_1->CONTROL = 0x000000E2|div;
// interrupts enabled in the main program after all devices initialized
  NVIC->IP[6] = (NVIC->IP[6]&0xFFFF00FF)|0x00004000; // priority 2
  NVIC->ISER[0] = 0x02000000;         // enable interrupt 25 in NVIC
}

void T32_INT1_IRQHandler(void){
  TIMER32_1->INTCLR = 0x00000001;  // acknowledge Timer32 Timer 1 interrupt
  (*PeriodicTask32)();               // execute user task
}

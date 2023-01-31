// TimerA0.c
// Runs on MSP432
// Use Timer A1 in periodic mode to request interrupts at a particular
// period.
// Daniel Valvano
// July 5, 2017

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


void (*TimerA0Task)(void);   // user function

// ***************** TimerA0_Init ****************
// Activate Timer A0 interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in units (24/SMCLK), 16 bits
// Outputs: none
void TimerA0_Init(void(*task)(void), uint16_t period){
  TimerA0Task = task;             // user function
  TIMER_A0->CTL &= ~0x0030;       // halt Timer A0
  // bits15-10=XXXXXX, reserved
  // bits9-8=10,       clock source to SMCLK
  // bits7-6=10,       input clock divider /4
  // bits5-4=00,       stop mode
  // bit3=X,           reserved
  // bit2=0,           set this bit to clear
  // bit1=0,           no interrupt on timer
  TIMER_A0->CTL = 0x0280;
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
  TIMER_A0->CCTL[0] = 0x0010;
  TIMER_A0->CCR[0] = (period - 1);   // compare match value
  TIMER_A0->EX0 = 0x0005;    // configure for input clock divider /6
// interrupts enabled in the main program after all devices initialized
  NVIC->IP[2] = (NVIC->IP[2]&0xFFFFFF00)|0x00000040; // priority 2
  NVIC->ISER[0] = 0x00000100;   // enable interrupt 8 in NVIC
  TIMER_A0->CTL |= 0x0014;      // reset and start Timer A1 in up mode
}


// ------------TimerA0_Stop------------
// Deactivate the interrupt running a user task periodically.
// Input: none
// Output: none
void TimerA0_Stop(void){
  TIMER_A0->CTL &= ~0x0030;       // halt Timer A0
  NVIC->ICER[0] = 0x00000100;     // disable interrupt 8 in NVIC
}


void TA0_0_IRQHandler(void){
  TIMER_A0->CCTL[0] &= ~0x0001; // acknowledge capture/compare interrupt 0
  (*TimerA0Task)();             // execute user task
}

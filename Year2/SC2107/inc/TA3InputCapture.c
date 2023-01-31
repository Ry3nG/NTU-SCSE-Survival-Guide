// TA3InputCapture.c
// Runs on MSP432
// Use Timer A3 in capture mode to request interrupts on rising
// edges of P10.4 (TA3CCP0) and P8.2 (TA3CCP2) and call user
// functions.
// Daniel Valvano
// May 30, 2017

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

// external signal connected to P8.2 (TA3CCP2) (trigger on rising edge)
// external signal connected to P10.4 (TA3CCP0) (trigger on rising edge)

#include <stdint.h>
#include "msp.h"

#define RSLK_MAX 1

void ta3dummy(uint16_t t){};       // dummy function
void (*CaptureTask0)(uint16_t time) = ta3dummy;// user function
void (*CaptureTask2)(uint16_t time) = ta3dummy;// user function

//------------TimerA3Capture_Init------------
// Initialize Timer A3 in edge time mode to request interrupts on
// the rising edges of P10.4 (TA3CCP0) and P8.2 (TA3CCP2).  The
// interrupt service routines acknowledge the interrupt and call
// a user function.
// Input: task0 is a pointer to a user function called when P10.4 (TA3CCP0) edge occurs
//              parameter is 16-bit up-counting timer value when P10.4 (TA3CCP0) edge occurred (units of 0.083 usec)
//        task2 is a pointer to a user function called when P8.2 (TA3CCP2) edge occurs
//              parameter is 16-bit up-counting timer value when P8.2 (TA3CCP2) edge occurred (units of 0.083 usec)
// Output: none
// Assumes: low-speed subsystem master clock is 12 MHz
// P8.2 -> TA3.CCI2A; P10.4 -> TA3.CCI0A

void TimerA3Capture_Init(void(*task0)(uint16_t time), void(*task2)(uint16_t time)){
  // write this as part of lab 4
    CaptureTask0 = task0;              // user function
    CaptureTask2 = task2;              // user function
#if (RSLK_MAX==0)
    // initialize P8.2 and make it input (P8.2 TA3CCI2A)
    P8->SEL0 |= 0x04;
    P8->SEL1 &= ~0x04;                 // configure P8.2 to TA3CCI2A
    P8->DIR &= ~0x04;                  // make P8.2 in
    // initialize P10.4 and make it input (P10.4 TA3CCI0A)
    P10->SEL0 |= 0x10;
    P10->SEL1 &= ~0x10;                 // configure P8.2 to TA3CCI0A
    P10->DIR &= ~0x10;                  // make P8.2 in
#else
    // initialize P10.4 and P10.5 and make them input (P10.4 TA3CCI0A, P10.5 TA3CCI1A)
    P10->SEL0 |= 0x30;
    P10->SEL1 &= ~0x30;                 // configure P8.2 to TA3CCI0A
    P10->DIR &= ~0x30;                  // make P8.2 in
#endif
    TIMER_A3->CTL &= ~0x0030;               // halt Timer A3
    // bits15-10=XXXXXX, reserved
    // bits9-8=10,       clock source to SMCLK
    // bits7-6=00,       input clock divider /1
    // bits5-4=00,       stop mode
    // bit3=X,           reserved
    // bit2=0,           set this bit to clear
    // bit1=0,           interrupt disable
    // bit0=0,           clear interrupt pending
    TIMER_A3->CTL = 0x0200;
    // bits15-14=01,     capture on rising edge
    // bits13-12=00,     capture/compare input on CCI2A
    // bit11=1,          synchronous capture source
    // bit10=X,          synchronized capture/compare input
    // bit9=X,           reserved
    // bit8=1,           capture mode
    // bits7-5=XXX,      output mode
    // bit4=1,           enable capture/compare interrupt
    // bit3=X,           read capture/compare input from here
    // bit2=X,           output this value in output mode 0
    // bit1=X,           capture overflow status
    // bit0=0,           clear capture/compare interrupt pending
#if (RSLK_MAX==0)
    TIMER_A3->CCTL[2] = 0x4910;
#else
    TIMER_A3->CCTL[1] = 0x4910;
#endif

    // bits15-14=01,     capture on rising edge
    // bits13-12=00,     capture/compare input on CCI0A
    // bit11=1,          synchronous capture source
    // bit10=X,          synchronized capture/compare input
    // bit9=X,           reserved
    // bit8=1,           capture mode
    // bits7-5=XXX,      output mode
    // bit4=1,           enable capture/compare interrupt
    // bit3=X,           read capture/compare input from here
    // bit2=X,           output this value in output mode 0
    // bit1=X,           capture overflow status
    // bit0=0,           clear capture/compare interrupt pending
    TIMER_A3->CCTL[0] = 0x4910;

    // configure for input clock divider /1
    TIMER_A3->EX0 &= ~0x0007;

    // priority 2 for TA3.0 and TA3.x. Four INTs per IP[] register. Only MS 3 bits valid.
    NVIC->IP[2] = (NVIC->IP[3]&0x0000FFFF)|0x40400000;

    // interrupts enabled in the main program after all devices initialized
    NVIC->ISER[0] |= 0x0000C000; // enable interrupt 15 (TA3.x) and 14 (TA3.0) in NVIC

    TIMER_A3->CTL |= 0x0024;        // reset and start Timer A3 in continuous up mode
    // bits15-10=XXXXXX, reserved
    // bits9-8=10,       clock source to SMCLK
    // bits7-6=00,       input clock divider /1
    // bits5-4=10,       continuous count up mode
    // bit3=X,           reserved
    // bit2=1,           set this bit to clear
    // bit1=0,           interrupt disable (no interrupt on rollover)
    // bit0=0,           clear interrupt pending

}

void TA3_0_IRQHandler(void){
  // write this as part of lab 4
    TIMER_A3->CCTL[0] &= ~0x0001;             // acknowledge capture/compare interrupt 0
    (*CaptureTask0)(TIMER_A3->CCR[0]);         // execute user task
}

void TA3_N_IRQHandler(void){
  // write this as part of lab 4
#if (RSLK_MAX==0)
    TIMER_A3->CCTL[2] &= ~0x0001;             // acknowledge capture/compare interrupt 2
    (*CaptureTask2)(TIMER_A3->CCR[2]);         // execute user task
#else
    TIMER_A3->CCTL[1] &= ~0x0001;             // acknowledge capture/compare interrupt 2
    (*CaptureTask2)(TIMER_A3->CCR[1]);         // execute user task
#endif
}


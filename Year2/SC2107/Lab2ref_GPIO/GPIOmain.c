// GPIOmain.c
// Runs on MSP432
// Initialize four GPIO pins as outputs.  Continually generate output to
// drive simulated stepper motor.
// Daniel Valvano
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

// P4.3 is an output to LED3, negative logic
// P4.2 is an output to LED2, negative logic
// P4.1 is an output to LED1, negative logic
// P4.0 is an output to LED0, negative logic

#include <stdint.h>
#include "msp.h"
#include "..\inc\Clock.h"
#include "..\inc\TExaS.h"

void GPIO_Init(void){
  // initialize P4.3-P4.0 and make them outputs
  P4->SEL0 &= ~0x0F;
  P4->SEL1 &= ~0x0F;            // configure stepper motor/LED pins as GPIO
  P4->DIR |= 0x0F;              // make stepper motor/LED pins out
}

int main(void){
  Clock_Init48MHz();
  GPIO_Init();
  TExaS_Init(LOGICANALYZER_P4);
  while(1){
    P4->OUT = (P4->OUT&~0x0F)|10; // 1010, LED is 0101
    Clock_Delay1ms(100);          // 100ms delay 10 steps/sec
    P4->OUT = (P4->OUT&~0x0F)|9;  // 1001, LED is 0110
    Clock_Delay1ms(100);          // 100ms delay 10 steps/sec
    P4->OUT = (P4->OUT&~0x0F)|5;  // 0101, LED is 1010
    Clock_Delay1ms(100);          // 100ms delay 10 steps/sec
    P4->OUT = (P4->OUT&~0x0F)|6;  // 0110, LED is 1001
    Clock_Delay1ms(100);          // 100ms delay 10 steps/sec
  }
}

// Program 2.13 from Volume 2
#define STEPPER  (*((volatile uint8_t *)0x40004C23))  /* Port 4 Output, bits 3-0 are stepper motor */
static void step(uint8_t n){
  STEPPER = (STEPPER&~0x0F)|n;  // output to stepper causing it to step once
  Clock_Delay1ms(100);          // 100ms delay 10 steps/sec
}
int main2(void){ // reset clears P4REN, P4DS, P4SEL0, P4SEL1
  Clock_Init48MHz();
  TExaS_Init(LOGICANALYZER_P4);
  GPIO_Init();
  while(1){
    step(5);  // motor is 0101
    step(6);  // motor is 0110
    step(10); // motor is 1010
    step(9);  // motor is 1001
  }
}

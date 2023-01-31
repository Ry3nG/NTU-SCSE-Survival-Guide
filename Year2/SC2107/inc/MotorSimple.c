// MotorSimple.c

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

// Sever VCCMD=VREG jumper on Motor Driver and Power Distribution Board and connect VCCMD to 3.3V.
//   This makes P3.7 and P3.6 low power disables for motor drivers.  0 to sleep/stop.
// Sever nSLPL=nSLPR jumper.
//   This separates P3.7 and P3.6 allowing for independent control
// Left motor direction connected to P1.7 (J2.14)
// Left motor PWM connected to P2.7/TA0CCP4 (J4.40)
// Left motor enable connected to P3.7 (J4.31)
// Right motor direction connected to P1.6 (J2.15)
// Right motor PWM connected to P2.6/TA0CCP3 (J4.39)
// Right motor enable connected to P3.6 (J2.11)

#include <stdint.h>
#include "msp.h"
#include "../inc/SysTick.h"
#include "../inc/Bump.h"

// Time delay using busy wait.
// assumes 48 MHz bus clock
void SysTick_Wait1us(uint32_t delay){
  uint32_t i;
  for(i=0; i<delay; i++){
    SysTick_Wait(48);  // wait 10ms (assumes 48 MHz clock)
  }
}

void Motor_InitSimple(void){
// Initializes the 6 GPIO lines and puts driver to sleep
// Returns right away
// initialize P1.6 and P1.7 and make them outputs

    P3->SEL0 &= ~0xC0;
    P3->SEL1 &= ~0xC0;    // 1) configure P1.6, 1.7 as GPIO
    P3->DIR |= 0xC0;      // 2) make P1.6, 1.7 output
    P3->OUT &= ~0xC0;     // 3) output LOW

    P1->SEL0 &= ~0xC0;
    P1->SEL1 &= ~0xC0;    // 1) configure P1.6, 1.7 as GPIO
    P1->DIR |= 0xC0;      // 2) make P1.6, 1.7 output
    P1->OUT &= ~0xC0;     // 3) output LOW

    P2->SEL0 &= ~0xC0;
    P2->SEL1 &= ~0xC0;    // 1) configure P1.6, 1.7 as GPIO
    P2->DIR |= 0xC0;      // 2) make P1.6, 1.7 output
    P2->OUT &= ~0xC0;     // 3) output LOW
}

void Motor_StopSimple(void){
// Stops both motors, puts driver to sleep
// Returns right away
  P1->OUT &= ~0xC0;
  P2->OUT &= ~0xC0;   // off
  P3->OUT &= ~0xC0;   // low current sleep mode
}
void Motor_ForwardSimple(uint16_t duty, uint32_t time){
// Drives both motors forward at duty (100 to 9900)
// Runs for time duration (units=10ms), and then stops
// Stop the motors and return if any bumper switch is active
// Returns after time*10ms or if a bumper switch is hit

uint32_t counter;
//uint8_t temp;
    counter = time;
    // Forward direction
    P1->OUT &= ~0xC0;
    //temp=Bump_Read();
    while(counter>0 && Bump_Read()==0x3F){
    //while(counter>0){
        // Enable L and R motor
        P3->OUT |= 0xC0;
        // PWM HIGH
        P2->OUT |= 0xC0;
        SysTick_Wait1us(duty);
        //PWM LOW
        P2->OUT &= ~0xC0;
        SysTick_Wait1us(10000-duty);
        counter--;
    }
    Motor_StopSimple();
}
void Motor_BackwardSimple(uint16_t duty, uint32_t time){
// Drives both motors backward at duty (100 to 9900)
// Runs for time duration (units=10ms), and then stops
// Runs even if any bumper switch is active
// Returns after time*10ms

    // write this as part of Lab 12
    uint32_t counter;

        counter = time;
        // Backward direction
        P1->OUT |= 0xC0;

        while(counter>0 && Bump_Read()==0x3F){
        //while(counter>0){
            // Enable L and R motor
            P3->OUT |= 0xC0;
            // PWM HIGH
            P2->OUT |= 0xC0;
            SysTick_Wait1us(duty);
            //PWM LOW
            P2->OUT &= ~0xC0;
            SysTick_Wait1us(10000-duty);
            counter--;
        }
        Motor_StopSimple();
}
void Motor_LeftSimple(uint16_t duty, uint32_t time){
// Drives just the left motor forward at duty (100 to 9900)
// Right motor is stopped (sleeping)
// Runs for time duration (units=10ms), and then stops
// Stop the motor and return if any bumper switch is active
// Returns after time*10ms or if a bumper switch is hit

    uint32_t counter;

        counter = time;
        // Forward direction
        P1->OUT &= ~0xC0;

        while(counter>0 && Bump_Read()==0x3F){
        //while(counter>0){
            // Enable L motor
            P3->OUT |= 0x80;
            // PWM HIGH
            P2->OUT |= 0x80;
            SysTick_Wait1us(duty);
            //PWM LOW
            P2->OUT &= ~0x80;
            SysTick_Wait1us(10000-duty);
            counter--;
        }
        Motor_StopSimple();

}
void Motor_RightSimple(uint16_t duty, uint32_t time){
// Drives just the right motor forward at duty (100 to 9900)
// Left motor is stopped (sleeping)
// Runs for time duration (units=10ms), and then stops
// Stop the motor and return if any bumper switch is active
// Returns after time*10ms or if a bumper switch is hit

    uint32_t counter;

        counter = time;
        // Forward direction
        P1->OUT &= ~0xC0;

        while(counter>0 && Bump_Read()==0x3F){
        //while(counter>0){
            // Enable R motor
            P3->OUT |= 0x40;
            // PWM HIGH
            P2->OUT |= 0x40;
            SysTick_Wait1us(duty);
            //PWM LOW
            P2->OUT &= ~0x40;
            SysTick_Wait1us(10000-duty);
            counter--;
        }
        Motor_StopSimple();

}



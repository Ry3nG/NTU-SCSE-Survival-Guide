// Motor.c
// Runs on MSP432
// Provide mid-level functions that initialize ports and
// set motor speeds to move the robot. Lab 13 starter
// Daniel Valvano
// July 8, 2017

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
#include "../inc/CortexM.h"
#include "../inc/PWM.h"

#define PERIOD 7500

#define RSLK_MAX 1
// *******Lab 3 solution*******

// ------------Motor_Init------------
// Initialize GPIO pins for output, which will be
// used to control the direction of the motors and
// to enable or disable the drivers.
// The motors are initially stopped, the drivers
// are initially powered down, and the PWM speed
// control is uninitialized.
// Input: none
// Output: none
void Motor_Init(void){
  // write this as part of Lab 3
    P3->SEL0 &= ~0xC0;
    P3->SEL1 &= ~0xC0;    // 1) configure P1.6, 1.7 as GPIO
    P3->DIR |= 0xC0;      // 2) make P1.6, 1.7 output
    P3->OUT &= ~0xC0;     // 3) output LOW
#if (RSLK_MAX==0)
    P1->SEL0 &= ~0xC0;
    P1->SEL1 &= ~0xC0;    // 1) configure P1.6, 1.7 as GPIO
    P1->DIR |= 0xC0;      // 2) make P1.6, 1.7 output
    P1->OUT &= ~0xC0;     // 3) output LOW
#else
    P5->SEL0 &= ~0x30;
    P5->SEL1 &= ~0x30;    // 1) configure P5.5, 5.4 as GPIO
    P5->DIR |= 0x30;      // 2) make P5.5, 5.4 output
    P5->OUT &= ~0x30;     // 3) output LOW
#endif
    P2->SEL0 &= ~0xC0;
    P2->SEL1 &= ~0xC0;    // 1) configure P1.6, 1.7 as GPIO
    P2->DIR |= 0xC0;      // 2) make P1.6, 1.7 output
    P2->OUT &= ~0xC0;     // 3) output LOW
  
    PWM_Init34(PERIOD, 0, 0);

}

// ------------Motor_Stop------------
// Stop the motors, power down the drivers, and
// set the PWM speed control to 0% duty cycle.
// Input: none
// Output: none
void Motor_Stop(void){
  // write this as part of Lab 3
    P2->OUT &= ~0xC0;   // off
    P3->OUT &= ~0xC0;   // low current sleep mode
    PWM_Duty3(0);
    PWM_Duty4(0);
}

// ------------Motor_Forward------------
// Drive the robot forward by running left and
// right wheels forward with the given duty
// cycles.
// Input: leftDuty  duty cycle of left wheel (0 to 14,998)
//        rightDuty duty cycle of right wheel (0 to 14,998)
// Output: none
// Assumes: Motor_Init() has been called
void Motor_Forward(uint16_t leftDuty, uint16_t rightDuty){ 
  // write this as part of Lab 3

    // Forward direction
#if (RSLK_MAX==0)
    P1->OUT &= ~0xC0;
#else
    P5->OUT &= ~0x30;
#endif

    PWM_Duty3(leftDuty);
    PWM_Duty4(rightDuty);

    //Enable L and R motor
    P3->OUT |= 0xC0;
  
}

// ------------Motor_Right------------
// Turn the robot to the right by running the
// left wheel forward and the right wheel
// backward with the given duty cycles.
// Input: leftDuty  duty cycle of left wheel (0 to 14,998)
//        rightDuty duty cycle of right wheel (0 to 14,998)
// Output: none
// Assumes: Motor_Init() has been called
void Motor_Right(uint16_t leftDuty, uint16_t rightDuty){ 
  // write this as part of Lab 3
    // Right direction
#if (RSLK_MAX == 0)
    P1->OUT &= ~0x80;
    P1->OUT |= 0x40;
#else
    P5->OUT &= ~0x10;
    P5->OUT |= 0x20;
#endif

    PWM_Duty3(leftDuty);
    PWM_Duty4(rightDuty);

    //Enable L and R motor
    P3->OUT |= 0xC0;

}

// ------------Motor_Left------------
// Turn the robot to the left by running the
// left wheel backward and the right wheel
// forward with the given duty cycles.
// Input: leftDuty  duty cycle of left wheel (0 to 14,998)
//        rightDuty duty cycle of right wheel (0 to 14,998)
// Output: none
// Assumes: Motor_Init() has been called
void Motor_Left(uint16_t leftDuty, uint16_t rightDuty){ 
  // write this as part of Lab 3
    // Right direction
#if (RSLK_MAX == 0)
    P1->OUT &= ~0x40;
    P1->OUT |= 0x80;
#else
    P5->OUT &= ~0x20;
    P5->OUT |= 0x10;
#endif
    PWM_Duty3(leftDuty);
    PWM_Duty4(rightDuty);

    //Enable L and R motor
    P3->OUT |= 0xC0;

}

// ------------Motor_Backward------------
// Drive the robot backward by running left and
// right wheels backward with the given duty
// cycles.
// Input: leftDuty  duty cycle of left wheel (0 to 14,998)
//        rightDuty duty cycle of right wheel (0 to 14,998)
// Output: none
// Assumes: Motor_Init() has been called
void Motor_Backward(uint16_t leftDuty, uint16_t rightDuty){ 
  // write this as part of Lab 3
    // Backward direction
#if (RSLK_MAX==0)
    P1->OUT |= 0xC0;
#else
    P5->OUT |= 0x30;
#endif
    PWM_Duty3(leftDuty);
    PWM_Duty4(rightDuty);

    //Enable L and R motor
    P3->OUT |= 0xC0;

}

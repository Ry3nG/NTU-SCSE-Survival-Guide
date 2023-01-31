// Ultrasound.c
// Runs on MSP432
// Provide mid-level functions that initialize ports, start
// an ultrasonic sensor measurement, and finish an ultrasonic
// sensor measurement using the HC-SR04 ultrasonic distance
// sensor.
// Daniel Valvano
// May 2, 2017

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

// Pololu #3543 Vreg (5V regulator output) connected to HC-SR04 Vcc (+5V) and MSP432 +5V (J3.21)
// 22k top connected to HC-SR04 Echo (digital output from sensor)
// 22k bottom connected to 33k top and MSP432 P6.6 (J4.36) (digital input to MSP432)
// 33k bottom connected to ground
// Pololu ground connected to HC-SR04 ground and MSP432 ground (J3.22)
// MSP432 P5.6 (J4.37) (digital output from MSP432) connected to HC-SR04 trigger

#include <stdint.h>
#include "../inc/Clock.h"
#include "../inc/TA2InputCapture.h"
#include "msp.h"

uint16_t Ultrasound_FirstTime, Ultrasound_SecondTime;
int Ultrasound_Count = 0;          // incremented with every interrupt
int Ultrasound_Valid = 0;          // measurement valid if non-zero
int Ultrasound_Busy = 0;           // measurement in progress if non-zero

void ultrasoundint(uint16_t currenttime){
  if((Ultrasound_Count%2) == 0){
    // this is the first edge in the measurement
    Ultrasound_FirstTime = currenttime;
    Ultrasound_Valid = 0;
  }else{
    // this is the second edge in the measurement
    Ultrasound_SecondTime = currenttime;
    Ultrasound_Valid = 1;
    Ultrasound_Busy = 0;
  }
  Ultrasound_Count = Ultrasound_Count + 1;
}

// ------------Ultrasound_Init------------
// Initialize a GPIO pin for output, which will be
// used to trigger the ultrasonic sensor.
// Initialize the input capture interface, which
// will be used to take the measurement.
// Input: none
// Output: none
void Ultrasound_Init(void){
  // initialize P6.6 and make it GPIO
  P6->SEL0 &= ~0x40;
  P6->SEL1 &= ~0x40;               // configure P6.6 as GPIO
  P6->DIR |= 0x40;                 // make P6.6 out
  P6->OUT &= ~0x40;
  TimerA2Capture_Init(&ultrasoundint);
}

// ------------Ultrasound_Start------------
// Start a measurement using the ultrasonic sensor.
// If a measurement is currently in progress, return
// immediately.
// Input: none
// Output: none
// Assumes: Ultrasound_Init() has been called
// Assumes: Clock_Init48MHz() has been called
void Ultrasound_Start(void){
  if(Ultrasound_Busy == 0){
    // no measurement is in progress, so start one
    Ultrasound_Busy = 1;
    P6->OUT |= 0x40;
    Clock_Delay1us(10);
    P6->OUT &= ~0x40;
  }
}

// ------------Ultrasound_End------------
// Query the HC-SR04 ultrasonic distance sensor for a
// measurement.  If no measurement is currently in
// progress, start one and return zero immediately.
// If the measurement is not yet complete, return
// zero immediately.  If the measurement is complete,
// store the result in the pointers provided and
// return one.
// Input: distMm is pointer to store measured distance (units mm)
//        distIn is pointer to store measured distance (units 10*in)
// Output: one if measurement is ready and pointers are valid
//         zero if measurement is not ready and pointers unchanged
// Assumes: Ultrasound_Init() has been called
// Assumes: Clock_Init48MHz() has been called
int Ultrasound_End(uint16_t *distMm, uint16_t *distIn){
  if((Ultrasound_Busy == 0) && (Ultrasound_Valid == 0)){
    // no measurement is in progress, and no measurement is finished, so start one
    Ultrasound_Start();
    return 0;
  }
  if((Ultrasound_Busy != 0) && (Ultrasound_Valid == 0)){
    // measurement is in progress, but it is not finished
    return 0;
  }
  // measurement is ready
  *distMm = ((uint16_t)(Ultrasound_SecondTime - Ultrasound_FirstTime))/70;
  *distIn = ((uint16_t)(Ultrasound_SecondTime - Ultrasound_FirstTime))/178;
  return 1;
}

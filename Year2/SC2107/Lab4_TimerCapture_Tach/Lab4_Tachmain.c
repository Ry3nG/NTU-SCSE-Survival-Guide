// Lab16_Tachmain.c
// Runs on MSP432
// Test the operation of the tachometer by implementing
// a simple DC motor speed controller.
// Daniel Valvano
// September 5, 2017

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

// Pololu #3542 Romi Encoder connected to Pololu #3543 Motor Driver and Power Distribution Board
//   This connects motor, power, encoders, and grounds.  Kit includes this hardware.  See images.
// Sever VPU = VREG jumper on Motor Driver and Power Distribution Board and connect VPU to 3.3V.
//   This is necessary because MSP432 inputs are not 5V tolerant.
// Left Encoder A connected to P8.2 (J5)
// Left Encoder B connected to P9.2 (J5)
// Right Encoder A connected to P10.4 (J5)
// Right Encoder B connected to P10.5 (J5)

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

// See Bump.c for bumper connections (Port 8 or Port 4)

#include <stdint.h>
#include "msp.h"
#include "../inc/Clock.h"
#include "../inc/CortexM.h"
#include "../inc/LaunchPad.h"
#include "../inc/Motor.h"
#include "../inc/Tachometer.h"
#include "../inc/TA3InputCapture.h"
#include "../inc/TExaS.h"
#include "../inc/Bump.h"
#include "../inc/UART0.h"

#define P2_4 (*((volatile uint8_t *)(0x42098070)))
#define P2_3 (*((volatile uint8_t *)(0x4209806C)))
#define P2_2 (*((volatile uint8_t *)(0x42098068)))
#define P2_1 (*((volatile uint8_t *)(0x42098064)))
#define P2_0 (*((volatile uint8_t *)(0x42098060)))

//#define PERIOD 1000  // must be even

uint16_t Period0;              // (1/SMCLK) units = 83.3 ns units
uint16_t First0=0;             // Timer A3 first edge, P10.4
uint32_t Done0=0;              // set each rising

uint16_t Period2;              // (1/SMCLK) units = 83.3 ns units
uint16_t First2=0;             // Timer A3 first edge, P8.2
uint32_t Done2=0;              // set each rising

// max period is (2^16-1)*83.3 ns = 5.4612 ms
// min period determined by time to run ISR, which is about 1 us
void PeriodMeasure0(uint16_t time){
  Period0 = (time - First0)&0xFFFF; // 16 bits, 83.3 ns resolution
  First0 = time;                    // setup for next
  Done0++;
}

// max period is (2^16-1)*83.3 ns = 5.4612 ms
// min period determined by time to run ISR, which is about 1 us
void PeriodMeasure2(uint16_t time){
  Period2 = (time - First2)&0xFFFF; // 16 bits, 83.3 ns resolution
  First2 = time;                    // setup for next
  Done2++;
}

void TimedPause(uint32_t time){
  Clock_Delay1ms(time);         // run for a while and stop
  Motor_Stop();
  while(LaunchPad_Input()==0);  // wait for touch
  while(LaunchPad_Input());     // wait for release
}

uint32_t main_count=0;

void main(void){
    DisableInterrupts();
    Clock_Init48MHz();  // 48 MHz clock; 12 MHz Timer A clock
    LaunchPad_Init();   // built-in switches and LEDs
    UART0_Init();       // initialize UART0 115,200 baud rate
    Motor_Init();       // configure motor
    TimerA3Capture_Init(&PeriodMeasure0,&PeriodMeasure2);
    TimedPause(500);
    Motor_Forward(3000,3000);
    EnableInterrupts();
    while(1){
      WaitForInterrupt();
      main_count++;
      if(main_count%1000){
          UART0_OutString("Period0 = ");UART0_OutUDec5(Period0);UART0_OutString(" Period2 = ");UART0_OutUDec5(Period2);UART0_OutString(" \r\n");
      }
    }
}

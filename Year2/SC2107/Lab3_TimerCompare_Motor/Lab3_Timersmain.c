// Lab3_Timersmain.c

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
// Negative logic bump sensors
// P8.7 Bump5
// P8.6 Bump4
// P8.5 Bump3
// P8.4 Bump2
// P8.3 Bump1
// P8.0 Bump0
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
#include "msp.h"
#include "..\inc\bump.h"
#include "..\inc\Clock.h"
#include "..\inc\SysTick.h"
#include "..\inc\CortexM.h"
#include "..\inc\LaunchPad.h"
#include "..\inc\Motor.h"
#include "..\inc\TimerA1.h"
#include "..\inc\TExaS.h"
#include "..\inc\Reflectance.h"

volatile uint8_t RESULT;

void (*Port4Task)(void);

volatile uint8_t reflectance_data, bump_data;

// Driver test
void TimedPause(uint32_t time)
{
    Clock_Delay1ms(time);          // run for a while and stop
    Motor_Stop();
    while (LaunchPad_Input() == 0)
        ;  // wait for touch
    while (LaunchPad_Input())
        ;     // wait for release
}

// Test of Periodic interrupt
#define REDLED (*((volatile uint8_t *)(0x42098060)))
#define BLUELED (*((volatile uint8_t *)(0x42098068)))
uint32_t Time;
void Task(void)
{
#if 0
    REDLED ^= 0x01;       // toggle P2.0
    REDLED ^= 0x01;// toggle P2.0
    Time = Time + 1;
    REDLED ^= 0x01;// toggle P2.0
#endif

#if 1
    volatile static uint8_t count = 0;

    count++;
    if (count == 10)
        count = 0;

    if (Bump_Read() != 0x3F)
    {
        P3->OUT &= ~0xC0;   // low current sleep mode
    }
    else
    {
        P3->OUT |= 0xC0;   // Wake up motor
    }

#endif
}

void Bump_Read_void(void)
{
    // write this as part of Lab 3
    // Pack the 6 valid bits in the value read from the input data
    // register to occupy 6 lower order bits of the result variable.
    uint8_t bump0, bump1, bump2, bump3, bump4, bump5, result;
    result = 0;
    bump0 = (P4->IN & 0b00000001);
    bump1 = (P4->IN & 0b00000100) >> 1;
    bump2 = (P4->IN & 0b00001000) >> 1;

    bump3 = (P4->IN & 0b00100000) >> 2;
    bump4 = (P4->IN & 0b01000000) >> 2;
    bump5 = (P4->IN & 0b10000000) >> 2;
    result = bump0 + bump1 + bump2 + bump3 + bump4 + bump5;
    RESULT = result;
}
void PORT4_IRQHandler(void)
{
    //(*Port4Task)();
    bump_data = Bump_Read();
    P4->IFG &=0xED; // flag
}
void Bump_Init_Edge(void (*task)(void))
{
    // write this as part of Lab 3
    // Initialise GPIO related registers.
    // Registers: SEL0, SEL1, DIR, REN, OUT.
    Port4Task = task;
    P4->SEL0 &= ~0xED;
    P4->SEL1 &= ~0xED; // init GPIO
    P4->DIR &= ~0xED; // init as input
    P4->REN |= 0xED;  //enable pull up/down resistors
    P4->OUT |= 0xED;  //pull up

    P4->IES |= 0xED;
    P4->IFG &= ~0xED;
    P4->IE |= 0xED;

    NVIC->IP[9] = (NVIC->IP[9] & 0x00FFFFFF) | 0x40000000;
    NVIC->ISER[1] = 0x40;
}

int main(void)
{
    // Uses Timer generated PWM to move the robot
    // Uses TimerA1 to periodically
    // check the bump switches, stopping the robot on a collision

    Clock_Init48MHz();
    LaunchPad_Init(); // built-in switches and LEDs
    Bump_Init_Edge(&Bump_Read_void);// bump switches
    Motor_Init();     // your function
    TExaS_Init(LOGICANALYZER_P2);
    TimerA1_Init(&Task, 50000);  // 10 Hz
    EnableInterrupts();

    TimedPause(1000);
    RESULT = 0b00111111;
    while (1)
    {
        Motor_Forward(3000, 3000);  // your function
        WaitForInterrupt();

    }

    //TimedPause(1000);
    //Motor_Backward(3000,3000); // your function
    //TimedPause(1000);
    //Motor_Left(3000,3000);     // your function
    //TimedPause(1000);
    //Motor_Right(3000,3000);    // your function
    //TimedPause(1000);
}


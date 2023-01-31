// InputOutput.c
// Runs on MSP432
// Test the GPIO initialization functions by setting the LED
// color according to the status of the switches.
// Only SW1 makes color LED blue, and red LED on
// Only SW2 makes color LED red, and red LED on
// Both SW1 and SW2 makes color LED purple, and red LED on
// Neither SW1 or SW2 turns LEDs off

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

// built-in LED1 connected to P1.0
// negative logic built-in Button 1 connected to P1.1
// negative logic built-in Button 2 connected to P1.4
// built-in red LED connected to P2.0
// built-in green LED connected to P2.1
// built-in blue LED connected to P2.2
// Color    LED(s) Port2
// dark     ---    0
// red      R--    0x01
// blue     --B    0x04
// green    -G-    0x02
// yellow   RG-    0x03
// sky blue -GB    0x06
// white    RGB    0x07
// pink     R-B    0x05
#include <stdint.h>
#include "msp.h"
#include "..\inc\Clock.h"

#define BITBAND 0

#define SW1       0x02                  // on the left side of the LaunchPad board
#define SW2       0x10                  // on the right side of the LaunchPad board
#define RED       0x01
#define GREEN     0x02
#define BLUE      0x04

//Bit Band address of P2.2 (Blue), P2.1 (Green) and P2.0 (Red)
#define BLUEOUT     (*((volatile uint8_t *)(0x42098068)))
#define GREENOUT    (*((volatile uint8_t *)(0x42098064)))
#define REDOUT      (*((volatile uint8_t *)(0x42098060)))

//Function declaration
void Bit_Manipulation(void);
void Bit_ShiftExtract(void);
void Volatile_KeyWord(void);

//Initialise GPIO Port1 registers
void Port1_Init(void){
  P1->SEL0 = 0x00;
  P1->SEL1 = 0x00;                        // configure P1.4 and P1.1 as GPIO
  P1->DIR = 0x01;                         // make P1.4 and P1.1 in, P1.0 output
  P1->REN = 0x12;                         // enable pull resistors on P1.4 and P1.1
  P1->OUT = 0x12;                         // P1.4 and P1.1 are pull-up
}

//Read Port1 input data register
uint8_t Port1_Input(void){
  return (P1->IN&0x12);                   // read P1.4,P1.1 inputs
}

//Initialise GPIO Port2 registers
void Port2_Init(void){
  P2->SEL0 = 0x00;
  P2->SEL1 = 0x00;                        // configure P2.2-P2.0 as GPIO
  P2->DS = 0x07;                          // make P2.2-P2.0 high drive strength
  P2->DIR = 0x07;                         // make P2.2-P2.0 out
  P2->OUT = 0x00;                         // all LEDs off
}

//Output data to Port1 GPIO pins by writing to Port1 output data register
void Port1_Output(uint8_t data){        // write all of P1.0 outputs
  P1->OUT = (P1->OUT&0xFE)|data;
}

//Output data to Port2 GPIO pins by writing to Port2 output data register
void Port2_Output(uint8_t data){        // write all of P2 outputs
  P2->OUT = data;
}

int main(void){
  uint8_t status;

  Port1_Init();                         // initialize P1.1 and P1.4 and make them inputs (P1.1 and P1.4 built-in buttons)
                                        // initialize P1.0 as output to red LED
  Port2_Init();                         // initialize P2.2-P2.0 and make them outputs (P2.2-P2.0 built-in LEDs)

  Bit_Manipulation();
  Bit_ShiftExtract();

  while(1){
    status = Port1_Input();
    switch(status){                 // switches are negative logic on P1.1 and P1.4
      case 0x10:                    // SW1 pressed
#if (BITBAND==0)
        Port2_Output(BLUE);
#else
        BLUEOUT = 1;
#endif
        Port1_Output(1);
        break;
      case 0x02:                    // SW2 pressed
#if (BITBAND==0)
        Port2_Output(RED);
#else
        REDOUT = 1;
#endif
        Port1_Output(1);
        break;
      case 0x00:                    // both switches pressed
#if (BIT_BAND==0)
        Port2_Output(BLUE+RED);
#else
        REDOUT = 1;
        BLUEOUT= 1;
#endif
        Port1_Output(1);
        break;
      case 0x12:                    // neither switch pressed
        Port2_Output(0);
        Port1_Output(0);
        break;
    }
  }
}

/*
 * Function illustrate the concept of bit manipulation using a bit mask, to set and clear specific bits in
 * a target destination.
 * For this case the destination is the P2 output data register, which controls the logic of the output pins
 * in Port2. These three pins are connected to the RED, GREEN and BLUE led on hte MSP432 Launchpad.
 */

void Bit_Manipulation(void)
{
    /*
     * light up RED, GREN and BLUE LED sequentially.
     * Or-ing P1 output data reg with 0x1 result in bit0 being set to '1' and other bits are left unchanged.
     * Or-ing P1 output data reg with 0x2 result in bit1 being set to '1' and other bits are left unchanged.
     * Or-ing P1 output data reg with 0x4 result in bit2 being set to '1' and other bits are left unchanged.
     * Final result is P1->OUT bit0, 1 and 2 are set to '1'.  All three LEDS are lighted and colour is white
     * Caution: LED is very bright so dont look at it for too long.
     */
    P2->OUT |= 0x1;
    P2->OUT |= 0x2;
    P2->OUT |= 0x4;

    /*
     * To clear just bit 1, i.e. turn off GREEN LED to get a (RED+BLUE = PURPLE) colour.
     * '~' is a 1's complement operation, i.e. bitwise inversion.
     * Consider 8-bit binary system, 0x2 = 0000 0010, ~0x2 = 1111 1101.
     * Performing a bitwise AND operation (&) will result in bit1 of the
     * target register cleared to '0' and all other bits is left unchanged.
     */
    P2->OUT &= ~0x2;
    Clock_Delay1ms(1000);
    P2->OUT &=~0x7;

    Volatile_KeyWord();
}

/*
 * Function illustrate the concept of bit shifting and extraction using a bit mask.
 */

void Bit_ShiftExtract(void)
{
    volatile int test[]={0xA, 0xB, 0xC, 0xD, 0xE, 0xF};
    volatile int i, testbit, count=0;

    /*
     * Iterate through each element of the test[] array.
     * For each element, right shift the data by 2 bits and apply a 0x1 mask to extract bit0.
     * Assign the result to testbit variable.
     * increment count if testbit==1.
     */
    for (i=0;i<6;i++){
        testbit = (test[i]>>2)&0x1;
        if(testbit)count++;
    }
}

/*
 * Function illustrate the effect of volatile qualifier on the compiler/optimizer behaviour.
 */

void Volatile_KeyWord(void)
{
    //volatile int x;
    int x;
    //volatile int y, z;
    int y, z;

    x=1;
    y=2;

    if(x>0)z=y+x;
    else z=y-x;

    x=z;
}






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

#define SW1       0x02                  // on the left side of the LaunchPad board
#define SW2       0x10                  // on the right side of the LaunchPad board
#define RED       0x01
#define GREEN     0x02
#define BLUE      0x04

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

int main(void){ uint8_t status;

  Port1_Init();                         // initialize P1.1 and P1.4 and make them inputs (P1.1 and P1.4 built-in buttons)
                                        // initialize P1.0 as output to red LED
  Port2_Init();                         // initialize P2.2-P2.0 and make them outputs (P2.2-P2.0 built-in LEDs)
  while(1){
    status = Port1_Input();
    switch(status){                 // switches are negative logic on P1.1 and P1.4
      case 0x10:                    // SW1 pressed
        Port2_Output(BLUE);
        Port1_Output(1);
        break;
      case 0x02:                    // SW2 pressed
        Port2_Output(RED);
        Port1_Output(1);
        break;
      case 0x00:                    // both switches pressed
        Port2_Output(BLUE+RED);
        Port1_Output(1);
        break;
      case 0x12:                    // neither switch pressed
        Port2_Output(0);
        Port1_Output(0);
        break;
    }
  }
}


// GPIO.c
// Runs on MSP432
// Digital input/output from MSP432 LaunchPad to CC2650
// Jonathan Valvano
// February 23, 2017

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

#include "msp.h"
#include "GPIO.h"
// Legend    TI part number
// CC2650BP  BOOSTXL-CC2650MA
// CC2650LP  LAUNCHXL-CC2650
// MSP432    MSP-EXP432P401R
// TM4C123   EK-TM4C123GXL
// MKII      BOOSTXL-EDUMKII

#ifdef DEFAULT
// Option 4) Use this setup with CC2650BP without an MKII 
// Two board stack: CC2650BP+MSP432 
// Acceptable projects:
//     VerySimpleApplicationProcessor_MSP432
//     ApplicationProcessor_MSP432
// This runs with the default version of SNP that ships on the BOOSTXL-CC2650MA
// signal  MSP432                           CC2650BP       comment
//  3V3    J1.1  3.3V                       J1.1  3.3V     Power from MSP432 to CC2650BP 
//  GND    J2.20 ground                     J2.20 ground   Connect ground together
//  NRESET J4.35 TM4C123 PC6, MSP432 P6.7   J4.35          Reset from MSP432 to CC2650BP  
//  TX     J1.3  TM4C123 PB0, MSP432 P3.2   J1.3  DIO0_TXD UART from CC2650BP to MSP432  
//  RX     J1.4  TM4C123 PB1, MSP432 P3.3   J1.4  DIO1_RXD UART from MSP432 to CC2650BP
//  MRDY   J1.2  TM4C123 PB5, MSP432 P6.0   J1.2  IOID_7   Master ready from MSP432 to CC2650BP 
//  SRDY   J2.19 TM4C123 PB2, MSP432 P2.5   J2.19 IOID_8   Slave ready from CC2650BP to MSP432 

//------------GPIO_Init------------
// Initialize MRDY (out), SRDY (in), RESET (out) GPIO pins
// Input: none
// Output: none
void GPIO_Init(void){
  P2->SEL0 &= ~0x20;  // SRDY is P2.5, J2.19
  P2->SEL1 &= ~0x20;  // 1) configure P2.5 GPIO
  P2->DIR &= ~0x20;   // 2) make P2.5 in
  P2->REN |= 0x20;    // 3) enable pull resistors on P2.5
  P2->OUT |= 0x20;    //    P2.5 are pull-up
  
  P6->SEL0 &= ~0x01;  // J1.2 MRDY {TM4C123 PB5, MSP432 P6.0}
  P6->SEL1 &= ~0x01;  // 1) configure P6.0 as GPIO
  P6->DIR |= 0x01;    // 2) make P6.0 out
  P6->DS |= 0x01;     // 3) activate increased drive strength
  SetMRDY();        //   MRDY=1  
  
  P6->SEL0 &= ~0x80;  // J4.35 Reset to CC2650 {TM4C123 PC6, MSP432 P6.7}
  P6->SEL1 &= ~0x80;  // 1) configure P6.7 as GPIO
  P6->DIR |= 0x80;    // 2) make P6.7 out
  P6->DS |= 0x80;     // 3) activate increased drive strength
  ClearReset();     // RESET=0    
}
#else
// These three options require either reprogramming the CC2650LP/CC2650BP or using a 7-wire tether
// These three options allow the use of the MKII I/O boosterpack
// Option 1) The CC2650BP is tethered to the MSP432 using 7 wires (no reprogramming CC2650 needed)
// Two board stack: MSP432+MKII  <---7 wires--->  CC2650BP
// signal  MSP432                           CC2650BP       comment
//  3V3    J1.1  3.3V                       J1.1  3.3V     Power from MSP432 to CC2650BP 
//  GND    J2.20 ground                     J2.20 ground   Connect ground together
//  NRESET J4.35 TM4C123 PC6, MSP432 P6.7   J4.35          Reset from MSP432 to CC2650BP  
//  TX     J1.3  TM4C123 PB0, MSP432 P3.2   J1.3  DIO0_TXD UART from CC2650BP to MSP432  
//  RX     J1.4  TM4C123 PB1, MSP432 P3.3   J1.4  DIO1_RXD UART from MSP432 to CC2650BP
//  MRDY   J2.14 TM4C123 PB6, MSP432 P1.7   J1.2  IOID_7   Master ready from MSP432 to CC2650BP 
//  SRDY   J2.12 TM4C123 PA3, MSP432 P5.2   J2.19 IOID_8   Slave ready from CC2650BP to MSP432 

// Option 2) This version also works with a custom version of the SNP loaded onto the CC2650BP
// Program into CC2650BP: simple_np_cc2650bp_uart_pm_xsbl_mooc_custom.hex
// Three board stack: CC2650BP+MSP432+MKII (BOOSTXL-CC2650MA, MSP-EXP432P401R, and BOOSTXL-EDUMKII)
// signal  MSP432                           CC2650LP       comment
//  3V3    J1.1  3.3V                       J1.1  3.3V     Power from MSP432 to CC2650BP 
//  GND    J2.20 ground                     J2.20 ground   Connect ground together
//  NRESET J4.35 TM4C123 PC6, MSP432 P6.7   J4.35          Reset from MSP432 to CC2650BP  
//  TX     J1.3  TM4C123 PB0, MSP432 P3.2   J1.3  DIO0_TXD UART from CC2650BP to MSP432  
//  RX     J1.4  TM4C123 PB1, MSP432 P3.3   J1.4  DIO1_RXD UART from MSP432 to CC2650BP
//  MRDY   J2.14 TM4C123 PB6, MSP432 P1.7   J1.14 DIO8     Master ready from MSP432 to CC2650BP 
//  SRDY   J2.12 TM4C123 PA3, MSP432 P5.2   J2.12 DIO14    Slave ready from CC2650BP to MSP432 

// Option 3) This version also works with a custom version of the SNP loaded onto the CC2650LP
// Program into CC2650LP: simple_np_cc2650lp_uart_pm_xsbl_mooc_custom.hex
// Remove Rx and Tx jumpers on CC2650LP
// Optional: remove two LED jumpers on Red, Green LEDs on CC2650 LaunchPad
// Place insulting tape over the set of 11 jumpers in middle, before stacking
// Three board stack: CC2650LP+MSP432+MKII (LAUNCHXL-CC2650, MSP-EXP432P401R, and BOOSTXL-EDUMKII)
// signal  MSP432                           CC2650LP       comment
//  3V3    J1.1  3.3V                       J1.1  3.3V     Power from MSP432 to CC2650LP 
//  GND    J2.20 ground                     J2.20 ground   Connect ground together
//  NRESET J4.35 TM4C123 PC6, MSP432 P6.7   J4.35          Reset from MSP432 to CC2650LP  
//  TX     J1.3  TM4C123 PB0, MSP432 P3.2   J1.3  DIO3_TXD UART from CC2650LP to MSP432  
//  RX     J1.4  TM4C123 PB1, MSP432 P3.3   J1.4  DIO2_RXD UART from MSP432 to CC2650LP
//  MRDY   J2.14 TM4C123 PB6, MSP432 P1.7   J2.14 DIO8     Master ready from MSP432 to CC2650LP 
//  SRDY   J2.12 TM4C123 PA3, MSP432 P5.2   J2.12 DIO14    Slave ready from CC2650LP to MSP432 

//------------GPIO_Init------------
// Initialize MRDY (out), SRDY (in), RESET (out) GPIO pins
// Input: none
// Output: none
void GPIO_Init(void){
  P5->SEL0 &= ~0x04;  // SRDY is P5.2, J2.12
  P5->SEL1 &= ~0x04;  // 1) configure P5.2 GPIO
  P5->DIR &= ~0x04;   // 2) make P5.2 in
  P5->REN |= 0x04;    // 3) enable pull resistors on P5.2
  P5->OUT |= 0x04;    //    P5.2 are pull-up
  
  P1->SEL0 &= ~0x80;  // J2.14 MRDY is P1.7
  P1->SEL1 &= ~0x80;  // 1) configure P1.7 as GPIO
  P1->DIR |= 0x80;    // 2) make P1.7 out
  P1->DS |= 0x80;     // 3) activate increased drive strength
  SetMRDY();        //   MRDY=1  
  
  P6->SEL0 &= ~0x80;  // J4.35 Reset to CC2650 {TM4C123 PC6, MSP432 P6.7}
  P6->SEL1 &= ~0x80;  // 1) configure P6.7 as GPIO
  P6->DIR |= 0x80;    // 2) make P6.7 out
  P6->DS |= 0x80;     // 3) activate increased drive strength
  ClearReset();     // RESET=0    
}
#endif

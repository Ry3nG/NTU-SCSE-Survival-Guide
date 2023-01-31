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

// reflectance LED illuminate connected to P5.3
// reflectance sensor 1 connected to P7.0 (robot's right, robot off road to left)
// reflectance sensor 2 connected to P7.1
// reflectance sensor 3 connected to P7.2
// reflectance sensor 4 connected to P7.3 center
// reflectance sensor 5 connected to P7.4 center
// reflectance sensor 6 connected to P7.5
// reflectance sensor 7 connected to P7.6
// reflectance sensor 8 connected to P7.7 (robot's left, robot off road to right)

#include "msp.h"
//#include "..\inc\bump.h"
#include "..\inc\Reflectance.h"
#include "..\inc\Clock.h"
#include "..\inc\SysTickInts.h"
#include "..\inc\CortexM.h"
#include "..\inc\LaunchPad.h"
#include "..\inc\TExaS.h"

volatile uint8_t reflectance_data, bump_data;
volatile uint32_t MainCount=0;

volatile uint8_t RESULT;

void (*Port4Task)(void);

void SysTick_Handler(void){ // every 1ms
    volatile static uint8_t count=0;
    if(count==0){
        Reflectance_Start();
    }
    else if (count==1) {
        reflectance_data =  Reflectance_End();
        bump_data = RESULT;
    }
    count++;
    if(count==10)count=0;
}

// Read current state of 6 switches
   // Returns a 6-bit positive logic result (0 to 63)
   // bit 5 Bump5
   // bit 4 Bump4
   // bit 3 Bump3
   // bit 2 Bump2
   // bit 1 Bump1
   // bit 0 Bump0
   void Bump_Read_void(void){
       // write this as part of Lab 3
       // Pack the 6 valid bits in the value read from the input data
       // register to occupy 6 lower order bits of the result variable.
       uint8_t bump0, bump1, bump2, bump3, bump4, bump5, result;
       result = 0;
       bump0 = (P4->IN&0b00000001);
       bump1 = (P4->IN&0b00000100)>>1;
       bump2 = (P4->IN&0b00001000)>>1;

       bump3 = (P4->IN&0b00100000)>>2;
       bump4 = (P4->IN&0b01000000)>>2;
       bump5 = (P4->IN&0b10000000)>>2;
       result = bump0+bump1+bump2+bump3+bump4+bump5;
       RESULT = result;
   }
   void PORT4_IRQHandler(void){
       (*Port4Task)();
   }
   // Initialize Bump sensors
   // Make six Port 4 pins inputs
   // Activate interface pullup
   // pins 7,6,5,3,2,0
   void Bump_Init_Edge(void(*task)(void)){
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

       NVIC->IP[9] = (NVIC->IP[9]&0x00FFFFFF)|0x40000000;
       NVIC->ISER[1] = 0x40;
   }

int main(void){

volatile uint8_t data_pins;

    Clock_Init48MHz();
    LaunchPad_Init();
    Bump_Init_Edge(&Bump_Read_void);
    Reflectance_Init();
    TExaS_Init(LOGICANALYZER_P7);
    SysTick_Init(48000,1);  // set up SysTick for 1000 Hz interrupts
    EnableInterrupts();

    while(1){
      WaitForInterrupt();
      if(MainCount%1000 == 0)P2->OUT ^= 0x01; // foreground thread
      MainCount++;
    }
}

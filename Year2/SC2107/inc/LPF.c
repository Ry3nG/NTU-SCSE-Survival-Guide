// LPF.c
// Runs on MSP432
// implements three FIR low-pass filters

// Jonathan Valvano
// September 12, 2017

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

#include <stdint.h>
#include "msp.h"


//**************Low pass Digital filter**************
uint32_t Size;      // Size-point average, Size=1 to 512
uint32_t x[1024];   // two copies of MACQ
uint32_t *Pt;       // pointer to current
uint32_t I1;        // index to oldest
uint32_t LPFSum;    // sum of the last Size samples

void LPF_Init(uint32_t initial, uint32_t size){ int i;
  if(size>1024) size=1024; // max
  Size = size;
  I1 = Size-1;
  LPFSum = Size*initial; // prime MACQ with initial data
  for(i=0; i<Size; i++){
    x[i] = initial;
  }
}
// calculate one filter output, called at sampling rate
// Input: new ADC data   Output: filter output
// y(n) = (x(n)+x(n-1)+...+x(n-Size-1)/Size
uint32_t LPF_Calc(uint32_t newdata){
  LPFSum = LPFSum+newdata-x[I1];   // subtract oldest, add newest
  x[I1] = newdata;     // save new data
  if(I1 == 0){
    I1 = Size-1;              // wrap
  } else{
    I1--;                     // make room for data
  }
  return LPFSum/Size;
}

//**************Low pass Digital filter**************
uint32_t Size2;      // Size-point average, Size=1 to 512
uint32_t x2[1024];   // two copies of MACQ
uint32_t *Pt2;       // pointer to current
uint32_t I2;        // index to oldest
uint32_t LPFSum2;    // sum of the last Size samples

void LPF_Init2(uint32_t initial, uint32_t size){ int i;
  if(size>1024) size=1024; // max
  Size2 = size;
  I2 = Size2-1;
  LPFSum2 = Size2*initial; // prime MACQ with initial data
  for(i=0; i<Size2; i++){
    x2[i] = initial;
  }
}
// calculate one filter output, called at sampling rate
// Input: new ADC data   Output: filter output
// y(n) = (x(n)+x(n-1)+...+x(n-Size-1)/Size
uint32_t LPF_Calc2(uint32_t newdata){
  LPFSum2 = LPFSum2+newdata-x2[I2];   // subtract oldest, add newest
  x2[I2] = newdata;     // save new data
  if(I2 == 0){
    I2 = Size2-1;              // wrap
  } else{
    I2--;                     // make room for data
  }
  return LPFSum2/Size2;
}

//**************Low pass Digital filter**************
uint32_t Size3;      // Size-point average, Size=1 to 512
uint32_t x3[1024];   // two copies of MACQ
uint32_t *Pt3;       // pointer to current
uint32_t I3;        // index to oldest
uint32_t LPFSum3;    // sum of the last Size samples

void LPF_Init3(uint32_t initial, uint32_t size){ int i;
  if(size>1024) size=1024; // max
  Size3 = size;
  I3 = Size3-1;
  LPFSum3 = Size3*initial; // prime MACQ with initial data
  for(i=0; i<Size3; i++){
    x3[i] = initial;
  }
}
// calculate one filter output, called at sampling rate
// Input: new ADC data   Output: filter output
// y(n) = (x(n)+x(n-1)+...+x(n-Size-1)/Size
uint32_t LPF_Calc3(uint32_t newdata){
  LPFSum3 = LPFSum3+newdata-x3[I3];   // subtract oldest, add newest
  x3[I3] = newdata;     // save new data
  if(I3 == 0){
    I3 = Size3-1;              // wrap
  } else{
    I3--;                     // make room for data
  }
  return LPFSum3/Size3;
}


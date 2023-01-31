// SineFunction.c
// Runs on MSP432
// A simple implementation of sine function
// Jonathan Valvano
// May 23, 2017

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

/* Calculate fixed-point sin
x(deg) angle(radians) 1000*sin(angle)  y
 0     0                0              -3
 1     0.017453293     17.45240644     15
 2     0.034906585     34.8994967      33
 3     0.052359878     52.33595624     51
87     1.518436449    998.6295348    1000
88     1.535889742    999.390827     1001
89     1.553343034    999.8476952    1001
90     1.570796327   1000            1000
// assume x is between 0 and 90
// y = -0.0006*x*x*x - 0.0213*x*x + 17.921*x - 2.12;
*/
int32_t CubicSin(int32_t x){ 
  int32_t y; 
// start with equation, convert to C
// multiply by 10,000 and divide by 10,000 to remove floating point
// y = (-6*x*x*x – 213*x*x + 179210*x – 21200)/10000;
// factor to reduce number of multiplies
  y = (((-6*x-213)*x+179210)*x-21200)/10000;
  return y;
}
/* Calculate fixed-point sin
  input: x angle in degrees
  output: 1000*sin(x)
*/
int32_t fsin(int32_t x){ 
  while(x<-180){
    x = x+360; // shift into -180 to +179
  }
  while(x>=180){
    x = x-360; // shift into -180 to +179
  }
  // four quadrant solution
  if(x>=0 && x<=90){
    return CubicSin(x);
  }else if(x>=-90 && x<0){
    return -CubicSin(-x);
  }else if(x>90){
    return CubicSin(180-x);
  }
  return -CubicSin(180+x);
}

// test main
int32_t Results[361];
int main(void){ int angle; int32_t y;
  for(angle=-180; angle<180; angle++){
    y = fsin(angle);
    Results[angle+180] = y;
  }
  while(1){};
}



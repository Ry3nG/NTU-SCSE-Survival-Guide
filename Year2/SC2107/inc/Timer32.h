/**
 * @file      Timer32.h
 * @brief     Initialize Timer32
 * @details   Use Timer32 for periodic interrupts.
 * @version   V1.0
 * @author    Valvano
 * @copyright Copyright 2017 by Jonathan W. Valvano, valvano@mail.utexas.edu,
 * @warning   AS-IS
 * @note      For more information see  http://users.ece.utexas.edu/~valvano/
 * @date      August 13, 2017
 ******************************************************************************/

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

#ifndef __TIMER32INTS_H__ // do not include more than once
#define __TIMER32INTS_H__

/**
 * \enum timer32divider
 * \brief specifies the prescale used for the 32-bit timer
 */
 enum timer32divider{
  T32DIV1 = 0x00000000,    /**< divide by 1, maximum period of about 89 seconds at 48 MHz */
  T32DIV16 = 0x00000004,   /**< divide by 16, maximum period of about 23 minutes at 48 MHz */
  T32DIV256 = 0x00000008   /**< divide by 256, maximum period of about 6 hours, 21 minutes at 48 MHz */
};

/**
 * Activate Timer 32 interrupts to run user task periodically
 * @param task is a pointer to a user function called periodically
 * @param period in units (1/(bus clock)/div), 32 bits
 * @param div is clock divider for Timer32 Timer 1
 * @return none
 * @note T32DIV1   for input clock divider /1<br>
 * T32DIV16  for input clock divider /16<br>
 * T32DIV256 for input clock divider /256<br>
 * @brief Initialize Timer 32
 */
void Timer32_Init(void(*task)(void), uint32_t period, enum timer32divider div);

#endif // __TIMER32INTS_H__

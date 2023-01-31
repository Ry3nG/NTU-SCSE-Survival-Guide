/**
 * @file      SysTick.h
 * @brief     Provide functions that initialize the SysTick module
 * @details   Time delay using SysTick busy-wait
 * @version   V1.0
 * @author    Valvano
 * @copyright Copyright 2017 by Jonathan W. Valvano, valvano@mail.utexas.edu,
 * @warning   AS-IS
 * @note      For more information see  http://users.ece.utexas.edu/~valvano/
 * @date      February 19, 2017
 ******************************************************************************/

// Provide functions that initialize the SysTick module, wait at least a
// designated number of clock cycles, and wait approximately a multiple
// of 10 milliseconds using busy wait.  After a power-on-reset, the
// MSP432 gets its clock from the internal digitally controlled
// oscillator, which is set to 3 MHz by default.  One distinct advantage
// of the MSP432 is that it has low-power clock options to reduce power
// consumption by reducing clock frequency.  This matters for the
// function SysTick_Wait10ms(), which will wait longer than 10 ms if the
// clock is slower.


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

/**
 * Initialize SysTick with busy wait running at bus clock
 *
 * @param  none
 * @return none
 * @note   The system bus clock affects this module
 * @brief  Initialize SysTick
 */
void SysTick_Init(void);


/**
 * Time delay using busy wait
 *
 * @param   delay is the number of bus cycles to wait
 * @return  none
 * @note    The system bus clock affects this module
 * @warning SysTick_Init must be called before calling this function
 * @brief   Time delay using SysTick
 */
void SysTick_Wait(uint32_t delay);

/**
 * Time delay using busy wait
 *
 * @param   delay is the time in 10-ms units
 * @return  none
 * @note    assumes 48 MHz bus clock
 * @warning SysTick_Init must be called before calling this function
 * @brief   Time delay using SysTick
 */
void SysTick_Wait10ms(uint32_t delay);



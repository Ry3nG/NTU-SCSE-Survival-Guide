/**
 * @file      FlashProgram.h
 * @brief     Provide functions that initialize the flash memory
 * @details   Runs on MSP432, write
 * 32-bit data to flash, write an array of 32-bit data to flash,
 * and erase a 4 KB block.
 * @version   V1.0
 * @author    Valvano
 * @copyright Copyright 2017 by Jonathan W. Valvano, valvano@mail.utexas.edu,
 * @warning   AS-IS
 * @note      For more information see  http://users.ece.utexas.edu/~valvano/
 * @date      July 2, 2017
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
 * \brief Value returned if failure
 */
#define ERROR   1
/**
 * \brief Value returned if success
 */
#define NOERROR 0


/**
 * Initialize Flash
 *
 * @param  systemClockFreqMHz System clock frequency in MHz
 * @return none
 * @note   Units of frequency are in MHz
 * @note   On the MSP432, this function is not needed and thus the implementation is empty. The empty function is included to be compatible with other architectures that do need initialization.
 * @brief  Initialize Flash
 */
void Flash_Init(uint8_t systemClockFreqMHz);

/**
 * Write 32-bit data to flash at given address.
 *
 * @param   addr 4-byte aligned flash memory address to write
 * @param   data 32-bit data
 * @return  Result 'NOERROR' if successful, 'ERROR' if fail
 * @note    This function is not interrupt safe.
 * @warning 'addr' must be in flash Bank 1, the function must be in bank 0
 * @brief   Write 32-bit data to flash
 */
int Flash_Write(uint32_t addr, uint32_t data);

/**
 * Write an array of 32-bit data to flash starting at given address.
 *
 * @param   source pointer to array of 32-bit data
 * @param   addr 4-byte aligned flash memory address to start writing
 * @param   count  number of 32-bit writes
 * @return  Result number of successful writes; return value == count if completely successful
 * @note    At 48 MHz, it takes 612 usec to write 10 words
 * @note    This function is not interrupt safe.
 * @warning Parameter 'addr' must be in flash Bank 1, the function must be in bank 0
 * @brief   Write an array to flash
 */
int Flash_WriteArray(uint32_t *source, uint32_t addr, uint16_t count);


/**
 * Write an array of 32-bit data to flash starting at given address.
 * This is twice as fast as Flash_WriteArray(), but the address has
 * to be 16-byte aligned, and the count has to be <= 16.
 *
 * @param   source pointer to array of 32-bit data
 * @param   addr 16-byte aligned flash memory address to start writing
 * @param   count  number of 32-bit writes
 * @return  Result number of successful writes; return value == min(count, 16) if completely successful
 * @note    At 48 MHz, it takes 114 usec to write 16 words
 * @note    This function is not interrupt safe.
 * @warning Parameter 'addr' must be in flash Bank 1, the function must be in bank 0
 * @brief   Write an array to flash
 */
int Flash_FastWrite(uint32_t *source, uint32_t addr, uint16_t count);


/**
 * Erase 4 KB block of flash
 *
 * @param   addr 4-KB aligned flash memory address to erase
 * @return  Result 'NOERROR' if successful, 'ERROR' if fail
 * @note    At 48 MHz, it takes 612 usec to write 10 words
 * @note    This function is not interrupt safe.
 * @warning Parameter 'addr' must be in flash Bank 1, the function must be in bank 0
 * @brief   Erase 4 KB block of flash
 */
int Flash_Erase(uint32_t addr);

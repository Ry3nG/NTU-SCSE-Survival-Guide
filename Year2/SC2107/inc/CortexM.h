/**
 * @file      CortexM.h
 * @brief     Basic functions used in these labs
 * @details   Used for enabling and disabling interrupts
 * @version   V1.0
 * @author    Valvano
 * @copyright Copyright 2017 by Jonathan W. Valvano, valvano@mail.utexas.edu,
 * @warning   AS-IS
 * @note      For more information see  http://users.ece.utexas.edu/~valvano/
 * @date      February 18, 2017
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


/**
 * Disables Interrupts
 *
 * @param  none
 * @return none
 *
 * @brief  Sets the I bit in the PRIMASK to disable interrupts.
 */
void DisableInterrupts(void); // Disable interrupts


/**
 * Enables Interrupts
 *
 * @param  none
 * @return none
 *
 * @brief  clears the I bit in the PRIMASK to enable interrupts
 */
void EnableInterrupts(void);  // Enable interrupts


/**
 * Start a critical section. Code between StartCritical and EndCritical is run atomically
 *
 * @param  none
 * @return copy of the PRIMASK (I bit) before StartCritical called
 *
 * @brief  Saves a copy of PRIMASK and disables interrupts
 */
long StartCritical(void);    


/**
 * End a critical section. Code between StartCritical and EndCritical is run atomically
 *
 * @param  sr is PRIMASK (I bit) before StartCritical called
 * @return none
 *
 * @brief  Sets PRIMASK with value passed in
 */
void EndCritical(long sr);    // restore I bit to previous value


/**
 * Enters low power sleep mode waiting for interrupt (WFI instruction)
 * processor sleeps until next hardware interrupt
 * returns after ISR has been run
 *
 * @param  none
 * @return none
 *
 * @brief  Enters low power sleep mode waiting for interrupt
 */
void WaitForInterrupt(void);  


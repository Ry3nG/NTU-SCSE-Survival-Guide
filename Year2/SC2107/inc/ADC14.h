/**
 * @file      ADC14.h
 * @brief     Initialize 14-bit ADC0
 * @details   ADC input, software trigger, 14-bit conversion<br>
 * The ADC14 allows two possible references: 2.5V or 3.3V.
 * The internal 2.5V reference is lower noise, but limits the range to 0 to 2.5V.>
 * The other possibility is to use the analog voltage supply at 3.3V,
 * making the ADC range 0 to 3.3V. In this driver, the 3.3V range is selected.
 * There are three configurations (each with initialization and a
 * read ADC with software trigger, busy-wait function:<br>
 * - sample just P4.7/A6 <br>
 * - sample P4.6/A7 and P4.7/A6 <br>
 * - sample just P4.1/A12 <br>
 * - sample P9.0/A17, P4.1/A12, and P9.1/A16<br>
 * @version   V1.0
 * @author    Valvano
 * @copyright Copyright 2017 by Jonathan W. Valvano, valvano@mail.utexas.edu,
 * @warning   AS-IS
 * @note      For more information see  http://users.ece.utexas.edu/~valvano/
 * @date      July 20, 2017
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


#ifndef ADC14_H_
#define ADC14_H_

/**
 * Initialize 14-bit ADC0 in software-triggered mode to take
 * measurements when the associated function is called.
 * One channel is measured: P4.7/A6
 * @param none
 * @return none
 * @note  The 3.3V analog supply is used as reference
 * @brief  Initialize 14-bit ADC0
 */
void ADC0_InitSWTriggerCh6(void);


/**
 * Initialize 14-bit ADC0 in software-triggered mode to take
 * measurements when the associated function is called.
 * These channels are measured:<br>
 * - Sample P4.6/A7(first)<br>
 * - Sample P4.7/A6(last)
 * @param none
 * @return none
 * @note  The 3.3V analog supply is used as reference
 * @brief  Initialize 14-bit ADC0
 */
void ADC0_InitSWTriggerCh67(void);

/**
 * Initialize 14-bit ADC0 in software-triggered mode to take
 * measurements when the associated function is called.
 * One channel is measured: P4.1/A12
 * @param none
 * @return none
 * @note  The 3.3V analog supply is used as reference
 * @brief  Initialize 14-bit ADC0
 */
void ADC0_InitSWTriggerCh12(void);


/**
 * Initialize 14-bit ADC0 in software-triggered mode to take
 * measurements when the associated function is called.  These
 * channels are measured:<br>
 * - Sample P9.0/A17(first)<br>
 * - Sample P4.1/A12<br>
 * - Sample P9.1/A16(last)
 * @param none
 * @return none
 * @note  The 3.3V analog supply is used as reference
 * @brief  Initialize 14-bit ADC0
 */
void ADC0_InitSWTriggerCh17_12_16(void);

/**
 * Trigger a single ADC measurement on P4.7/A6,
 * wait for it to complete, and return the 14-bit result
 * as 0 to 16383.
 * The ADC input voltage range is 0 to 3.3V.
 * Busy-wait synchronization used.
 * @param none
 * @return 14-bit result
 * @note  Assumes ADC0_InitSWTriggerCh6() has been called.
 * @brief  Trigger ADC measurement and wait for result.
 */
uint32_t ADC_In6(void);

/**
 * Trigger a single ADC measurement on P4.7/A6 and P4.6/A7,
 * wait for it to complete, and put the results in the pointers
 * given.  The pointers are 32-bit integers because the ADC
 * registers are 32 bits.  In this case, bits 31-16 are
 * undefined, and bits 15-14 are zero.
 * The ADC input voltage range is 0 to 3.3V.
 * Busy-wait synchronization used.
 * Uses return by reference parameter passing.
 * @param ch6 is a pointer to store 32-bit P4.7/A6 conversion result<br>
 * @param ch7 is a pointer to store 32-bit P4.6/A7 conversion result
 * @return none
 * @note  Assumes ADC0_InitSWTriggerCh67() has been called.
 * @brief  Trigger ADC measurement on channels 6+7 and wait for result.
 */
void ADC_In67(uint32_t *ch6, uint32_t *ch7);

/**
 * Trigger a single ADC measurement on P4.1/A12,
 * wait for it to complete, and return the 14-bit result
 * as 0 to 16383.
 * The ADC input voltage range is 0 to 3.3V.
 * Busy-wait synchronization used.
 * @param none
 * @return 14-bit result
 * @note  Assumes ADC0_InitSWTriggerCh12() has been called.
 * @brief  Trigger ADC measurement and wait for result.
 */
uint32_t ADC_In12(void);

/**
 * Trigger a single ADC measurement on P9.0/A17, P4.1/A12, and
 * P9.1/A16, wait for it to complete, and put the results in
 * the pointers given.  The pointers are 32-bit integers
 * because the ADC registers are 32 bits.  In this case, bits
 * 31-16 are undefined, and bits 15-14 are zero.
 * Busy-wait synchronization used.
 * The ADC input voltage range is 0 to 3.3V.
 * Uses return by reference parameter passing.
 * @param ch17 is a pointer to store 32-bit P9.0/A17 conversion result<br>
 * @param ch12 is a pointer to store 32-bit P4.1/A12 conversion result<br>
 * @param ch16 is a pointer to store 32-bit P9.1/A16 conversion result
 * @return none
 * @note  Assumes ADC0_InitSWTriggerCh17_12_16() has been called.
 * @brief  Trigger ADC measurement on channels 17+12+16 and wait for result.
 */
void ADC_In17_12_16(uint32_t *ch17, uint32_t *ch12, uint32_t *ch16);

#endif /* ADC14_H_ */

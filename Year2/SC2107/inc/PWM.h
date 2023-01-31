/**
 * @file      PWM.h
 * @brief     Provide PWM output functions
 * @details   Four TimerA0 PWM outputs
 * @remark    PWM on P2.4 using TimerA0 TA0.CCR1
 * @remark    PWM on P2.5 using TimerA0 TA0.CCR2
 * @remark    PWM on P2.6 using TimerA0 TA0.CCR3
 * @remark    PWM on P2.7 using TimerA0 TA0.CCR4
 * @remark    MCLK = SMCLK = 3MHz DCO; ACLK = 32.768kHz
 * @remark    TACCR0 generates a square wave of freq ACLK/1024 =32Hz
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

#ifndef PWM_H_
#define PWM_H_



/**
 * @details  Initialize PWM outputs on P2.4, P2.5
 * @remark   Counter counts up to TA0CCR0 and back down
 * @remark   Let Timerclock period T = 8/12MHz = 666.7ns
 * @remark   P2.4=1 when timer equals TA0CCR1 on way down, P2.4=0 when timer equals TA0CCR1 on way up
 * @remark   P2.5=1 when timer equals TA0CCR2 on way down, P2.5=0 when timer equals TA0CCR2 on way up
 * @remark   Period of P2.4 is period*1.333us, duty cycle is duty1/period
 * @remark   Period of P2.5 is period*1.333us, duty cycle is duty2/period
 * @remark   Assumes 48 MHz bus clock
 * @remark   Assumes SMCLK = 48MHz/4 = 12 MHz, 83.33ns
 * @param  period is period of wave in 1.333us units
 * @param  duty1 is initial width of high pulse on P2.4 in 1.333us units
 * @param  duty2 is initial width of high pulse om P2.5 in 1.333us units
 * @return none
 * @brief  Initialize PWM1 PWM2
 */
void PWM_Init12(uint16_t period, uint16_t duty1, uint16_t duty2);

/**
 * @details  Initialize PWM output on P2.4
 * @remark   Counter counts up to TA0CCR0 and back down
 * @remark   Let Timerclock period T = 1/12MHz = 83.33ns
 * @remark   P2.4=1 when timer equals TA0CCR1 on way down, P2.4=0 when timer equals TA0CCR1 on way up
 * @remark   Period of P2.4 is period*166.67ns, duty cycle is duty/period
 * @remark   Assumes 48 MHz bus clock
 * @remark   Assumes SMCLK = 48MHz/4 = 12 MHz, 83.33ns
 * @param  period is period of wave in 166.67ns units
 * @param  duty is initial width of high pulse on P2.4 in 166.67ns units
 * @return none
 * @brief  Initialize PWM1
 */
void PWM_Init1(uint16_t period, uint16_t duty);

//***************************PWM_Duty1*******************************
// change duty cycle of PWM output on P2.4
// Inputs:  duty1
// Outputs: none
// period of P2.4 is 2*period*666.7ns, duty cycle is duty1/period

/**
 * @details  Set duty cycle on P2.4
 * @remark   Period of P2.4 is period*1.333us, duty cycle is duty1/period
 * @param    duty1 is width of high pulse on P2.4 in 1.333us units
 * @return   none
 * @warning  duty1 must be less than period
 * @brief    set duty cycle on PWM1
 */
void PWM_Duty1(uint16_t duty1);

/**
 * @details  Set duty cycle on P2.5
 * @remark   Period of P2.5 is period*1.333us, duty cycle is duty2/period
 * @param    duty2 is width of high pulse on P2.5 in 1.333us units
 * @return   none
 * @warning  duty2 must be less than period
 * @brief    set duty cycle on PWM2
 */
void PWM_Duty2(uint16_t duty2);

/**
 * @details  Initialize PWM outputs on P2.6, P2.7
 * @remark   Counter counts up to TA0CCR0 and back down
 * @remark   Let Timerclock period T = 8/12MHz = 666.7ns
 * @remark   P2.6=1 when timer equals TA0CCR3 on way down, P2.6=0 when timer equals TA0CCR3 on way up
 * @remark   P2.7=1 when timer equals TA0CCR4 on way down, P2.7=0 when timer equals TA0CCR4 on way up
 * @remark   Period of P2.6 is period*1.333us, duty cycle is duty3/period
 * @remark   Period of P2.7 is period*1.333us, duty cycle is duty4/period
 * @remark   Assumes 48 MHz bus clock
 * @remark   Assumes SMCLK = 48MHz/4 = 12 MHz, 83.33ns
 * @param  period is period of wave in 1.333us units
 * @param  duty3 is initial width of high pulse on P2.6 in 1.333us units
 * @param  duty4 is initial width of high pulse om P2.7 in 1.333us units
 * @return none
 * @brief  Initialize PWM3 PWM4
 */
void PWM_Init34(uint16_t period, uint16_t duty3, uint16_t duty4);

/**
 * @details  Set duty cycle on P2.6
 * @remark   Period of P2.6 is period*1.333us, duty cycle is duty3/period
 * @param    duty3 is width of high pulse on P2.6 in 1.333us units
 * @return   none
 * @warning  duty3 must be less than period
 * @brief    set duty cycle on PWM3
 */
void PWM_Duty3(uint16_t duty3);

/**
 * @details  Set duty cycle on P2.7
 * @remark   Period of P2.7 is period*1.333us, duty cycle is duty3/period
 * @param    duty4 is width of high pulse on P2.7 in 1.333us units
 * @return   none
 * @warning  duty4 must be less than period
 * @brief    set duty cycle on PWM4
 */
void PWM_Duty4(uint16_t duty4);



#endif /* PWM_H_ */

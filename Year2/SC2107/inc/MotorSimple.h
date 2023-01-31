/**
 * @file      MotorSimple.h
 * @brief     Set motor speed and direction
 * @details   Provide mid-level functions that initialize ports and
 * set motor speeds to move the robot. Simple solution that does NOT
 * use PWM hardware. Rather the PWM outputs are created by software
 * delays using the SysTick timer.<br>
 * Sever VCCMD=VREG jumper on Motor Driver and Power Distribution Board and connect VCCMD to 3.3V.
 *   This makes P3.7 and P3.6 low power disables for motor drivers.  0 to sleep/stop.<br>
 * Sever nSLPL=nSLPR jumper.
 *   This separates P3.7 and P3.6 allowing for independent control<br>
 * Left motor direction connected to P1.7 (J2.14)<br>
 * Left motor PWM connected to P2.7/TA0CCP4 (J4.40)<br>
 * Left motor enable connected to P3.7 (J4.31)<br>
 * Right motor direction connected to P1.6 (J2.15)<br>
 * Right motor PWM connected to P2.6/TA0CCP3 (J4.39)<br>
 * Right motor enable connected to P3.6 (J2.11)
 * @version   V1.0
 * @author    Valvano
 * @copyright Copyright 2017 by Jonathan W. Valvano, valvano@mail.utexas.edu,
 * @warning   AS-IS
 * @note      For more information see  http://users.ece.utexas.edu/~valvano/
 * @date      July 7, 2017
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




#ifndef MOTORSIMPLE_H_
#define MOTORSIMPLE_H_
// *******Lab 12 solution*******

/**
 * Initializes the 6 GPIO lines and puts driver to sleep.<br>
 * This simple set of drivers does not use hardware timer PWM.
 * Rather, it uses software delays with SysTick and consumes all the
 * processor time.
 * @param none
 * @return none
 * @note Returns right away.
 * @brief  Initialize motor interface
 */
void Motor_InitSimple(void);



/**
 * Stops both motors, puts driver to sleep.
 * @param none
 * @return none
 * @note Returns right away.
 * @brief  Stops the motors
 */
void Motor_StopSimple(void);


/**
 * Drives both motors forward at duty (100 to 9900).
 * Runs for time duration (units=10ms), and then stops.
 * Stop the motors and return if any bumper switch is active.
 * Returns after time*10ms or if a bumper switch is hit.
 * @param duty duty cycle of both wheels (100 to 9900)
 * @param time duration (10ms) to run
 * @return none
 * @note Does not return until time has elapsed or any bumper switch is active.
 * @brief  Run both motors forward
 */
void Motor_ForwardSimple(uint16_t duty, uint32_t time);


/**
 * Drives both motors backward at duty (100 to 9900).
 * Runs for time duration (units=10ms), and then stops.
 * Runs even if any bumper switch is active.
 * Returns after time*10ms.
 * @param duty duty cycle of both wheels (100 to 9900)
 * @param time duration (10ms) to run
 * @return none
 * @note Does not return until time has elapsed.
 * @brief  Run both motors backward
 */
void Motor_BackwardSimple(uint16_t duty, uint32_t time);


/**
 * Drives just the left motor forward at duty (100 to 9900).
 * Right motor is stopped (sleeping).
 * Runs for time duration (units=10ms), and then stops.
 * Stop the motors and return if any bumper switch is active.
 * Returns after time*10ms or if a bumper switch is hit.
 * @param duty duty cycle of left wheel (100 to 9900)
 * @param time duration (10ms) to run
 * @return none
 * @note Does not return until time has elapsed or any bumper switch is active.
 * @brief  Run left motor forward
 */
void Motor_LeftSimple(uint16_t duty, uint32_t time);


/**
 * Drives just the right motor forward at duty (100 to 9900).
 * Left motor is stopped (sleeping).
 * Runs for time duration (units=10ms), and then stops.
 * Stop the motors and return if any bumper switch is active.
 * Returns after time*10ms or if a bumper switch is hit.
 * @param duty duty cycle of right wheel (100 to 9900)
 * @param time duration (10ms) to run
 * @return none
 * @note Does not return until time has elapsed or any bumper switch is active.
 * @brief  Run right motor forward
 */
void Motor_RightSimple(uint16_t duty, uint32_t time);


#endif /* MOTORSIMPLE_H_ */

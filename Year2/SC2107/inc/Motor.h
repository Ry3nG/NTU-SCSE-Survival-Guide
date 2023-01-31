/**
 * @file      Motor.h
 * @brief     Set motor speed and direction
 * @details   Provide mid-level functions that initialize ports and
 * set motor speeds to move the robot.<br>
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




#ifndef MOTOR_H_
#define MOTOR_H_

// *******Lab 13 solution*******

/**
 * Initialize GPIO pins for output, which will be
 * used to control the direction of the motors and
 * to enable or disable the drivers.
 * The motors are initially stopped, the drivers
 * are initially powered down, and the PWM speed
 * control is uninitialized.
 * @param none
 * @return none
 * @brief  Initialize motor interface
 */
void Motor_Init(void);

/**
 * Stop the motors, power down the drivers, and
 * set the PWM speed control to 0% duty cycle.
 * @param none
 * @return none
 * @brief  Stop the robot
 */
void Motor_Stop(void);

/**
 * Drive the robot forward by running left and
 * right wheels forward with the given duty
 * cycles.
 * @param leftDuty  duty cycle of left wheel (0 to 14,998)
 * @param rightDuty duty cycle of right wheel (0 to 14,998)
 * @return none
 * @note Assumes Motor_Init() has been called
 * @brief  Drive the robot forward
 */
void Motor_Forward(uint16_t leftDuty, uint16_t rightDuty);

/**
 * Turn the robot to the right by running the
 * left wheel forward and the right wheel
 * backward with the given duty cycles.
 * @param leftDuty  duty cycle of left wheel (0 to 14,998)
 * @param rightDuty duty cycle of right wheel (0 to 14,998)
 * @return none
 * @note Assumes Motor_Init() has been called
 * @brief  Turn the robot to the right
 */
void Motor_Right(uint16_t leftDuty, uint16_t rightDuty);

/**
 * Turn the robot to the left by running the
 * left wheel backward and the right wheel
 * forward with the given duty cycles.
 * @param leftDuty  duty cycle of left wheel (0 to 14,998)
 * @param rightDuty duty cycle of right wheel (0 to 14,998)
 * @return none
 * @note Assumes Motor_Init() has been called
 * @brief  Turn the robot to the left
 */
void Motor_Left(uint16_t leftDuty, uint16_t rightDuty);

/**
 * Drive the robot backward by running left and
 * right wheels backward with the given duty
 * cycles.
 * @param leftDuty  duty cycle of left wheel (0 to 14,998)
 * @param rightDuty duty cycle of right wheel (0 to 14,998)
 * @return none
 * @note Assumes Motor_Init() has been called
 * @brief  Drive the robot backward
 */
void Motor_Backward(uint16_t leftDuty, uint16_t rightDuty);

#endif /* MOTOR_H_ */

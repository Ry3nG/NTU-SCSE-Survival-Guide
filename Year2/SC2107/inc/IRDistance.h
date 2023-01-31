/**
 * @file      IRDistance.h
 * @brief     Take infrared distance measurements
 * @details   Provide mid-level functions that convert raw ADC
 * values from the GP2Y0A21YK0F infrared distance sensors to
 * distances in mm.
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

// Pololu #3543 Vreg (5V regulator output) connected to all three Pololu #136 GP2Y0A21YK0F Vcc's (+5V) and MSP432 +5V (J3.21)
// Pololu #3543 Vreg (5V regulator output) connected to positive side of three 10 uF capacitors physically near the sensors
// Pololu ground connected to all three Pololu #136 GP2Y0A21YK0F grounds and MSP432 ground (J3.22)
// Pololu ground connected to negative side of all three 10 uF capacitors
// MSP432 P9.0 (J5) (analog input to MSP432) connected to right GP2Y0A21YK0F Vout
// MSP432 P4.1 (J1.5) (analog input to MSP432) connected to center GP2Y0A21YK0F Vout
// MSP432 P9.1 (J5) (analog input to MSP432) connected to left GP2Y0A21YK0F Vout


#ifndef IRDISTANCE_H_
#define IRDISTANCE_H_


/**
 * Convert ADC sample into distance for the GP2Y0A21YK0F
 * infrared distance sensor.  Conversion uses a calibration formula<br>
 * Dl = Al/(nl + Bl) + Cl
 * @param nl is the 14-bit ADC sample 0 to 16383
 * @return distance from robot center to left wall (units mm)
 * @brief  Convert left infrared distance measurement
 */
int32_t LeftConvert(int32_t nl);

/**
 * Convert ADC sample into distance for the GP2Y0A21YK0F
 * infrared distance sensor.  Conversion uses a calibration formula<br>
 * Dc = Ac/(nc + Bc) + Cc
 * @param nc is the 14-bit ADC sample 0 to 16383
 * @return distance from robot center to center wall (units mm)
 * @brief  Convert center infrared distance measurement
 */
int32_t CenterConvert(int32_t nc);

/**
 * Convert ADC sample into distance for the GP2Y0A21YK0F
 * infrared distance sensor.  Conversion uses a calibration formula<br>
 * Dr = Ar/(nr + Br) + Cr
 * @param nr is the 14-bit ADC sample 0 to 16383
 * @return distance from robot center to right wall (units mm)
 * @brief  Convert right infrared distance measurement
 */
int32_t RightConvert(int32_t nr);      // returns right distance in mm

#endif /* IRDISTANCE_H_ */

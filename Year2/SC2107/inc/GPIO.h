/**
 * @file      GPIO.h
 * @brief     Digital input/output from LaunchPad to CC2650
 * @details   There are two possible hardware connections between MSP432 to CC2650
 * The #define DEFAULT selects which connection to use.
 * These two hardware possibilities can deployed into four options.
 * There are two projects that can be used with these four options:
 * <b>VerySimpleApplicationProcessor_MSP432</b> and <b>ApplicationProcessor_MSP432</b>.

<table>
<caption id="gpio_terms">Terminology</caption>
<tr><th>Legend    <th>TI part number
<tr><td>CC2650BP  <td>BOOSTXL-CC2650MA
<tr><td>CC2650LP  <td>LAUNCHXL-CC2650
<tr><td>MSP432    <td>MSP-EXP432P401R
<tr><td>TM4C123   <td>EK-TM4C123GXL
<tr><td>MKII      <td>BOOSTXL-EDUMKII
</table>
 * @note      Options 1,2,3 allow the use of the MKII I/O boosterpack together with the CC2650

 * @remark   <b>Option 1</b>: the CC2650BP is tethered to the MSP432 using 7 wires.
 * No reprogramming CC2650BP is needed.<br>
 * This configuration has MSP432 plugged into the MKII, and a 7-wire cable to the CC2650BP.<br>
 * For option 1, do NOT include the #define DEFAULT 1.
<table>
<caption id="gpio_option1">Option 1</caption>
<tr><th>signal <th>TM4C123/MSP432                   <th>CC2650BP       <th>comment
<tr><td>3V3    <td>J1.1  3.3V                       <td>J1.1  3.3V     <td>Power from MSP432 to CC2650BP
<tr><td>GND    <td>J2.20 ground                     <td>J2.20 ground   <td>Connect ground together
<tr><td>NRESET <td>J4.35 TM4C123 PC6, MSP432 P6.7   <td>J4.35          <td>Reset from MSP432 to CC2650BP
<tr><td>TX     <td>J1.3  TM4C123 PB0, MSP432 P3.2   <td>J1.3  DIO0_TXD <td>UART from CC2650BP to MSP432
<tr><td>RX     <td>J1.4  TM4C123 PB1, MSP432 P3.3   <td>J1.4  DIO1_RXD <td>UART from MSP432 to CC2650BP
<tr><td>MRDY   <td>J2.14 TM4C123 PB6, MSP432 P1.7   <td>J1.2  IOID_7   <td>Master ready from MSP432 to CC2650BP
<tr><td>SRDY   <td>J2.12 TM4C123 PA3, MSP432 P5.2   <td>J2.19 IOID_8   <td>Slave ready from CC2650BP to MSP432
</table>
<br>
 * @remark    <b>Option 2</b>: The CC2650BP is reprogrammed with a custom version of the SNP.
 * You reprogram the CC2650BP with simple_np_cc2650bp_uart_pm_xsbl_mooc_custom.hex.<br>
 * This configuration has a three board stack: CC2650BP+MSP432+MKII<br>
 * In other words these three boards are connected together: BOOSTXL-CC2650MA, MSP-EXP432P401R, and BOOSTXL-EDUMKII.<br>
 * For option 2, do NOT include the #define DEFAULT 1.
<table>
<caption id="gpio_option2">Option 2</caption>
<tr><th>signal <th>TM4C123/MSP432                   <th>CC2650BP       <th>comment
<tr><td>3V3    <td>J1.1  3.3V                       <td>J1.1  3.3V     <td>Power from MSP432 to CC2650BP
<tr><td>GND    <td>J2.20 ground                     <td>J2.20 ground   <td>Connect ground together
<tr><td>NRESET <td>J4.35 TM4C123 PC6, MSP432 P6.7   <td>J4.35          <td>Reset from MSP432 to CC2650BP
<tr><td>TX     <td>J1.3  TM4C123 PB0, MSP432 P3.2   <td>J1.3  DIO0_TXD <td>UART from CC2650BP to MSP432
<tr><td>RX     <td>J1.4  TM4C123 PB1, MSP432 P3.3   <td>J1.4  DIO1_RXD <td>UART from MSP432 to CC2650BP
<tr><td>MRDY   <td>J2.14 TM4C123 PB6, MSP432 P1.7   <td>J1.14 DIO8     <td>Master ready from MSP432 to CC2650BP
<tr><td>SRDY   <td>J2.12 TM4C123 PA3, MSP432 P5.2   <td>J2.12 DIO14    <td>Slave ready from CC2650BP to MSP432
</table>
<br>
 * @remark    <b>Option 3</b>: The CC2650LP is reprogrammed with a custom version of the SNP.
 * You reprogram the CC2650LP with simple_np_cc2650lp_uart_pm_xsbl_mooc_custom.hex.<br>
 * This configuration has a three board stack: CC2650LP+MSP432+MKII<br>
 * In other words these three boards are connected together: LAUNCHXL-CC2650, MSP-EXP432P401R, and BOOSTXL-EDUMKII.<br>
 * Remove the Rx and Tx jumpers on CC2650LP.<br>
 * It is optional, but we suggest you also remove the two LED jumpers on Red, Green LEDs on the CC2650 LaunchPad.
 * We also recommend you place insulting tape over the set of 11 jumpers in middle, before stacking.<br>
 * For option 3, do NOT include the #define DEFAULT 1.
<table>
<caption id="gpio_option3">Option 3</caption>
<tr><th>signal <th>TM4C123/MSP432                   <th>CC2650LP       <th>comment
<tr><td>3V3    <td>J1.1  3.3V                       <td>J1.1  3.3V     <td>Power from MSP432 to CC2650LP
<tr><td>GND    <td>J2.20 ground                     <td>J2.20 ground   <td>Connect ground together
<tr><td>NRESET <td>J4.35 TM4C123 PC6, MSP432 P6.7   <td>J4.35          <td>Reset from MSP432 to CC2650LP
<tr><td>TX     <td>J1.3  TM4C123 PB0, MSP432 P3.2   <td>J1.3  DIO3_TXD <td>UART from CC2650LP to MSP432
<tr><td>RX     <td>J1.4  TM4C123 PB1, MSP432 P3.3   <td>J1.4  DIO2_RXD <td>UART from MSP432 to CC2650LP
<tr><td>MRDY   <td>J2.14 TM4C123 PB6, MSP432 P1.7   <td>J1.14 DIO12    <td>Master ready from MSP432 to CC2650LP
<tr><td>SRDY   <td>J2.12 TM4C123 PA3, MSP432 P5.2   <td>J2.12 DIO14    <td>Slave ready from CC2650LP to MSP432
</table>
<br>
 * @remark    <b>Option 4</b>: Use this setup with CC2650BP without a MKII.
 * This runs with the default version of SNP that ships on the BOOSTXL-CC2650MA.<br>
 * This configuration has a two board stack: CC2650BP+MSP432<br>
 * In other words these two boards are connected together: BOOSTXL-CC2650MA and MSP-EXP432P401R.<br>
 * For option 4, DO include the #define DEFAULT 1.
<table>
<caption id="gpio_option4">Option 4</caption>
<tr><th>signal <th>TM4C123/MSP432                   <th>CC2650BP       <th>comment
<tr><td>3V3    <td>J1.1  3.3V                       <td>J1.1  3.3V     <td>Power from MSP432 to CC2650BP
<tr><td>GND    <td>J2.20 ground                     <td>J2.20 ground   <td>Connect ground together
<tr><td>NRESET <td>J4.35 TM4C123 PC6, MSP432 P6.7   <td>J4.35          <td>Reset from MSP432 to CC2650BP
<tr><td>TX     <td>J1.3  TM4C123 PB0, MSP432 P3.2   <td>J1.3  DIO0_TXD <td>UART from CC2650BP to MSP432
<tr><td>RX     <td>J1.4  TM4C123 PB1, MSP432 P3.3   <td>J1.4  DIO1_RXD <td>UART from MSP432 to CC2650BP
<tr><td>MRDY   <td>J1.2  TM4C123 PB5, MSP432 P6.0   <td>J1.2  IOID_7   <td>Master ready from MSP432 to CC2650BP
<tr><td>SRDY   <td>J2.19 TM4C123 PB2, MSP432 P2.5   <td>J2.19 IOID_8   <td>Slave ready from CC2650BP to MSP432
</table>
<br>
 * @version   V1.0
 * @author    Valvano
 * @copyright Copyright 2017 by Jonathan W. Valvano, valvano@mail.utexas.edu,
 * @warning   AS-IS
 * @note      For more information see  http://users.ece.utexas.edu/~valvano/
 * @date      February 23, 2017

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

#include "msp.h"

/**
 * \brief defining DEFAULT means option 4, without the definition means options 1,2,3
 */
#define DEFAULT 1


#ifdef DEFAULT
// Option 4
#define SetMRDY() (P6->OUT |= 0x01)       /**< Set MRDY pin high */
#define ClearMRDY() (P6->OUT &= ~0x01)    /**< Clear MRDY pin low */
#define SetReset() (P6->OUT |= 0x80)      /**< Set Reset pin high */
#define ClearReset() (P6->OUT &= ~0x80)   /**< Clear Reset pin low */
#define ReadSRDY() (P2->IN&0x20)          /**< Read SRDY pin */
#else
// Options 1,2,3
#define SetMRDY() (P1->OUT |= 0x80)       /**< Set MRDY pin high */
#define ClearMRDY() (P1->OUT &= ~0x80)    /**< Clear MRDY pin low */
#define SetReset() (P6->OUT |= 0x80)      /**< Set Reset pin high */
#define ClearReset() (P6->OUT &= ~0x80)   /**< Clear Reset pin low */
#define ReadSRDY() (P5->IN&0x04)          /**< Read SRDY pin */
#endif

/**
 * Initialize GPIO pins used for application processor
 * @param  none
 * @return none
 * @brief  Initialize MRDY (out), SRDY (in), RESET (out) GPIO pins
 */
void GPIO_Init(void);

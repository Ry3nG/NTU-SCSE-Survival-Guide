/**
 * @file      TExaS.h
 * @brief     Test Execute and Simulate
 * @details   Virtual 7-bit logic analyzer or 8-bit scope sampling J3.26/P4.4/A9
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

Simplified BSD License (FreeBSD License)
Copyright (c) 2017, Jonathan Valvano
All rights reserved.

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
 * \enum TExaSmode
 * \brief specifies the TExaS modes
 */
enum TExaSmode{
  SCOPE,             /**< creates a 10 kHz 8-bit oscilloscope on J3.26/P4.4/A9 */
  LOGICANALYZER,     /**< creates a 10 kHz 7-bit logic analyzer */
  LOGICANALYZER_P1,  /**< creates a 10 kHz 7-bit logic analyzer on P1.6-P1.0 */
  LOGICANALYZER_P2,  /**< creates a 10 kHz 7-bit logic analyzer on P2.6-P2.0 */
  LOGICANALYZER_P3,  /**< creates a 10 kHz 7-bit logic analyzer on P3.6-P3.0 */
  LOGICANALYZER_P4,  /**< creates a 10 kHz 7-bit logic analyzer on P4.6-P4.0 */
  LOGICANALYZER_P5,  /**< creates a 10 kHz 7-bit logic analyzer on P5.6-P5.0 */
  LOGICANALYZER_P6,  /**< creates a 10 kHz 7-bit logic analyzer on P6.6-P6.0 */
  LOGICANALYZER_P7,  /**< creates a 10 kHz 7-bit logic analyzer on P7.6-P7.0 */
  LOGICANALYZER_P8,  /**< creates a 10 kHz 7-bit logic analyzer on P8.6-P8.0 */
  LOGICANALYZER_P9,  /**< creates a 10 kHz 7-bit logic analyzer on P9.6-P9.0 */
  LOGICANALYZER_P10,  /**< creates a 10 kHz 7-bit logic analyzer on P10.6-P10.0 */
  LOGICANALYZER_P4_765432,  /**< creates a 10 kHz 6-bit logic analyzer on P4.7-P4.2 */
  LOGICANALYZER_P4_765320,  /**< creates a 10 kHz 6-bit logic analyzer on P4.7-5,3-2,0 */
  LOGICANALYZER_P2_7654  /**< creates a 10 kHz 4-bit logic analyzer on P2.7-P2.4 */
};


/**
 * Initialize scope or logic analyzer, triggered by periodic timer
 *
 * @param  mode is SCOPE or LOGICANALYZER
 * @return none
 *
 * @note   This module only runs at 48 MHz<br>
 * Uses UART0, EUSCI_A0 to pass data to PC<br>
 * Uses ADC J3.26/P4.4/A9 in scope mode<br>
 * Uses Timer32 periodic interrupts for 10 kHz sampling
 * @warning TExaS_Init must be called before calling any other TExaS functions
 * @brief  Initialize logic analyzer or scope
 * @details   Virtual 7-bit logic analyzer or 8-bit scope sampling J3.26/P4.4/A9
 */
void TExaS_Init(enum TExaSmode mode);

/**
 * Stop scope or logic analyzer functionality
 *
 * @param  none
 * @return none
 *
 * @note   Data sent at 10 kHz
 * @brief  Stop the logic analyzer or scope
 */
void TExaS_Stop(void);

/**
 * Toggle logic analyzer bit 0
 *
 * @param  none
 * @return none
 *
 * @note   Logic analyzer data sent at 10 kHz
 * @brief  toggle bit 0
 */
void TExaS_Task0(void);
/**
 * Toggle logic analyzer bit 1
 *
 * @param  none
 * @return none
 *
 * @note   Logic analyzer data sent at 10 kHz
 * @note   Only used with TExaS_Init(LOGICANALYZER); initialization
 * @brief  toggle bit 1
 */
void TExaS_Task1(void);
/**
 * Toggle logic analyzer bit 2
 *
 * @param  none
 * @return none
 *
 * @note   Logic analyzer data sent at 10 kHz
 * @note   Only used with TExaS_Init(LOGICANALYZER); initialization
 * @brief  toggle bit 2
 */
void TExaS_Task2(void);
/**
 * Toggle logic analyzer bit 3
 *
 * @param  none
 * @return none
 *
 * @note   Logic analyzer data sent at 10 kHz
 * @note   Only used with TExaS_Init(LOGICANALYZER); initialization
 * @brief  toggle bit 3
 */
void TExaS_Task3(void);
/**
 * Toggle logic analyzer bit 4
 *
 * @param  none
 * @return none
 *
 * @note   Logic analyzer data sent at 10 kHz
 * @note   Only used with TExaS_Init(LOGICANALYZER); initialization
 * @brief  toggle bit 4
 */
void TExaS_Task4(void);
/**
 * Toggle logic analyzer bit 5
 *
 * @param  none
 * @return none
 *
 * @note   Logic analyzer data sent at 10 kHz
 * @note   Only used with TExaS_Init(LOGICANALYZER); initialization
 * @brief  toggle bit 5
 */
void TExaS_Task5(void);
/**
 * Toggle logic analyzer bit 6
 *
 * @param  none
 * @return none
 *
 * @note   Logic analyzer data sent at 10 kHz
 * @note   Only used with TExaS_Init(LOGICANALYZER); initialization
 * @brief  toggle bit 6
 */
void TExaS_Task6(void);

/**
 * Specify all seven bits of logic analyzer
 *
 * @param  data is a 7-bit number
 * @return none
 * @note   Logic analyzer data sent at 10 kHz
 * @note   Only used with TExaS_Init(LOGICANALYZER); initialization
 * @brief  specify logic analyzer output
 */
void TExaS_Set(uint8_t data);
/**
 * Set logic analyzer bit 0
 *
 * @param  none
 * @return none
 *
 * @note   Logic analyzer data sent at 10 kHz
 * @note   Only used with TExaS_Init(LOGICANALYZER); initialization
 * @brief  Bit0 set high
 */
void TExaS_Set0(void);
/**
 * Set logic analyzer bit 1
 *
 * @param  none
 * @return none
 *
 * @note   Logic analyzer data sent at 10 kHz
 * @note   Only used with TExaS_Init(LOGICANALYZER); initialization
 * @brief  Bit1 set high
 */
void TExaS_Set1(void);
/**
 * Set logic analyzer bit 2
 *
 * @param  none
 * @return none
 *
 * @note   Logic analyzer data sent at 10 kHz
 * @note   Only used with TExaS_Init(LOGICANALYZER); initialization
 * @brief  Bit2 set high
 */
void TExaS_Set2(void);
/**
 * Set logic analyzer bit 3
 *
 * @param  none
 * @return none
 *
 * @note   Logic analyzer data sent at 10 kHz
 * @note   Only used with TExaS_Init(LOGICANALYZER); initialization
 * @brief  Bit3 set high
 */
void TExaS_Set3(void);
/**
 * Set logic analyzer bit 4
 *
 * @param  none
 * @return none
 *
 * @note   Logic analyzer data sent at 10 kHz
 * @note   Only used with TExaS_Init(LOGICANALYZER); initialization
 * @brief  Bit4 set high
 */
void TExaS_Set4(void);
/**
 * Set logic analyzer bit 5
 *
 * @param  none
 * @return none
 *
 * @note   Logic analyzer data sent at 10 kHz
 * @note   Only used with TExaS_Init(LOGICANALYZER); initialization
 * @brief  Bit5 set high
 */
void TExaS_Set5(void);
/**
 * Set logic analyzer bit 5
 *
 * @param  none
 * @return none
 *
 * @note   Logic analyzer data sent at 10 kHz
 * @note   Only used with TExaS_Init(LOGICANALYZER); initialization
 * @brief  Bit5 set high
 */
void TExaS_Set6(void);
/**
 * Clear logic analyzer bit 0
 *
 * @param  none
 * @return none
 *
 * @note   Logic analyzer data sent at 10 kHz
 * @note   Only used with TExaS_Init(LOGICANALYZER); initialization
 * @brief  Bit0 cleared low
 */
void TExaS_Clear0(void);
/**
 * Clear logic analyzer bit 1
 *
 * @param  none
 * @return none
 *
 * @note   Logic analyzer data sent at 10 kHz
 * @note   Only used with TExaS_Init(LOGICANALYZER); initialization
 * @brief  Bit1 cleared low
 */
void TExaS_Clear1(void);
/**
 * Clear logic analyzer bit 2
 *
 * @param  none
 * @return none
 *
 * @note   Logic analyzer data sent at 10 kHz
 * @note   Only used with TExaS_Init(LOGICANALYZER); initialization
 * @brief  Bit2 cleared low
 */
void TExaS_Clear2(void);
/**
 * Clear logic analyzer bit 3
 *
 * @param  none
 * @return none
 *
 * @note   Logic analyzer data sent at 10 kHz
 * @note   Only used with TExaS_Init(LOGICANALYZER); initialization
 * @brief  Bit3 cleared low
 */
void TExaS_Clear3(void);
/**
 * Clear logic analyzer bit 4
 *
 * @param  none
 * @return none
 *
 * @note   Logic analyzer data sent at 10 kHz
 * @note   Only used with TExaS_Init(LOGICANALYZER); initialization
 * @brief  Bit4 cleared low
 */
void TExaS_Clear4(void);
/**
 * Clear logic analyzer bit 5
 *
 * @param  none
 * @return none
 *
 * @note   Logic analyzer data sent at 10 kHz
 * @note   Only used with TExaS_Init(LOGICANALYZER); initialization
 * @brief  Bit5 cleared low
 */
void TExaS_Clear5(void);
/**
 * Clear logic analyzer bit 6
 *
 * @param  none
 * @return none
 *
 * @note   Logic analyzer data sent at 10 kHz
 * @note   Only used with TExaS_Init(LOGICANALYZER); initialization
 * @brief  Bit6 cleared low
 */
void TExaS_Clear6(void);


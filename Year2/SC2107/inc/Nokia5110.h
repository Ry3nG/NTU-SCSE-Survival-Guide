/**
 * @file      Nokia5110.h
 * @brief     Provide simple I/O functions for the Nokia 5110
 * @details   Use eUSCI_A3 to send an 8-bit code to the Nokia5110 48x84
 * pixel LCD to display text, images, or other information.
 * @version   V1.0
 * @author    Valvano and Nathan Seidle
 * @copyright Copyright 2017 by Jonathan W. Valvano, valvano@mail.utexas.edu,
 * @warning   AS-IS
 * @note      For more information see  http://users.ece.utexas.edu/~valvano/<br><br>
 * Font table, initialization, and other functions based
 * off of Nokia_5110_Example from Spark Fun:<br>
 * 7-17-2011<br>
 * Spark Fun Electronics 2011<br>
 * Nathan Seidle<br>
 * http://dlnmh9ip6v2uc.cloudfront.net/datasheets/LCD/Monochrome/Nokia_5110_Example.pde
 * @date      September 12, 2017
 *
<table>
<caption id="Nokia5110_ports">Nokia 5110 LCD</caption>
<tr><th>Pin   <th>Nokia 5110 function
<tr><td>+3.3 V<td>VCC
<tr><td>ground<td>GND
<tr><td>P9.4  <td>SCE, active low enable
<tr><td>P9.3  <td>RST, reset=0; run=1
<tr><td>P9.6  <td>D/C, data=1; command=0
<tr><td>P9.7  <td>DN(MOSI), master out slave in
<tr><td>P9.5  <td>SCLK, serial clock
<tr><td>+3.3 V<td>LED, optional LED backlight
</table>
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

// Blue Nokia 5110
// ---------------
// Signal        (Nokia 5110) LaunchPad pin
// Reset         (RST, pin 1) connected to P9.3
// UCA3STE       (CE,  pin 2) connected to P9.4
// Data/Command  (DC,  pin 3) connected to P9.6
// UCA3SIMO      (Din, pin 4) connected to P9.7
// UCA3CLK       (Clk, pin 5) connected to P9.5
// 3.3V          (Vcc, pin 6) power
// back light    (BL,  pin 7) not connected, consists of 4 3.3 V white LEDs which draw ~80mA total
// Ground        (Gnd, pin 8) ground

// Red SparkFun Nokia 5110 (LCD-10168)
// -----------------------------------
// Signal        (Nokia 5110) LaunchPad pin
// 3.3V          (VCC, pin 1) power
// Ground        (GND, pin 2) ground
// UCA3STE       (SCE, pin 3) connected to P9.4
// Reset         (RST, pin 4) connected to P9.3
// Data/Command  (D/C, pin 5) connected to P9.6
// UCA3SIMO      (DN,  pin 6) connected to P9.7
// UCA3CLK       (SCLK, pin 7) connected to P9.5
// back light    (LED, pin 8) not connected, consists of 4 3.3 V white LEDs which draw ~80mA total


#ifndef NOKIA5110_H_
#define NOKIA5110_H_


/**
 * \brief  Maximum columns of the LCD, although the pixels are
 * numbered from zero to (MAX-1).  Address may automatically
 * be incremented after each transmission.
 */
#define MAX_X                   84

/**
 * \brief  Maximum rows of the LCD, although the pixels are
 * numbered from zero to (MAX-1).  In the default horizontal
 * addressing mode (V = 0), rows are clustered into groups of
 * eight, which are all sent together with one 8-bit SSI data
 * transmission.
 */
#define MAX_Y                   48

/**
 * \brief Contrast value 0xB1 looks good on red SparkFun
 * and 0xB8 looks good on blue Nokia 5110.
 * Adjust this from 0xA0 (lighter) to 0xCF (darker) for your display.
 */
#define CONTRAST                0xBF

/**
 * Initialize Nokia 5110 48x84 LCD by sending the proper
 * commands to the PCD8544 driver.  One feature of the
 * MSP432 is that its SSIs can get their baud clock from
 * either the auxiliary clock (ACLK = REFOCLK/1 = 32,768 Hz
 * see <b>Clock.c</b>) or from the low-speed subsystem master
 * clock (SMCLK <= 12 MHz see <b>Clock.c</b>).  The SSI can
 * further divide this clock signal by using the 16-bit Bit
 * Rate Control prescaler Register, UCAxBRW.
 * @param none
 * @return none
 * @note  Assumes low-speed subsystem master clock is 12 MHz
 * @see Nokia5110_OutChar(), Nokia5110_Clear(), Nokia5110_PrintBMP()
 * @brief  Initialize LCD driver
 */
void Nokia5110_Init(void);

/**
 * Print a character to the Nokia 5110 48x84 LCD.  The
 * character will be printed at the current cursor position,
 * the cursor will automatically be updated, and it will
 * wrap to the next row or back to the top if necessary.
 * One blank column of pixels will be printed on either side
 * of the character for readability.  Since characters are 8
 * pixels tall and 5 pixels wide, 12 characters fit per row,
 * and there are six rows.
 * @param data  character to print
 * @return none
 * @note  LCD is in default horizontal addressing mode (V = 0)
 * @see Nokia5110_Init(), Nokia5110_Clear(), Nokia5110_SetCursor()
 * @brief  Print a character to the LCD
 */
void Nokia5110_OutChar(char data);

/**
 * Print a string of characters to the Nokia 5110 48x84 LCD.
 * The string will automatically wrap, so padding spaces may
 * be needed to make the output look optimal.
 * @param ptr  pointer to NULL-terminated ASCII string
 * @return none
 * @note  LCD is in default horizontal addressing mode (V = 0)
 * @see Nokia5110_Init(), Nokia5110_Clear(), Nokia5110_SetCursor()
 * @brief  Print a string of characters to the LCD
 */
void Nokia5110_OutString(char *ptr);

/**
 * Output a 16-bit number in unsigned decimal format with a
 * fixed size of five right-justified digits of output.
 * @param n  16-bit unsigned number
 * @return none
 * @note  LCD is in default horizontal addressing mode (V = 0)
 * @see Nokia5110_Init(), Nokia5110_Clear(), Nokia5110_SetCursor()
 * @brief  Print a 16-bit unsigned number to the LCD
 */
void Nokia5110_OutUDec(uint16_t n);

/**
 * Output a 16-bit number in signed decimal format with a
 * fixed size of six right-justified digits of output.
 * @param n  16-bit signed number
 * @return none
 * @note  LCD is in default horizontal addressing mode (V = 0)
 * @see Nokia5110_Init(), Nokia5110_Clear(), Nokia5110_SetCursor()
 * @brief  Print a 16-bit signed number to the LCD
 */
void Nokia5110_OutSDec(int16_t n);


/**
 * Output a 16-bit number in unsigned 3-digit fixed point, 0.1 resolution
 * fixed size of four right-justified characters.<br>
 * numbers 0 to 999 printed as " 0.0" to "99.9"
 * @param n  16-bit unsigned number
 * @return none
 * @note  LCD is in default horizontal addressing mode (V = 0)
 * @see Nokia5110_Init(), Nokia5110_Clear(), Nokia5110_SetCursor()
 * @brief  Print a 16-bit unsigned fixed-point number to the LCD
 */
void Nokia5110_OutUFix1(uint16_t n);

/**
 * Move the cursor to the desired X- and Y-position.  The
 * next character will be printed here.  X=0 is the leftmost
 * column.  Y=0 is the top row.
 * @param newX  new X-position of the cursor (0<=newX<=11)
 * @param newY  new Y-position of the cursor (0<=newY<=5)
 * @return none
 * @see Nokia5110_Init(), Nokia5110_Clear(), Nokia5110_SetCursor()
 * @brief  Set coordinates of next print
 */
void Nokia5110_SetCursor(uint8_t newX, uint8_t newY);

/**
 * Clear the LCD by writing zeros to the entire screen and
 * reset the cursor to (0,0) (top left corner of screen).
 * @param none
 * @return none
 * @see Nokia5110_Init(), Nokia5110_OutChar(), Nokia5110_SetCursor()
 * @brief  Clear the screen and reset cursor
 */
void Nokia5110_Clear(void);

/**
 * Fill the whole screen by drawing a 48x84 bitmap image.
 * @param ptr  pointer to 504 byte bitmap
 * @return none
 * @note  LCD is in default horizontal addressing mode (V = 0)
 * @see Nokia5110_Init(), Nokia5110_OutChar(), Nokia5110_Clear()
 * @brief  Draw 48x84 formatted bitmap image.
 */
void Nokia5110_DrawFullImage(const uint8_t *ptr);

/**
 * Bitmaps defined above were created for the LM3S1968 or
 * LM3S8962's 4-bit grayscale OLED display.  They also
 * still contain their header data and may contain padding
 * to preserve 4-byte alignment.  This function takes a
 * bitmap in the previously described format and puts its
 * image data in the proper location in the buffer so the
 * image will appear on the screen after the next call to
 *   Nokia5110_DisplayBuffer();
 * The interface and operation of this process is modeled
 * after RIT128x96x4_BMP(x, y, image);
 * @param  xpos      horizontal position of bottom left corner of image, columns from the left edge<br>
 *                     must be less than 84<br>
 *                     0 is on the left; 82 is near the right
 * @param  ypos      vertical position of bottom left corner of image, rows from the top edge<br>
 *                     must be less than 48<br>
 *                     2 is near the top; 47 is at the bottom
 * @param  ptr       pointer to a 16 color BMP image
 * @param  threshold grayscale colors above this number make corresponding pixel 'on'<br>
 *                     0 to 14<br>
 *                     0 is fine for ships, explosions, projectiles, and bunkers
 * @return none
 * @note Call Nokia5110_DisplayBuffer() to see this bitmap.
 * @see Nokia5110_ClearBuffer(), Nokia5110_DisplayBuffer(), Nokia5110_SetPxl()
 * @brief  Put 48x84 unformatted 4-bit color bitmap image in internal screen buffer.
 */
void Nokia5110_PrintBMP(uint8_t xpos, uint8_t ypos, const uint8_t *ptr, uint8_t threshold);

/**
 * There is a buffer in RAM that holds one screen.  This
 * routine clears that buffer.
 * @param none
 * @return none
 * @see Nokia5110_PrintBMP(), Nokia5110_DisplayBuffer(), Nokia5110_SetPxl()
 * @brief  Clear internal screen buffer.
 */
void Nokia5110_ClearBuffer(void);

/**
 * Fill the whole screen by drawing a 48x84 screen image
 * from the RAM buffer.
 * @param none
 * @return none
 * @note  LCD is in default horizontal addressing mode (V = 0)
 * @see Nokia5110_PrintBMP(), Nokia5110_ClearBuffer(), Nokia5110_SetPxl()
 * @brief  Draw internal screen buffer to the display.
 */
void Nokia5110_DisplayBuffer(void);

/**
 * Clear the internal screen buffer pixel at (i, j),
 * turning it off.
 * @param i  the row index  (0 to 47 in this case),    y-coordinate
 * @param j  the column index  (0 to 83 in this case), x-coordinate
 * @return none
 * @note Call Nokia5110_DisplayBuffer() to see this change.
 * @see Nokia5110_ClearBuffer(), Nokia5110_DisplayBuffer(), Nokia5110_SetPxl()
 * @brief  Turn a pixel off in internal screen buffer.
 */
void Nokia5110_ClrPxl(uint32_t i, uint32_t j);

/**
 * Set the internal screen buffer pixel at (i, j),
 * turning it on.
 * @param i  the row index  (0 to 47 in this case),    y-coordinate
 * @param j  the column index  (0 to 83 in this case), x-coordinate
 * @return none
 * @note Call Nokia5110_DisplayBuffer() to see this change.
 * @see Nokia5110_ClearBuffer(), Nokia5110_DisplayBuffer(), Nokia5110_ClrPxl()
 * @brief  Turn a pixel on in internal screen buffer.
 */
void Nokia5110_SetPxl(uint32_t i, uint32_t j);


#endif /* NOKIA5110_H_ */

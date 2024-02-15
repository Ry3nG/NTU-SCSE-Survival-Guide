/*
 * oled.h
 *
 *  Created on: Jul 30, 2021
 *      Author: yrloke
 */

#ifndef INC_OLED_H_
#define INC_OLED_H_

#include "sys.h"
#include "system.h"

//-----------------OLED Definition----------------
#define OLED_SCL_Pin GPIO_PIN_5
#define OLED_SCL_GPIO_Port GPIOE
#define OLED_SDA_Pin GPIO_PIN_6
#define OLED_SDA_GPIO_Port GPIOE
#define OLED_RST_Pin GPIO_PIN_7
#define OLED_RST_GPIO_Port GPIOE
#define OLED_DC_Pin GPIO_PIN_8
#define OLED_DC_GPIO_Port GPIOE

#define OLED_RST_Clr() PEout(7)=0   //RST
#define OLED_RST_Set() PEout(7)=1   //RST

#define OLED_RS_Clr()  PEout(8)=0   //DC
#define OLED_RS_Set()  PEout(8)=1   //DC

#define OLED_SCLK_Clr()  PEout(5)=0   //SCL
#define OLED_SCLK_Set()  PEout(5)=1   //SCL

#define OLED_SDIN_Clr()  PEout(6)=0   //SDA
#define OLED_SDIN_Set()  PEout(6)=1   //SDA
#define OLED_CMD  0	//Write Command
#define OLED_DATA 1	//Write Data

//OLED Control Functions
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size,uint8_t mode);
void OLED_ShowNumber(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
void OLED_ShowString(uint8_t x,uint8_t y,const uint8_t *p);
void OLED_Set_Pos(unsigned char x, unsigned char y);

#endif /* INC_OLED_H_ */

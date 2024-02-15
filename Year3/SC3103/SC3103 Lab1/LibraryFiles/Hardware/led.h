#ifndef __LED_H
#define __LED_H
#include "sys.h"
#include "system.h"

#define LED_TASK_PRIO		3     //Task priority 
#define LED_STK_SIZE 		128   //Task stack size 


/*--------LED control pin--------*/
#define LED_PORT GPIOE
#define LED_PIN GPIO_Pin_10
#define LED PEout(10) 
/*----------------------------------*/

void LED_Init(void);  
void led_task(void *pvParameters);
extern int Led_Count;
#endif

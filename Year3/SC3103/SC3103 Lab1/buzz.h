#ifndef __BUZZER_H
#define __BUZZER_H
#include "sys.h"
#include "system.h"

#define BUZZ_TASK_PRIO		3     //Task priority 
#define BUZZ_STK_SIZE 		128   //Task stack size 

void buzzer_task(void *pvParameters);
void Buzzer_Init(void);

#endif

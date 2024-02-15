#include "led.h"

int Led_Count=5000;

//LED initialization
void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);    //Enable APB Clock
	
  GPIO_InitStructure.GPIO_Pin =  LED_PIN;                  //LED Pin
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;            //Push pull output
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;        //100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(LED_PORT, &GPIO_InitStructure);                    //Initialize LED GPIO
	GPIO_SetBits(LED_PORT,LED_PIN);
}

void led_task(void *pvParameters)
{
    while(1)
    {
      LED=~LED;        //0 on, 1 off   		
      vTaskDelay(Led_Count); //Delay 
    }
}  

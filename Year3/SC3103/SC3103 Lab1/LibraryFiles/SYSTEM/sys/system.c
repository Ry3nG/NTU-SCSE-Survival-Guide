#include "system.h"


void systemInit(void)
{       

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	delay_init(168);			                                            
	
	//Initialize the hardware interface connected to the LED lamp
	LED_Init();  
	          
}

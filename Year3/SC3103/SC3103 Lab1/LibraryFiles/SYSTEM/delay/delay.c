#include "delay.h"
#include "sys.h"
////////////////////////////////////////////////////////////////////////////////// 	 

#if SYSTEM_SUPPORT_OS
#include "FreeRTOS.h"						  
#include "task.h"
#endif


static u8  fac_us=0;							//number of ticks per us	   
static u16 fac_ms=0;							//number of ticks per ms

static u32 sysTickCnt=0;
extern void xPortSysTickHandler(void);
 
//SysTick Handler when OS is in use
void SysTick_Handler(void)
{	
    if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)
    {
        xPortSysTickHandler();	
    }
}

u32 getSysTickCnt(void)
{
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)	/*系统已经运行*/
		return xTaskGetTickCount();
	else
		return sysTickCnt;
}		   

/**************************************************************************
Delay Initialization
**************************************************************************/
void delay_init(u8 SYSCLK)
{
	u32 reload;
 	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK); //Select Clock HCLK
	fac_us=SYSCLK;							//define number of tick in one us
	reload=SYSCLK;							//reload number of tick	   
	reload*=1000000/configTICK_RATE_HZ;		//configTICK_RATE_HZ
										                  	//reload 24bit register, 16777216
	fac_ms=1000/configTICK_RATE_HZ;			//define number of tick in one ms	   
	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;//Enable SYSTICK Interrupt
	SysTick->LOAD=reload; 					//Every 1/configTICK_RATE_HZ s	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk; //Enable SYSTICK     
}								    

/**************************************************************************
us delay function
**************************************************************************/  								   
void delay_us(u32 nus)
{		
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;				//LOAD value	    	 
	ticks=nus*fac_us; 						//require number of ticks 
	told=SysTick->VAL;        			//current tick
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;	//SYSTICK is a count down timer
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;			//exit when tick exceed target ticks
		}  
	};										    
} 

/**************************************************************************
ms delay function
**************************************************************************/  
void delay_ms(u32 nms)
{	
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)//RTOS Scheduler is started
	{		
		if(nms>=fac_ms)						 
		{ 
   			vTaskDelay(nms/fac_ms);	 		//require ticks
		}
		nms%=fac_ms;						
	}
	else
	delay_us((u32)(nms*1000));				//normal delay
}

//Delay without task scheduler
void delay_xms(u32 nms)
{
	u32 i;
	for(i=0;i<nms;i++) delay_us(1000);
}

			 




































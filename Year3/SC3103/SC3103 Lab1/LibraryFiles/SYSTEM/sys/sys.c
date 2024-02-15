#include "sys.h"  


//Wait For Interrupt
__asm void WFI_SET(void)
{
	WFI;		  
}
//Disable all interrupts
__asm void INTX_DISABLE(void)
{
	CPSID   I
	BX      LR	  
}
//Enable all interrupts
__asm void INTX_ENABLE(void)
{
	CPSIE   I
	BX      LR  
}
//Set stack address
//addr:store at r0
__asm void MSR_MSP(u32 addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}

















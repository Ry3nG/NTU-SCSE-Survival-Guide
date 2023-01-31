/******************************************************************************
* 
*  Copyright (C) 2012 - 2016 Texas Instruments Incorporated - http://www.ti.com/ 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
* 
*   Redistributions of source code must retain the above copyright 
*   notice, this list of conditions and the following disclaimer.
* 
*   Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the 
*   documentation and/or other materials provided with the   
*   distribution.
* 
*   Neither the name of Texas Instruments Incorporated nor the names of
*   its contributors may be used to endorse or promote products derived
*   from this software without specific prior written permission.
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
* 
*  MSP432P401R Interrupt Vector Table
* 
*****************************************************************************/

#include <stdint.h>

/* Linker variable that marks the top of the stack. */
extern unsigned long __STACK_END;

/* External declaration for the reset handler that is to be called when the */
/* processor is started                                                     */
extern void _c_int00(void);

/* External declaration for system initialization function                  */
extern void SystemInit(void);

/* Forward declaration of the default fault handlers. */
void Default_Handler            (void) __attribute__((weak));
extern void Reset_Handler       (void) __attribute__((weak));

/* Cortex-M4 Processor Exceptions */
extern void NMI_Handler         (void) __attribute__((weak, alias("Default_Handler")));
extern void HardFault_Handler   (void) __attribute__((weak, alias("Default_Handler")));
extern void MemManage_Handler   (void) __attribute__((weak, alias("Default_Handler")));
extern void BusFault_Handler    (void) __attribute__((weak, alias("Default_Handler")));
extern void UsageFault_Handler  (void) __attribute__((weak, alias("Default_Handler")));
extern void SVC_Handler         (void) __attribute__((weak, alias("Default_Handler")));
extern void DebugMon_Handler    (void) __attribute__((weak, alias("Default_Handler")));
extern void PendSV_Handler      (void) __attribute__((weak, alias("Default_Handler")));

/* device specific interrupt handler */
extern void SysTick_Handler     (void) __attribute__((weak,alias("Default_Handler")));
extern void PSS_IRQHandler      (void) __attribute__((weak,alias("Default_Handler")));
extern void CS_IRQHandler       (void) __attribute__((weak,alias("Default_Handler")));
extern void PCM_IRQHandler      (void) __attribute__((weak,alias("Default_Handler")));
extern void WDT_A_IRQHandler    (void) __attribute__((weak,alias("Default_Handler")));
extern void FPU_IRQHandler      (void) __attribute__((weak,alias("Default_Handler")));
extern void FLCTL_IRQHandler    (void) __attribute__((weak,alias("Default_Handler")));
extern void COMP_E0_IRQHandler  (void) __attribute__((weak,alias("Default_Handler")));
extern void COMP_E1_IRQHandler  (void) __attribute__((weak,alias("Default_Handler")));
extern void TA0_0_IRQHandler    (void) __attribute__((weak,alias("Default_Handler")));
extern void TA0_N_IRQHandler    (void) __attribute__((weak,alias("Default_Handler")));
extern void TA1_0_IRQHandler    (void) __attribute__((weak,alias("Default_Handler")));
extern void TA1_N_IRQHandler    (void) __attribute__((weak,alias("Default_Handler")));
extern void TA2_0_IRQHandler    (void) __attribute__((weak,alias("Default_Handler")));
extern void TA2_N_IRQHandler    (void) __attribute__((weak,alias("Default_Handler")));
extern void TA3_0_IRQHandler    (void) __attribute__((weak,alias("Default_Handler")));
extern void TA3_N_IRQHandler    (void) __attribute__((weak,alias("Default_Handler")));
extern void EUSCIA0_IRQHandler  (void) __attribute__((weak,alias("Default_Handler")));
extern void EUSCIA1_IRQHandler  (void) __attribute__((weak,alias("Default_Handler")));
extern void EUSCIA2_IRQHandler  (void) __attribute__((weak,alias("Default_Handler")));
extern void EUSCIA3_IRQHandler  (void) __attribute__((weak,alias("Default_Handler")));
extern void EUSCIB0_IRQHandler  (void) __attribute__((weak,alias("Default_Handler")));
extern void EUSCIB1_IRQHandler  (void) __attribute__((weak,alias("Default_Handler")));
extern void EUSCIB2_IRQHandler  (void) __attribute__((weak,alias("Default_Handler")));
extern void EUSCIB3_IRQHandler  (void) __attribute__((weak,alias("Default_Handler")));
extern void ADC14_IRQHandler    (void) __attribute__((weak,alias("Default_Handler")));
extern void T32_INT1_IRQHandler (void) __attribute__((weak,alias("Default_Handler")));
extern void T32_INT2_IRQHandler (void) __attribute__((weak,alias("Default_Handler")));
extern void T32_INTC_IRQHandler (void) __attribute__((weak,alias("Default_Handler")));
extern void AES256_IRQHandler   (void) __attribute__((weak,alias("Default_Handler")));
extern void RTC_C_IRQHandler    (void) __attribute__((weak,alias("Default_Handler")));
extern void DMA_ERR_IRQHandler  (void) __attribute__((weak,alias("Default_Handler")));
extern void DMA_INT3_IRQHandler (void) __attribute__((weak,alias("Default_Handler")));
extern void DMA_INT2_IRQHandler (void) __attribute__((weak,alias("Default_Handler")));
extern void DMA_INT1_IRQHandler (void) __attribute__((weak,alias("Default_Handler")));
extern void DMA_INT0_IRQHandler (void) __attribute__((weak,alias("Default_Handler")));
extern void PORT1_IRQHandler    (void) __attribute__((weak,alias("Default_Handler")));
extern void PORT2_IRQHandler    (void) __attribute__((weak,alias("Default_Handler")));
extern void PORT3_IRQHandler    (void) __attribute__((weak,alias("Default_Handler")));
extern void PORT4_IRQHandler    (void) __attribute__((weak,alias("Default_Handler")));
extern void PORT5_IRQHandler    (void) __attribute__((weak,alias("Default_Handler")));
extern void PORT6_IRQHandler    (void) __attribute__((weak,alias("Default_Handler")));

/* Interrupt vector table.  Note that the proper constructs must be placed on this to */
/* ensure that it ends up at physical address 0x0000.0000 or at the start of          */
/* the program if located at a start address other than 0.                            */
#pragma RETAIN(interruptVectors)
#pragma DATA_SECTION(interruptVectors, ".intvecs")
void (* const interruptVectors[])(void) =
{
    (void (*)(void))((uint32_t)&__STACK_END),
                                           /* The initial stack pointer */
    Reset_Handler,                         /* The reset handler         */
    NMI_Handler,                           /* The NMI handler           */
    HardFault_Handler,                     /* The hard fault handler    */
    MemManage_Handler,                     /* The MPU fault handler     */
    BusFault_Handler,                      /* The bus fault handler     */
    UsageFault_Handler,                    /* The usage fault handler   */
    0,                                     /* Reserved                  */
    0,                                     /* Reserved                  */
    0,                                     /* Reserved                  */
    0,                                     /* Reserved                  */
    SVC_Handler,                           /* SVCall handler            */
    DebugMon_Handler,                      /* Debug monitor handler     */
    0,                                     /* Reserved                  */
    PendSV_Handler,                        /* The PendSV handler        */
    SysTick_Handler,                       /* The SysTick handler       */
    PSS_IRQHandler,                        /* PSS ISR                   */
    CS_IRQHandler,                         /* CS ISR                    */
    PCM_IRQHandler,                        /* PCM ISR                   */
    WDT_A_IRQHandler,                      /* WDT ISR                   */
    FPU_IRQHandler,                        /* FPU ISR                   */
    FLCTL_IRQHandler,                      /* FLCTL ISR                 */
    COMP_E0_IRQHandler,                    /* COMP0 ISR                 */
    COMP_E1_IRQHandler,                    /* COMP1 ISR                 */
    TA0_0_IRQHandler,                      /* TA0_0 ISR                 */
    TA0_N_IRQHandler,                      /* TA0_N ISR                 */
    TA1_0_IRQHandler,                      /* TA1_0 ISR                 */
    TA1_N_IRQHandler,                      /* TA1_N ISR                 */
    TA2_0_IRQHandler,                      /* TA2_0 ISR                 */
    TA2_N_IRQHandler,                      /* TA2_N ISR                 */
    TA3_0_IRQHandler,                      /* TA3_0 ISR                 */
    TA3_N_IRQHandler,                      /* TA3_N ISR                 */
    EUSCIA0_IRQHandler,                    /* EUSCIA0 ISR               */
    EUSCIA1_IRQHandler,                    /* EUSCIA1 ISR               */
    EUSCIA2_IRQHandler,                    /* EUSCIA2 ISR               */
    EUSCIA3_IRQHandler,                    /* EUSCIA3 ISR               */
    EUSCIB0_IRQHandler,                    /* EUSCIB0 ISR               */
    EUSCIB1_IRQHandler,                    /* EUSCIB1 ISR               */
    EUSCIB2_IRQHandler,                    /* EUSCIB2 ISR               */
    EUSCIB3_IRQHandler,                    /* EUSCIB3 ISR               */
    ADC14_IRQHandler,                      /* ADC14 ISR                 */
    T32_INT1_IRQHandler,                   /* T32_INT1 ISR              */
    T32_INT2_IRQHandler,                   /* T32_INT2 ISR              */
    T32_INTC_IRQHandler,                   /* T32_INTC ISR              */
    AES256_IRQHandler,                     /* AES ISR                   */
    RTC_C_IRQHandler,                      /* RTC ISR                   */
    DMA_ERR_IRQHandler,                    /* DMA_ERR ISR               */
    DMA_INT3_IRQHandler,                   /* DMA_INT3 ISR              */
    DMA_INT2_IRQHandler,                   /* DMA_INT2 ISR              */
    DMA_INT1_IRQHandler,                   /* DMA_INT1 ISR              */
    DMA_INT0_IRQHandler,                   /* DMA_INT0 ISR              */
    PORT1_IRQHandler,                      /* PORT1 ISR                 */
    PORT2_IRQHandler,                      /* PORT2 ISR                 */
    PORT3_IRQHandler,                      /* PORT3 ISR                 */
    PORT4_IRQHandler,                      /* PORT4 ISR                 */
    PORT5_IRQHandler,                      /* PORT5 ISR                 */
    PORT6_IRQHandler                       /* PORT6 ISR                 */
};

/* Forward declaration of the default fault handlers. */
/* This is the code that gets called when the processor first starts execution */
/* following a reset event.  Only the absolutely necessary set is performed,   */
/* after which the application supplied entry() routine is called.  Any fancy  */
/* actions (such as making decisions based on the reset cause register, and    */
/* resetting the bits in that register) are left solely in the hands of the    */
/* application.                                                                */
void Reset_Handler(void)
{
    SystemInit();

    /* Jump to the CCS C Initialization Routine. */
    __asm("    .global _c_int00\n"
          "    b.w     _c_int00");
}


/* This is the code that gets called when the processor receives an unexpected  */
/* interrupt.  This simply enters an infinite loop, preserving the system state */
/* for examination by a debugger.                                               */
void Default_Handler(void)
{
    /* Fault trap exempt from ULP advisor */
    #pragma diag_push
    #pragma CHECK_ULP("-2.1")

	/* Enter an infinite loop. */
	while(1)
	{
	}

	#pragma diag_pop
}

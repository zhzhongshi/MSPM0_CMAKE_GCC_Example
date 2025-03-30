#include <stdint.h>

extern void SystemInit(void);
extern int  main( void );

extern uint32_t __data_load__;
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __ramfunct_load__;
extern uint32_t __ramfunct_start__;
extern uint32_t __ramfunct_end__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;
extern uint32_t __StackTop;

typedef void( *pFunc )( void );

/* Forward declaration of the default fault handlers. */
void Default_Handler(void);
extern void Reset_Handler       (void) __attribute__((weak));
extern void __libc_init_array(void);
extern void _init               (void) __attribute__((weak, alias("initStub")));
void initStub(void){;}

/* Processor Exceptions */
extern void NMI_Handler         (void) __attribute__((weak, alias("Default_Handler")));
extern void HardFault_Handler   (void) __attribute__((weak, alias("Default_Handler")));
extern void SVC_Handler         (void) __attribute__((weak, alias("Default_Handler")));
extern void PendSV_Handler      (void) __attribute__((weak, alias("Default_Handler")));
extern void SysTick_Handler     (void) __attribute__((weak, alias("Default_Handler")));

/* Device Specific Interrupt Handlers */
extern void GROUP0_IRQHandler   (void) __attribute__((weak, alias("Default_Handler")));
extern void GROUP1_IRQHandler   (void) __attribute__((weak, alias("Default_Handler")));
extern void TIMG8_IRQHandler    (void) __attribute__((weak, alias("Default_Handler")));
extern void UART3_IRQHandler    (void) __attribute__((weak, alias("Default_Handler")));
extern void ADC0_IRQHandler     (void) __attribute__((weak, alias("Default_Handler")));
extern void ADC1_IRQHandler     (void) __attribute__((weak, alias("Default_Handler")));
extern void CANFD0_IRQHandler   (void) __attribute__((weak, alias("Default_Handler")));
extern void DAC0_IRQHandler     (void) __attribute__((weak, alias("Default_Handler")));
extern void SPI0_IRQHandler     (void) __attribute__((weak, alias("Default_Handler")));
extern void SPI1_IRQHandler     (void) __attribute__((weak, alias("Default_Handler")));
extern void UART1_IRQHandler    (void) __attribute__((weak, alias("Default_Handler")));
extern void UART2_IRQHandler    (void) __attribute__((weak, alias("Default_Handler")));
extern void UART0_IRQHandler    (void) __attribute__((weak, alias("Default_Handler")));
extern void TIMG0_IRQHandler    (void) __attribute__((weak, alias("Default_Handler")));
extern void TIMG6_IRQHandler    (void) __attribute__((weak, alias("Default_Handler")));
extern void TIMA0_IRQHandler    (void) __attribute__((weak, alias("Default_Handler")));
extern void TIMA1_IRQHandler    (void) __attribute__((weak, alias("Default_Handler")));
extern void TIMG7_IRQHandler    (void) __attribute__((weak, alias("Default_Handler")));
extern void TIMG12_IRQHandler   (void) __attribute__((weak, alias("Default_Handler")));
extern void I2C0_IRQHandler     (void) __attribute__((weak, alias("Default_Handler")));
extern void I2C1_IRQHandler     (void) __attribute__((weak, alias("Default_Handler")));
extern void AES_IRQHandler      (void) __attribute__((weak, alias("Default_Handler")));
extern void RTC_IRQHandler      (void) __attribute__((weak, alias("Default_Handler")));
extern void DMA_IRQHandler      (void) __attribute__((weak, alias("Default_Handler")));


void (* const interruptVectors[])(void) __attribute__ ((used)) __attribute__ ((section (".intvecs"))) =
{
    (pFunc)&__StackTop,                    /* The initial stack pointer */
    Reset_Handler,                         /* The reset handler         */
    NMI_Handler,                           /* The NMI handler           */
    HardFault_Handler,                     /* The hard fault handler    */
    0,                                     /* Reserved                  */
    0,                                     /* Reserved                  */
    0,                                     /* Reserved                  */
    0,                                     /* Reserved                  */
    0,                                     /* Reserved                  */
    0,                                     /* Reserved                  */
    0,                                     /* Reserved                  */
    SVC_Handler,                           /* SVCall handler            */
    0,                                     /* Reserved                  */
    0,                                     /* Reserved                  */
    PendSV_Handler,                        /* The PendSV handler        */
    SysTick_Handler,                       /* SysTick handler           */
    GROUP0_IRQHandler,                     /* GROUP0 interrupt handler  */
    GROUP1_IRQHandler,                     /* GROUP1 interrupt handler  */
    TIMG8_IRQHandler,                      /* TIMG8 interrupt handler   */
    UART3_IRQHandler,                      /* UART3 interrupt handler   */
    ADC0_IRQHandler,                       /* ADC0 interrupt handler    */
    ADC1_IRQHandler,                       /* ADC1 interrupt handler    */
    CANFD0_IRQHandler,                     /* CANFD0 interrupt handler  */
    DAC0_IRQHandler,                       /* DAC0 interrupt handler    */
    0,                                     /* Reserved                  */
    SPI0_IRQHandler,                       /* SPI0 interrupt handler    */
    SPI1_IRQHandler,                       /* SPI1 interrupt handler    */
    0,                                     /* Reserved                  */
    0,                                     /* Reserved                  */
    UART1_IRQHandler,                      /* UART1 interrupt handler   */
    UART2_IRQHandler,                      /* UART2 interrupt handler   */
    UART0_IRQHandler,                      /* UART0 interrupt handler   */
    TIMG0_IRQHandler,                      /* TIMG0 interrupt handler   */
    TIMG6_IRQHandler,                      /* TIMG6 interrupt handler   */
    TIMA0_IRQHandler,                      /* TIMA0 interrupt handler   */
    TIMA1_IRQHandler,                      /* TIMA1 interrupt handler   */
    TIMG7_IRQHandler,                      /* TIMG7 interrupt handler   */
    TIMG12_IRQHandler,                     /* TIMG12 interrupt handler  */
    0,                                     /* Reserved                  */
    0,                                     /* Reserved                  */
    I2C0_IRQHandler,                       /* I2C0 interrupt handler    */
    I2C1_IRQHandler,                       /* I2C1 interrupt handler    */
    0,                                     /* Reserved                  */
    0,                                     /* Reserved                  */
    AES_IRQHandler,                        /* AES interrupt handler     */
    0,                                     /* Reserved                  */
    RTC_IRQHandler,                        /* RTC interrupt handler     */
    DMA_IRQHandler,                        /* DMA interrupt handler     */

};


void Reset_Handler(void)
{
    uint32_t *pui32Src, *pui32Dest;
    uint32_t *bs, *be;

    //
    // Copy the data segment initializers from flash to SRAM.
    //
    pui32Src = &__data_load__;
    for(pui32Dest = &__data_start__; pui32Dest < &__data_end__; )
    {
        *pui32Dest++ = *pui32Src++;
    }

    //
    // Copy the ramfunct segment initializers from flash to SRAM.
    //
    pui32Src = &__ramfunct_load__;
    for(pui32Dest = &__ramfunct_start__; pui32Dest < &__ramfunct_end__; )
    {
        *pui32Dest++ = *pui32Src++;
    }

    // Initialize .bss to zero
    bs = &__bss_start__;
    be = &__bss_end__;
    while (bs < be)
    {
        *bs = 0;
        bs++;
    }

    /*
     * System initialization routine can be called here, but it's not
     * required for MSPM0.
     */
    // SystemInit();

	//
	// Initialize virtual tables, along executing init, init_array, constructors
	// and preinit_array functions
	//
	__libc_init_array();
    main();
    HardFault_Handler();
}

void Default_Handler(void)
{
    /* Enter an infinite loop. */
    while(1)
    {
    }
}

#define RCC_APB2PCENR               (*(volatile unsigned int*)0x40021018)   // PB2 Peripheral Clock Enable Register
#define RCC_APB2PCENR_USART1EN      (0b1 << 14)     // USART1 interface clock enable bit
#define RCC_APB2PCENR_IOPDRST       (0b1 << 5)      // PD port module reset control for I/O.
#define RCC_APB2PCENR_AFIORST       (0b1 << 0)      // I/O auxiliary function module reset control.

#define USART_BASE                  ((volatile unsigned int*)0x40013800)
#define USART_STAT                  (*(USART_BASE + 0x00)) // USART status register                
#define USART_DATA                  (*(USART_BASE + 0x04)) // USART data register
#define USART_BRR                   (*(USART_BASE + 0x08)) // USART baudrate register
#define USART_BRR_DIVM(M)           (M << 4)            // The integer part of the dividing factor of the frequency divider. 
#define USART_BRR_DIVF(F)           (F << 0)            // The actional part of the dividing factor of the frequency divider. 
#define USART_CTRL1                 (*(USART_BASE + 0x0C)) // USART control register 1
#define USART_CTRL2                 (*(USART_BASE + 0x10)) // USART control register 2
#define USART_CTRL3                 (*(USART_BASE + 0x14)) // USART control register 3
#define USART_GPR                   (*(USART_BASE + 0x18)) // USART potection time and prescaler register



int main(void) {

    RCC_APB2PCENR |= (RCC_APB2PCENR_USART1EN | RCC_APB2PCENR_AFIORST | RCC_APB2PCENR_IOPDRST);

    USART_BRR |= (USART_BRR_DIVM(0xC) | USART_BRR_DIVF(0xF));
}
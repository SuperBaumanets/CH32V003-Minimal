#define RCC_APB2PCENR               (*(volatile unsigned int*)0x40021018)   // PB2 Peripheral Clock Enable Register
#define RCC_APB2PCENR_USART1EN      (0b1 << 14)     // USART1 interface clock enable bit
#define RCC_APB2PCENR_IOPDRST       (0b1 << 5)      // PD port module reset control for I/O.
#define RCC_APB2PCENR_AFIORST       (0b1 << 0)      // I/O auxiliary function module reset control.

#define USART_BASE                  0x40013800
#define USART_STAT                  (*(volatile unsigned int*)(USART_BASE + 0x00)) // USART status register                
#define USART_STAT_TXE_MASK         0b1
#define USART_DATA                  (*(volatile unsigned int*)(USART_BASE + 0x04)) // USART data register
#define USART_BRR                   (*(volatile unsigned int*)(USART_BASE + 0x08)) // USART baudrate register
#define USART_BRR_DIVM(M)           (M << 4)            // The integer part of the dividing factor of the frequency divider. 
#define USART_BRR_DIVF(F)           (F << 0)            // The actional part of the dividing factor of the frequency divider. 
#define USART_CTRL1                 (*(volatile unsigned int*)(USART_BASE + 0x0C)) // USART control register 1
#define USART_CTRL1_M               (0b1 << 12)         // Word long bit
#define USART_CTRL1_TE              (0b1 << 3)          // Transmitter enable
#define USART_CTRL2                 (*(volatile unsigned int*)(USART_BASE + 0x10)) // USART control register 2
#define USART_CTRL2_STOP_MASK       ~(0xC << 12)        // MASK STOP bits 
#define USART_CTRL2_STOP            (0b00 << 12)        // STOP bits
#define USART_CTRL3                 (*(volatile unsigned int*)(USART_BASE + 0x14)) // USART control register 3
#define USART_GPR                   (*(volatile unsigned int*)(USART_BASE + 0x18)) // USART potection time and prescaler register


int main(void) {

    RCC_APB2PCENR |= (RCC_APB2PCENR_USART1EN | RCC_APB2PCENR_IOPDRST | RCC_APB2PCENR_AFIORST);

    USART_BRR = (USART_BRR_DIVM(0xC) | USART_BRR_DIVF(0xF));

    USART_CTRL1 |= (USART_CTRL1_M | USART_CTRL1_TE);

    USART_CTRL2 = (USART_CTRL2 & USART_CTRL2_STOP_MASK) | USART_CTRL2_STOP;
   
    while(1){
    }

}


/*
UART_write(const char *buf, int size)
{
	int rem = size;
	for(int i = 0; i < size; i++)
	{
		UART_putc(*buf++);
	    rem--;
	}
	return rem;
}

void UART_putc(uint8_t data)
{
    uint8_t tmp8;    
    tmp8  = (uart_txHead+ 1) & UART_TX_BF_MASK;
    while (tmp8 == uart_txTail);
    uart_tx_bf[tmp8] = data;
	uart_txHead = tmp8;
	USART1->CTLR1 |= UART_IT_TXE_ENABLE;
}
*/
#define RCC_CTLR_BASE               0x40021000

#define RCC_CTLR                    (*((volatile unsigned int*)(RCC_CTLR_BASE + 0x00)))   // Clock control register

#define RCC_CTRL_PLL_MASK           ~(0b1 << 24)    // Mask PLL clock enable bit
#define RCC_CTLR_PLLON              (0b1 << 24)     // PLL clock enable control bit.  Enables the PLL clock
#define RCC_CTLR_PLLOFF             (0b0 << 24)     // PLL clock enable control bit.  Turn off the PLL clock

#define RCC_CTRL_PLLRDY             (0b1 << 25)     // PLL clock-ready lock flag bit.
#define RCC_CTRL_HSIRDY             (0b1 << 1)      // Internal high-speed clock (24MHz) Stable Ready

#define RCC_CFGR0                   (*(volatile unsigned int*)(RCC_CTLR_BASE + 0x04))   // Clock configuration register 0

#define RCC_CFGR0_PLLSRC_MASK       ~(0b1 << 16)    // Mask input clock source for PLL
#define RCC_CFGR0_PLLSRC            (0xb0 << 16)    // HSI HSI is not divided and sent to PLL

#define RCC_CFGR0_SW_MASK           ~(0x3 << 0)     // MASK select the system clock source.
#define RCC_CFGR0_SW                (0b10 << 0)     // Select the system clock source. PLL output as system clock

#define RCC_CFGR0_HPRE_MASK         ~(0xF << 4)     // Mask HB clock source prescaler control.
#define RCC_CFGR0_HPRE              (0xb0000 << 4)  // Prescaler off

#define RCC_CFGR0_SWS               (0b11 << 2)     // System clock (SYSCLK) status (hardware set) Not available
#define RCC_CFGR0_SWS_PLL           (0b10 << 2)     // The system clock source is a PLL


#define RCC_APB2PCENR               (*(volatile unsigned int*)(RCC_CTLR_BASE + 0x18))   // PB2 Peripheral Clock Enable Register

#define RCC_APB2PCENR_USART1EN_MASK ~(0b1 << 14)    // MASK USART1 interface clock enable bit
#define RCC_APB2PCENR_USART1EN      (0b1 << 14)     // USART1 interface clock enable bit

#define RCC_APB2PCENR_IOPDRST_MASK  ~(0b1 << 5)     // PD port module reset control for I/O.
#define RCC_APB2PCENR_IOPDRST       (0b1 << 5)      // PD port module reset control for I/O.


#define USART_PD_TX                  5              // USART TX PD5


#define GPIOD_CFGLR                 (*(volatile unsigned int*)0x40011400)   // PD port configuration register low

#define GPIOD_CFGLR_TX_MASK         ~(0xF << (4 * USART_PD_TX))             // Mask MODE5 and CNF5
#define GPIOD_CFGLR_TX_MODE         0b01            // Output mode, maximum speed 10MHz
#define GPIOD_CFGLR_TX_CNF          0b10            // Multiplexed function push-pull output mode.
#define GPIOD_CFGLR_TX_SET          ((GPIOD_CFGLR_TX_CNF | GPIOD_CFGLR_TX_MODE) << (4 * USART_PD_TX))


#define USART_BASE                  0x40013800

#define USART_STAT                  (*(volatile unsigned int*)(USART_BASE + 0x00)) // USART status register                
#define USART_STAT_TC               (0b1 << 6)      // Send completion flag

#define USART_DATA                  (*(volatile unsigned int*)(USART_BASE + 0x04)) // USART data register

#define USART_BRR                   (*(volatile unsigned int*)(USART_BASE + 0x08)) // USART baudrate register
#define USART_BRR_DIVM(M)           (M << 4)        // The integer part of the dividing factor of the frequency divider. 
#define USART_BRR_DIVF(F)           (F << 0)        // The actional part of the dividing factor of the frequency divider. 

#define USART_CTRL1                 (*(volatile unsigned int*)(USART_BASE + 0x0C)) // USART control register 1

#define USART_CTRL1_UE_MASK         ~(0b1 << 13)    // Mask USART enable bit
#define USART_CTRL1_UE_E            (0b1 << 13)     // USART enable bit enable
#define USART_CTRL1_UE_C            (0b0 << 13)     // USART enable bit clear

#define USART_CTRL1_M_MASK         ~(0b1 << 12)     // Mask USART enable bit   
#define USART_CTRL1_M               (0b0 << 12)     // Word long bit. 8 data bits. 

#define USART_CTRL1_TXE_MASK        ~(0b1 << 3)     // Mask Transmitter enable
#define USART_CTRL1_TXE             (0b1 << 3)      // Transmitter enable

#define USART_CTRL2                 (*(volatile unsigned int*)(USART_BASE + 0x10)) // USART control register 2
#define USART_CTRL2_STOP_MASK       ~(0xC << 12)    // Mask STOP bits 
#define USART_CTRL2_STOP            (0b00 << 12)    // STOP bits

//static const unsigned char data_s = 'w';

int main(void) {

    // Setup PLL clock
    // Turn off PLL
    RCC_CTLR = (RCC_CTLR & RCC_CTRL_PLL_MASK) | RCC_CTLR_PLLOFF;
    
    // Wait for HSI is ready
    while((RCC_CTLR & RCC_CTRL_HSIRDY)){}

    // Setup HSI for clock source for PLL
    RCC_CFGR0 = (RCC_CFGR0 & RCC_CFGR0_PLLSRC_MASK) | RCC_CFGR0_PLLSRC;
    // Turn on PLL
    RCC_CTLR = (RCC_CTLR & RCC_CTRL_PLL_MASK) | RCC_CTLR_PLLON;

    // Setup SYSCLK
    // Wait till PLL is ready
    while(!(RCC_CTLR & (unsigned int)RCC_CTRL_PLLRDY)){}
    RCC_CFGR0 = (RCC_CFGR0 & RCC_CFGR0_SW_MASK) | RCC_CFGR0_SW;
    //TODO Wait till PLL is used as system clock source
    while ((RCC_CFGR0 & RCC_CFGR0_SWS) != RCC_CFGR0_SWS_PLL ){}

    // Set HB clock source prescaler off
    RCC_CFGR0 = (RCC_CFGR0 & RCC_CFGR0_HPRE_MASK) | RCC_CFGR0_HPRE;

    // Setup PB2 peripheral clock
    RCC_APB2PCENR = (RCC_APB2PCENR & RCC_APB2PCENR_USART1EN_MASK) | RCC_APB2PCENR_USART1EN;
    RCC_APB2PCENR = (RCC_APB2PCENR & RCC_APB2PCENR_IOPDRST_MASK) | RCC_APB2PCENR_IOPDRST;

    // Setup GPIO
    GPIOD_CFGLR = (GPIOD_CFGLR & GPIOD_CFGLR_TX_MASK) | GPIOD_CFGLR_TX_SET;

    // Setup UART
    // Setup baudrate
    USART_BRR = (USART_BRR_DIVM(0x138) | USART_BRR_DIVF(0x8));
    // Disable UART
    USART_CTRL1 = (USART_CTRL1 & USART_CTRL1_UE_MASK) | USART_CTRL1_UE_C;
    // 8 data bits
    USART_CTRL1 = (USART_CTRL1 & USART_CTRL1_M_MASK) | USART_CTRL1_M;
    // Enable transmitter
    USART_CTRL1 = (USART_CTRL1 & USART_CTRL1_TXE_MASK) | USART_CTRL1_TXE; 
    // 1 stop bit
    USART_CTRL2 = (USART_CTRL2 & USART_CTRL2_STOP_MASK) | USART_CTRL2_STOP;
    // Enable UART
    USART_CTRL1 = (USART_CTRL1 & USART_CTRL1_UE_MASK) | USART_CTRL1_UE_E;
    
    while(1){
       
        while(!(USART_STAT & USART_STAT_TC));
        USART_DATA = 0xffffffff;

        for(unsigned int i = 0; i < 10000; i++){
            asm volatile("nop");
        }
    }
    
}

/*
RCC_APB2PCENR = 0b 00000000 00000000 01011010 00110101;
> wlink dump 0x40021018 4
> 35 5a 00 00
                   00000000 00000000 01011010 00110101
                                      (0x5a)   (0x35)
*/

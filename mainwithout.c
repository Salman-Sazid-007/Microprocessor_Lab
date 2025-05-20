#define RCC_base     0x40021000
#define GPIOC_base   0x40011000

#define RCC_APB2ENR  (*(volatile unsigned int*)(RCC_base + 0x18))
#define GPIOC_CRH    (*(volatile unsigned int*)(GPIOC_base + 0x04))
#define GPIOC_ODR    (*(volatile unsigned int*)(GPIOC_base + 0x0C))

void delay(unsigned int ms){
    for(unsigned int i = 0; i < ms * 1000; i++) {
        __asm__("nop");
    }
}

int main(void){
    // Enable GPIOC clock (bit 4)
    RCC_APB2ENR |= (1 << 4);

    // Configure PC13 as output (MODE13 = 10, CNF13 = 00)
    GPIOC_CRH &= ~(0xF << 20);    // Clear bits 23:20
    GPIOC_CRH |=  (0x2 << 20);    // MODE13 = 10 (2 MHz), CNF13 = 00

    while(1){
        GPIOC_ODR ^= (1 << 13);   // Toggle PC13
        delay(1000);              // ~1s delay
    }
}

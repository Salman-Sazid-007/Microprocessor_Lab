#define RCC_base     0x40021000
#define GPIOC_base   0x40011000
#define TIM1_base    0x40012C00

#define RCC_APB2ENR (*(volatile unsigned int*)(RCC_base + 0x18))
#define GPIOC_CRH   (*(volatile unsigned int*)(GPIOC_base + 0x04))
#define GPIOC_ODR   (*(volatile unsigned int*)(GPIOC_base + 0x0C))

#define TIM1_CR1    (*(volatile unsigned int*)(TIM1_base + 0x00))
#define TIM1_PSC    (*(volatile unsigned int*)(TIM1_base + 0x28))
#define TIM1_ARR    (*(volatile unsigned int*)(TIM1_base + 0x2C))
#define TIM1_SR     (*(volatile unsigned int*)(TIM1_base + 0x10))

void TIM1_init(unsigned int prescaler, unsigned int arr_val) {
    RCC_APB2ENR |= (1 << 11); // Enable TIM1
    TIM1_PSC = prescaler;
    TIM1_ARR = arr_val;
    TIM1_CR1 |= (1 << 0);     // Enable TIM1
}

void delay_ms_TIM1(unsigned int ms) {
    TIM1_ARR = ms;
    TIM1_SR &= ~(1 << 0);
    while (!(TIM1_SR & (1 << 0)));
    TIM1_SR &= ~(1 << 0);
}

int main(void) {
    RCC_APB2ENR |= (1 << 4); // Enable GPIOC

    // PC13 as output
    GPIOC_CRH &= 0xFF0FFFFF;
    GPIOC_CRH |= 0x00200000;

    TIM1_init(7999, 1000); // 1ms resolution

    while (1) {
        GPIOC_ODR ^= (1 << 13);
        delay_ms_TIM1(1000); // 1 second
    }
}

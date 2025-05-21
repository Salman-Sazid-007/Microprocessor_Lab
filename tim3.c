#define RCC_base     0x40021000
#define GPIOC_base   0x40011000
#define TIM3_base    0x40000400

#define RCC_APB2ENR (*(volatile unsigned int*)(RCC_base + 0x18))
#define RCC_APB1ENR (*(volatile unsigned int*)(RCC_base + 0x1C))

#define GPIOC_CRH   (*(volatile unsigned int*)(GPIOC_base + 0x04))
#define GPIOC_ODR   (*(volatile unsigned int*)(GPIOC_base + 0x0C))

#define TIM3_CR1    (*(volatile unsigned int*)(TIM3_base + 0x00))
#define TIM3_PSC    (*(volatile unsigned int*)(TIM3_base + 0x28))
#define TIM3_ARR    (*(volatile unsigned int*)(TIM3_base + 0x2C))
#define TIM3_SR     (*(volatile unsigned int*)(TIM3_base + 0x10))

void TIM3_init(unsigned int prescaler, unsigned int arr_val) {
    RCC_APB1ENR |= (1 << 1); // Enable TIM3
    TIM3_PSC = prescaler;
    TIM3_ARR = arr_val;
    TIM3_CR1 |= (1 << 0);    // Enable TIM3
}

void delay_ms_TIM3(unsigned int ms) {
    TIM3_ARR = ms;
    TIM3_SR &= ~(1 << 0);
    while (!(TIM3_SR & (1 << 0)));
    TIM3_SR &= ~(1 << 0);
}

int main(void) {
    RCC_APB2ENR |= (1 << 4); // Enable GPIOC

    // PC13 as output
    GPIOC_CRH &= 0xFF0FFFFF;
    GPIOC_CRH |= 0x00200000;

    TIM3_init(7999, 1000); // 1ms tick

    while (1) {
        GPIOC_ODR ^= (1 << 13);
        delay_ms_TIM3(2000); // 2 seconds
    }
}

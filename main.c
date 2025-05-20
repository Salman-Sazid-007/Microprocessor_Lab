#define RCC_base   0x40021000
#define GPIOC_base  0x40011000
#define TIM2_base   0x40000000



#define RCC_APB2ENR (*(volatile unsigned int*)(RCC_base + 0x18))
#define GPIOC_CRH ( *(volatile unsigned int*)(GPIOC_base + 0x04))
#define GPIOC_ODR ( *(volatile unsigned int*)(GPIOC_base + 0x0C))

#define RCC_APB1ENR (*(volatile unsigned int*)(RCC_base + 0x1C))
#define TIM2_CR1 (*(volatile unsigned int*)(TIM2_base+ 0x00))
#define TIM2_PSC (*(volatile unsigned int*)(TIM2_base+ 0x28))
#define TIM2_ARR (*(volatile unsigned int*)(TIM2_base+ 0x2C))
#define TIM2_SR (*(volatile unsigned int*)(TIM2_base+ 0x10))


void delay(unsigned int ms){
 TIM2_ARR = ms ;
 while(1){
   if(TIM2_SR &(1U<<0)){
    TIM2_SR &=~(1U<<0);
       break;
   }

 }

}


 int main(void){

 //enable peripheral clock

 RCC_APB2ENR |= 0x10;

 // output mode set at 2MHZ 10
 GPIOC_CRH &= 0xFF0FFFFF;
 GPIOC_CRH |= 0XFF2FFFFF;

 RCC_APB1ENR |= 0x1; //set tim2
 TIM2_PSC = 7999;
    TIM2_ARR = 50;

 TIM2_CR1 |=0x1;

 while(1){
  GPIOC_ODR ^= 0x2000;
  delay(1000);

 }



}

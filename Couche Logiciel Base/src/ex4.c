/* Embedded Systems - Exercise 1 */

#include <tinyprintf.h>
#include <stm32f4/rcc.h>
#include <stm32f4/gpio.h>
#include <stm32f4/tim.h>

// GPIOD
#define GREEN_LED	12
#define ORANGE_LED	13
#define RED_LED		14
#define BLUE_LED	15

// GPIODA
#define USER_BUT	0
//timer
#define  DELAY_50MS  4200
#define  DELAY_10MS  4200
volatile int b_state_1=0;
volatile int cmp=0;

int main() {
	printf("Starting...\n");

	// RCC init
	RCC_AHB1ENR |= RCC_GPIOAEN;
	RCC_AHB1ENR |= RCC_GPIODEN;
	RCC_APB1ENR |= RCC_TIM4EN;
	RCC_APB1ENR |= RCC_TIM2EN;

	
	// GPIO GREEN_LED init
	GPIOD_MODER = SET_BITS(GPIOD_MODER, GREEN_LED*2 ,2 ,0b01) ;
	GPIOD_OTYPER = GPIOD_OTYPER & ~( 1 << GREEN_LED ) ;
	GPIOD_PUPDR = SET_BITS (GPIOD_PUPDR , GREEN_LED*2 , 2 , 0b01 );
	GPIOD_BSRR=(1<<(GREEN_LED +16));
        //Button

	GPIOA_MODER = SET_BITS (GPIOA_MODER, USER_BUT*2 , 2 , 0b00 ) ;
	GPIOA_OTYPER = GPIOA_OTYPER & ~ ( 1 << USER_BUT ) ;
	GPIOA_PUPDR = SET_BITS(GPIOA_PUPDR, USER_BUT*2 , 2 , 0b10 ) ;

// Initialisation de Timer 4 & 2
	TIM4_Init() ;

		int last_b1 = 0 ;
		//TIM4_EGR = TIM_UG ;
	while(1){
		  TIM4_SR = 0;
		while((TIM4_SR & TIM_UIF)==0)
		{

			if((GPIOA_IDR & (1<<USER_BUT)) !=0){
				b_state_1=1 ;
                                last_b1=TIM4_CNT;
			}else if(b_state_1){
                           int now=TIM4_CNT;
                            if(now <= last_b1)
			       now +=DELAY_50MS;
			    if((now - last_b1) >=DELAY_50MS){
			       b_state_1=0;
			   }


					}
					//TIM4_SR = 0 ;

				}
	 if(b_state_1){
		 cmp++;

	 }
     if(cmp !=0){

           TIM2_SR = 0 ;
		   GPIOD_BSRR =(1<<GREEN_LED);
             delayMS();
           GPIOD_BSRR =(1<<(GREEN_LED+16));
             delayMS();

          }
		}

}
void TIM4_Init(){

	// configure TIM4 to wrap around at 10 ms
	        TIM4_CR1 = 0 ;
			TIM4_PSC = 1000 - 1; /*divided by 1000 */
			TIM4_ARR = DELAY_50MS-1; /* divided by 10000 */
			TIM4_EGR = TIM_UG; /* clear timer counter */

			TIM4_CR1 |= TIM_ARPE ;
			TIM4_SR = 0 ;
			//TIM4_CR1 = 1; /* enable TIM4 */
			TIM4_CR1 |= TIM_CEN ;
			// configure TIM2 to wrap around at 10 ms
		    TIM2_CR1 = 0 ;
			TIM2_PSC = 1000 - 1;
			TIM2_ARR = DELAY_10MS-1;
			TIM2_EGR = TIM_UG; /* clear timer counter */
            TIM2_CR1 |= TIM_ARPE ;
		    TIM2_SR = 0 ;
			//TIM4_CR1 = 1; /* enable TIM4 */
			TIM2_CR1 |= TIM_CEN ;

}


void delayMS(){


     switch(cmp){
           /* 1s---> led on 0.5 s and off 0.5s*/
           case 1:
	           TIM2_ARR= 20999 ;
	           while(!(TIM2_SR & TIM_UIF)) {}
	           TIM2_SR =0 ;
	           break;
            /*500 ms--> led on 250ms and off 250ms*/
           case 2 :
	           TIM2_ARR= 10499 ;
	           while(!(TIM2_SR & TIM_UIF)) {}
	           TIM2_SR =0 ;
	           break;
	        /*250 ms--> led on 125 ms and off 125 ms*/
           case 3 :
	           TIM2_ARR= 5250 ;
	           while(!(TIM2_SR & TIM_UIF)) {}
	           TIM2_SR =0 ;
	           break;
            default :
	           cmp=1;
}

}

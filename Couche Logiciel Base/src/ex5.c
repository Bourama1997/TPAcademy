/* Embedded Systems - Exercise 5 */

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

#define  DELAY_50MS  4200
#define  DELAY_10MS  4200
#define WAIT_DELAYS 84000
volatile int b_state_1=0;
volatile int cmp=0;
volatile int event_b1=0;
int main(void)
{



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
		// GPIO RED_LED init
		GPIOD_MODER = SET_BITS(GPIOD_MODER, RED_LED*2 ,2 ,0b01) ;
		GPIOD_OTYPER = GPIOD_OTYPER & ~( 1 << RED_LED ) ;
		GPIOD_PUPDR = SET_BITS (GPIOD_PUPDR , RED_LED*2 , 2 , 0b01 );
		GPIOD_BSRR=(1<<(RED_LED +16));
        //Button

		GPIOA_MODER = SET_BITS (GPIOA_MODER, USER_BUT*2 , 2 , 0b00 ) ;
		GPIOA_OTYPER = GPIOA_OTYPER & ~ ( 1 << USER_BUT ) ;
		GPIOA_PUPDR = SET_BITS(GPIOA_PUPDR, USER_BUT*2 , 2 , 0b10 ) ;

// Initialisation de Timer
		TIM4_5_Init() ;

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
         event_b1=1;
         cmp=10;
         GPIOD_BSRR=(1<<(GREEN_LED+16));

	      }

if(event_b1){
	 if((GPIOD_ODR & (1<<GREEN_LED))==0 ){
		 if(cmp >=10){
		 TIM2_SR=0;
		 delayMSI(3);
	     GPIOD_BSRR=(1<<(GREEN_LED));

		 delayMSI(3);

		 GPIOD_BSRR=(1<<(GREEN_LED+16));
		 cmp=1;
		 }else
			{
		 		  TIM2_SR=0;
		 		  delayMSI(2) ;
		 		  GPIOD_BSRR=(1<<(RED_LED));
		 		  delayMSI(2) ;
		 		  /*switch off led red*/
		 		 GPIOD_BSRR=(1<<(RED_LED+16));

		 		 cmp++;

		 		}

	 }

	}

	}


}

/*iniatialisation de valeur de timer 10 m */

void TIM4_5_Init(){

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
			TIM2_PSC = 3600 - 1;
			TIM2_ARR = DELAY_10MS-1;
			TIM2_EGR = TIM_UG; /* clear timer counter */
            TIM2_CR1 |= TIM_ARPE ;
		    TIM2_SR = 0 ;
			//TIM4_CR1 = 1; /* enable TIM4 */
			TIM2_CR1 |= TIM_CEN ;

}


void delayMSI(int cmp){


     switch(cmp){
           /* 1s*/
           case 1:
	           TIM2_ARR= 209999 ;
	           while(!(TIM2_SR & TIM_UIF)) {}
	           TIM2_SR =0 ;
	           break;
            /*500 ms*/
           case 2 :
	           TIM2_ARR= 2915 ;
	           while(!(TIM2_SR & TIM_UIF)) {}
	           TIM2_SR =0 ;
	           break;
	        /*250 ms*/
           case 3 :
	           TIM2_ARR= 58332 ;
	           while(!(TIM2_SR & TIM_UIF)) {}
	           TIM2_SR =0 ;
	           break;
            default :
	           cmp=1;
}

}

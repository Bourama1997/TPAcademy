/* Embedded Systems - Exercise 2 */

#include <tinyprintf.h>
#include <stm32f4/rcc.h>
#include <stm32f4/gpio.h>


// GPIOD
#define GREEN_LED	12
#define ORANGE_LED	13
#define RED_LED		14
#define BLUE_LED	15

// GPIODA
#define USER_BUT	0

int HALF_PERIOD=200000;
int b_state=0;
int main() {
	// RCC init
      RCC_AHB1ENR |= RCC_GPIOAEN;
      RCC_AHB1ENR |= RCC_GPIODEN;


	// GPIO GREEN_LED init
      GPIOD_MODER = SET_BITS(GPIOD_MODER, GREEN_LED*2 ,2 ,0b01) ;
      GPIOD_OTYPER = GPIOD_OTYPER & ~( 1 << GREEN_LED ) ;
      GPIOD_PUPDR = SET_BITS (GPIOD_PUPDR , GREEN_LED*2 , 2 , 0b01 );
      GPIOD_BSRR=(1<<(GREEN_LED +16));
        //Button

      GPIOA_MODER = SET_BITS (GPIOA_MODER, USER_BUT*2 , 2 , 0b00 ) ;
      GPIOA_OTYPER = GPIOA_OTYPER & ~ ( 1 << USER_BUT ) ;
      GPIOA_PUPDR = SET_BITS(GPIOA_PUPDR, USER_BUT*2 , 2 , 0b10 ) ;



	while(1){

		for(int i=0; i<HALF_PERIOD;i++)
		{
			if(GPIOA_IDR & (1<<USER_BUT) !=0)
				b_state=1 ;
			else if(b_state){
				b_state=0;
				HALF_PERIOD +=200;
			}
		}

		if(b_state)
		    GPIOD_BSRR=(1<<(GREEN_LED));
		else
		    GPIOD_BSRR=(1<<(GREEN_LED +16));
	}

}

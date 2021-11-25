/* Embedded Systems - Exercise 1 */

#include <tinyprintf.h>
#include <stm32f4/rcc.h>
#include <stm32f4/gpio.h>



// GPIOD
#define GREEN_LED	12
#define ORANGE_LED	13
#define RED_LED		14
#define BLUE_LED	15

// GPIOA
#define USER_BUT	0

int main() {
	// RCC init
		RCC_AHB1ENR |= RCC_GPIODEN;

		// GPIO RED_LED init
		GPIOD_MODER = SET_BITS(GPIOD_MODER, RED_LED*2 ,2 ,0b01) ;
		GPIOD_OTYPER = GPIOD_OTYPER & ~( 1 << RED_LED ) ;
		GPIOD_PUPDR = SET_BITS (GPIOD_PUPDR , RED_LED*2 , 2 , 0b01 );
		GPIOD_BSRR=(1<<(RED_LED +16));

		// GPIO GREEN_LED init
	    GPIOD_MODER = SET_BITS(GPIOD_MODER, GREEN_LED*2 ,2 ,0b01) ;
		GPIOD_OTYPER = GPIOD_OTYPER & ~( 1 << GREEN_LED ) ;
		GPIOD_PUPDR = SET_BITS (GPIOD_PUPDR , GREEN_LED*2 , 2 , 0b01 );
		GPIOD_BSRR=(1<<(GREEN_LED +16));

		// GPIO ORANGE_LED init
	    GPIOD_MODER = SET_BITS(GPIOD_MODER, ORANGE_LED*2 ,2 ,0b01) ;
	    GPIOD_OTYPER = GPIOD_OTYPER & ~( 1 << ORANGE_LED ) ;
		GPIOD_PUPDR = SET_BITS (GPIOD_PUPDR , ORANGE_LED*2 , 2 , 0b01 );
		GPIOD_BSRR=(1<<(ORANGE_LED +16));

		// GPIO BLUE_LED init
		GPIOD_MODER = SET_BITS(GPIOD_MODER, BLUE_LED*2 ,2 ,0b01) ;
		GPIOD_OTYPER = GPIOD_OTYPER & ~( 1 << BLUE_LED ) ;
		GPIOD_PUPDR = SET_BITS (GPIOD_PUPDR , BLUE_LED*2 , 2 , 0b01 );
		GPIOD_BSRR=(1<<(BLUE_LED +16));

		printf("Endless loop!\n");

	while(1){


             GPIOD_BSRR=(1<<(ORANGE_LED));
             delayMS(10);//10 ms
             GPIOD_BSRR=(1<<(RED_LED));
             GPIOD_BSRR=(1<<(ORANGE_LED+16));
             delayMS(10);//10 ms
             GPIOD_BSRR=(1<<(BLUE_LED));
             GPIOD_BSRR=(1<<(RED_LED+16));
             delayMS(10);//10 ms
             GPIOD_BSRR=(1<<(BLUE_LED+16));
             GPIOD_BSRR=(1<<(GREEN_LED));
             delayMS(10);//10 ms
             GPIOD_BSRR=(1<<(GREEN_LED+16));




	}

}
void delayMS(int n){
	int i;

	for(;n>0;n--);
	for(i=0; i<30000000/4;i++);
}


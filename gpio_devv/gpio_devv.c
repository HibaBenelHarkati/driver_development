/*
 * gpio_driver.c
 *
 * 
 *      Author: PC
 */
#include <stdint.h>
#include "stm32f103.h"

//#include "stm32f103xb.h"
void activeClock(void){

	RCC_reg->CR|=(1<<0);
	while(!(RCC_reg->CR & (0x1<<1))); //on attend que le clock se stabilise
	RCC_reg->CFGR &=~(0x3 << 0);
	while((RCC_reg->CFGR & (0x3<<2))!=(0x0<<2));			//(0x3<<2)masque pour lire les valeurs des 2 bits SWS

	Flash_reg->ACR = (2<<0);

}

void GPIO_clockControl(volatile GPIO_registers *GPIOx,uint8_t ClockState){	//clock state: enabled or disabled

	if(ClockState==ENABLE){
		if(GPIOx==GPIOA){			//si l adresse de GPIOx== adresse de GPIOA
			gpioA_ClkEn();
		}
		else if(GPIOx==GPIOB){
			gpioB_ClkEn();
		}
		else if(GPIOx==GPIOC){
			gpioC_ClkEn();

		}
		else if(GPIOx==GPIOD){
			gpioD_ClkEn();
		}
		else if(GPIOx==GPIOE){
			gpioE_ClkEn();
		}
	}

	else if(ClockState==DISABLE){
		if(GPIOx==GPIOA){			//si l adresse de GPIOx== adresse de GPIOA
				gpioA_ClkDis();
	    }
		else if(GPIOx==GPIOB){
				gpioB_ClkDis();
		}
		else if(GPIOx==GPIOC){
				gpioC_ClkDis();
		}
		else if(GPIOx==GPIOD){
				gpioD_ClkDis();
		}
		else if(GPIOx==GPIOE){
				gpioE_ClkDis();
		}
	}
}


//I/O definition for a particular pin AND TO CHECK ALL THE GPIOMODE AND GPIOCNF CHEcK THE GPIO_DRIVER.H
void GPIO_initi(volatile GPIO_registers *GPIOx,
		uint8_t gpioPinNumber,
		uint8_t gpioMode,	//reg_CR to define the mode
		uint8_t gpioCnf){


		if(gpioPinNumber<8){												//le cas du low + writing the pinmode in the corresponding register

			GPIOx -> reg_CR[0]&=~(0xF<<(4*gpioPinNumber));		//clear the bits of gpioMode pin
			//ecriture ds les pin MODE
			uint32_t tmp=0;
			tmp = gpioMode|(gpioCnf<<2); 		//cfg les positions initialement [CNF1 CNF0 MODE1 MODE0]
			GPIOx -> reg_CR[0]|=(tmp<<4*gpioPinNumber);						//copy using tmp so that it wont affct the original bits in the clr register


		}


		else{ //CR[1] == CRH

			GPIOx -> reg_CR[1]&=~(0xF<<(4*(gpioPinNumber-8)));

			uint32_t tmp=0;
			tmp |= gpioMode | (gpioCnf<<2);
			GPIOx -> reg_CR[1]|=(tmp<<(4*(gpioPinNumber-8)));

		}
}
void External_hardwareInterrupts(uint8_t GPIOx_pin, 			// GPIOAx_pin
		volatile uint8_t gpioPinNumber,
		uint8_t exti_rising, 				//EXTI_rising
		uint8_t IRQ_Num){

	//activer le clock pour interrupt
	RCC_reg->APB2ENR |=(1<<0);


	//mapping the line of EXTI with the gpios (definition de l interruption avec ses ports and pins)
	uint32_t tmp=0;

	if(0<=gpioPinNumber && gpioPinNumber<=3){
		tmp=AFIO_reg->EXTICR1;
		tmp&=~(0xF<<gpioPinNumber*4);
		tmp|=(GPIOx_pin<<gpioPinNumber*4);
		AFIO_reg->EXTICR1=tmp;
	}
	if(4<=gpioPinNumber && gpioPinNumber<=7){
		uint8_t pos=gpioPinNumber%4;
		tmp=AFIO_reg->EXTICR2;
		tmp&=~(0xF<<pos*4);
		tmp|=(GPIOx_pin<<pos*4);
		AFIO_reg->EXTICR2=tmp;
	}
	if(8<=gpioPinNumber && gpioPinNumber<=11){
		uint8_t pos=gpioPinNumber%4;
		tmp=AFIO_reg->EXTICR3;
		tmp&=~(0xF<<pos*4);
		tmp|=(GPIOx_pin<<pos*4);
		AFIO_reg->EXTICR3=tmp;
	}
	if(12<=gpioPinNumber && gpioPinNumber<=15){
		uint8_t pos=gpioPinNumber%4;
		tmp=AFIO_reg->EXTICR4;
		tmp&=~(0xF<<pos*4);
		tmp|=(GPIOx_pin<<pos*4);
		AFIO_reg->EXTICR4=tmp;

	}

	//enabling the interrupt on pinx corresponding to extix line

	if(gpioPinNumber<=15){
		//enabling the interrupt on pinx corresponding to extix line
		EXTI_reg->IMR|=(1<<gpioPinNumber);	//interr request

		//rising&falling trigger
		if(exti_rising==0){
				EXTI_reg->RTSR &=~(1<<gpioPinNumber);
				EXTI_reg->FTSR |=(1<<gpioPinNumber);
		}
		else{
				EXTI_reg->FTSR &= ~(1<<gpioPinNumber);
				EXTI_reg->RTSR|=(1<<gpioPinNumber);
		}

		//enabling nvic
		//__disable_irq();
		//NVIC_EnableIRQ(IRQ_Num); // Enable the pin0 calling the interrupting function (interrupt thread)
		//_enable_irq();		//activer les interr cote system
		// Activer NVIC
		_disable_irq();
		*NVIC_ISER0 |= (1 << IRQ_Num); // active EXTI0
		_enable_irq();

}}

/*
 * main.c
 *
 *  Created on: Oct 6, 2025
 *      Author: PC
 */
#include <stdint.h>
#include "../gpio_devv/gpio_devv.h"

int main(){
	activeClock();
	GPIO_clockControl(GPIOA,ENABLE);

	//push button
	GPIO_initi(GPIOA, PIN0, GPIO_Mode_Input , GPIO_CNFIn_Pull);	//PIN0 ==Line0 of EXTI0

	//LED
	GPIO_initi(GPIOA, PIN2, GPIO_Mode_OUT_50M , GPIO_CNFOut_GenOD );

	External_hardwareInterrupts(0,0,1, EXTI0_IRQn); //GPIOA, pin0 =>Line 0, rising trigger==1



	for(;;){
		/*GPIOA->reg_ODR&=~(0xFFFF);
		GPIOA->reg_ODR^=(0x1<<0);*/ //ceci pour le test du drvier GPIO=> Blinky
	}

}




//routine interruption
void EXTI0_IRQHandler(){
	if(EXTI_reg->PR&(1<<0)){ //line 0
		GPIOA->reg_ODR|=(1<<2);
		EXTI_reg->PR|=(1 << 0);
	}
}






/*void EXTI1_IRQHandler(){}*/
/*void EXTI2_IRQHandler(){}*/
/*void EXTI3_IRQHandler(){}*/
/*void EXTI4_IRQHandler(){}*/
/*void EXTI9_5_IRQHandler(){}*//* EXTI Line[9:5] interrupts  */

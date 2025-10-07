/*
 * GPIO_driver.h
 *   PROTOTYPES: declaring API
 *
 *  
 *      Author: PC
 */


#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_
#include "gpio_devv.c"




//init gpio///////////////////////////////

//Mode
#define GPIO_Mode_Input 0
#define GPIO_Mode_OUT_10M 1
#define GPIO_Mode_OUT_2M 2
#define GPIO_Mode_OUT_50M 3
			//////CNF///////
//CNF ENTREE
#define GPIO_CNFIn_Analog 0
#define GPIO_CNFIn_FloatingIn 1
#define GPIO_CNFIn_Pull 2
//CNF Sortie
#define GPIO_CNFOut_GenPP 0			//PP: push pull
#define GPIO_CNFOut_GenOD 1			//OD:open drain
#define GPIO_CNFOut_AltPP 2
#define GPIO_CNFOut_AltOD 3


//Pin number
// Définitions des numéros de pin
#define PIN0   0
#define PIN1   1
#define PIN2   2
#define PIN3   3
#define PIN4   4
#define PIN5   5
#define PIN6   6
#define PIN7   7
#define PIN8   8
#define PIN9   9
#define PIN10  10
#define PIN11  11
#define PIN12  12
#define PIN13  13
#define PIN14  14
#define PIN15  15


///////////////////////
//External interrupt configuration register 1 (AFIO_EXTICR1
#define GPIOA_pin 0
#define GPIOB_pin 1
#define GPIOC_pin 2
#define GPIOD_pin 3
#define GPIOE_pin 4
#define GPIOF_pin 5
#define GPIOG_pin 6


/////////////////////////////// this part is from the official stm32 inc repo
#define EXTI0_IRQn    6     /*!< EXTI Line0 Interrupt                                 */
#define EXTI1_IRQn    7    /*!< EXTI Line1 Interrupt                                 */
#define EXTI2_IRQn    8     /*!< EXTI Line2 Interrupt                                 */
#define EXTI3_IRQn    9    /*!< EXTI Line3 Interrupt                                 */
#define EXTI4_IRQn    10     /*!< EXTI Line4 Interrupt */
#define EXTI9_5_IRQn 23     /*!< External Line[9:5] Interrupts                        */










// PROTOTYPES DES FCTS  POU LE GPIO
//////////////////////initialisation
//enabling clock


void activeClock(void);
void GPIO_clockControl(volatile GPIO_registers *GPIOx, uint8_t ClockState);	//clock state: enabled or disabled



void GPIO_initi(volatile GPIO_registers *GPIOx,
		uint8_t gpioPinNumber,
		uint8_t gpioMode,					//definir le mode du gpio
		uint8_t gpioCnf);

void GPIO_Deinit(void);
/////////////////////////////////


//writing and reading from a pin
void GPIO_readPin(void);
void GPIO_writePin(void);

//writing and reading from a port
void GPIO_readPort(void);
void GPIO_writePort(void);

void External_hardwareInterrupts(uint8_t GPIOx_pin, 			// GPIOAx_pin
		volatile uint8_t gpioPinNumber,
		uint8_t exti_rising, 				//EXTI_rising
		uint8_t IRQ_Num);




#endif /* GPIO_DRIVER_H_ */

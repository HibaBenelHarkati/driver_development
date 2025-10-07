#include <stdint.h>



#ifndef STM32F103XXX_H_
#define STM32F103XXX_H_


#define DISABLE 0
#define ENABLE 1


// definir les adresse des bus
#define AHB  0x40018000U
#define APB1 0x40000000U
#define APB2 0x40010000U


// GPIO Base addresses
#define GPIOA_ADDR  (APB2 + (0x0800))
#define GPIOB_ADDR  (APB2 + (0x0C00))
#define GPIOC_ADDR  (APB2 + (0x1000))
#define GPIOD_ADDR  (APB2 + (0x1400))
#define GPIOE_ADDR  (APB2 + (0x1800))
#define GPIOF_ADDR  (APB2 + (0x1C00))
#define GPIOG_ADDR  (APB2 + (0x2000))


// RCC(clock config) address definition
#define RCC_ADDR 0x40021000U

//flash Acr adress
#define FLASH_ACR  0x40022000U

#define EXTI_ADDR 0x4001000U

#define AFI_ADDR 0x40010000U
//each register is 32bits

//GPIO registers
typedef struct {

	uint32_t reg_CR[2];			//register low and high
	uint32_t reg_IDR;			//input data register
	uint32_t reg_ODR;			//out data reg
	uint32_t reg_BSRR;			//bit set/reset reg
	uint32_t reg_BRR;			//bit reste reg
	uint32_t reg_LCKR; 			//lock register

}GPIO_registers;


//RCC registers p156
typedef struct{
	uint32_t CR;
	uint32_t CFGR;
	uint32_t CIR;
	uint32_t APB2RSTR;
	uint32_t APB1RSTR;
	uint32_t AHBENR;
	uint32_t APB2ENR;		//activation du clock pour les gpios
	uint32_t APB1ENR;
	uint32_t BDCR;
	uint32_t CSR;
}RCC_Reg;



typedef struct{
	uint32_t ACR;
}FLASH_reg;



//external interrupt
typedef struct{
	uint32_t IMR; 				//interrupt mask register
	uint32_t EMR;				//event mask reg
	uint32_t RTSR;				//rising trigger reg
	uint32_t FTSR; 				//falling trigger reg
	uint32_t SWIER;				//software interrupt event reg
	uint32_t PR;
}EXTI;



//AFIO pour activer le port pariculier de la ligne of the interrupt (ref manual .interrupts lines)

//!! before writing in these reg the AFIO clock should be enabled
typedef struct{
	uint32_t EVCR;				//for events
	uint32_t MAPR1;				//debbugging
	uint32_t EXTICR1;			//to select the port for EXTIx line from line 0-> 3
	uint32_t EXTICR2;			//from EXTI line 4 to line 7
	uint32_t EXTICR3;			//from 8 to line 11
	uint32_t EXTICR4;
	uint32_t MAPR2;
}AFIO;


#define AFIO_reg ((volatile AFIO*)AFI_ADDR)

#define EXTI_reg ((volatile EXTI*)EXTI_ADDR)

#define Flash_reg ((volatile FLASH_reg*)FLASH_ACR) 					 //RCC_reg est un pointeur qui pointe vers struct at the address RCC_ADDR, !!il fallit mettre les parentheses RCC_reg->APB2ENR|=(1<<2)


//definir un pointeur GPIOX QUI POINTE vers ses les registres
#define GPIOA ((volatile GPIO_registers*)GPIOA_ADDR)
#define GPIOB ((volatile GPIO_registers*)GPIOB_ADDR)
#define GPIOC ((volatile GPIO_registers*)GPIOC_ADDR)
#define GPIOD ((volatile GPIO_registers*)GPIOD_ADDR)
#define GPIOE ((volatile GPIO_registers*)GPIOE_ADDR)
#define GPIOF ((volatile GPIO_registers*)GPIOF_ADDR)
#define GPIOG ((volatile GPIO_registers*)GPIOG_ADDR)


//pointer ayant l adresse de RCC et pointe vers la struct RCC register
#define RCC_reg ((volatile  RCC_Reg*)RCC_ADDR) 					 //RCC_reg est un pointeur qui pointe vers struct at the address RCC_ADDR, !!il fallit mettre les parentheses RCC_reg->APB2ENR|=(1<<2)

//implementer le macro qui set le clock du gpio
#define gpioA_ClkEn()  (RCC_reg->APB2ENR|=(1<<2))
#define gpioB_ClkEn()  (RCC_reg->APB2ENR|=(1<<3))
#define gpioC_ClkEn()  (RCC_reg->APB2ENR|=(1<<4))
#define gpioD_ClkEn()  (RCC_reg->APB2ENR|=(1<<5))
#define gpioE_ClkEn()  (RCC_reg->APB2ENR|=(1<<6))


//implementer le macro pour la desactivatiin des gpio_clocks reset
#define gpioA_ClkDis()  (RCC_reg->APB2ENR &=~(1<<2))
#define gpioB_ClkDis()  (RCC_reg->APB2ENR &=~(1<<3))
#define gpioC_ClkDis()  (RCC_reg->APB2ENR &=~(1<<4))
#define gpioD_ClkDis()  (RCC_reg->APB2ENR &=~(1<<5))
#define gpioE_ClkDis()  (RCC_reg->APB2ENR &=~(1<<6))

#define _enable_irq()  __asm volatile ("cpsie i")
#define _disable_irq() __asm volatile ("cpsid i")

#define NVIC_ISER0 ((volatile uint32_t*)0xE000E100)

#endif /* STM32F103XXX_H_ */


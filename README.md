# driver_development

Writing my own GPIO driver for the STM32F103, from scratch, the setup i made is as follows:

**stm32f103.h** : This is where I defined all the base addresses, register maps, and macros for peripherals (GPIO, RCC, EXTI, AFIO...). Basically, it’s my own version of the MCU header file allowing direct access to registers.

**gpio_devv.c** and **gpio_devv.c**: These files form the core of the GPIO driver, i implemented functions to initialize GPIO clocks (enabling/disabling specific ports) and configured pin modes and CNF (input/output, push-pull...) and setted up external interrupts (EXTI) by linking GPIO pins to interrupt lines and configuring the NVIC

**main.c** : Here I configured: PA0 as an input for the push button and PA2 as an output for the LED, then I used EXTI0 (external interrupt line 0) so that when I press the button, the interrupt triggers and turns ON the LED 

/*
 * stm32f407xx.h
 *
 *  Created on: Jun 3, 2024
 *      Author: Yusuf
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>

#define __IO volatile
/*
 *  Memory Base Addresses
 */

#define FLASH_BASE_ADDR				(0x08000000UL) 	/* Flash base address (1 MB)	*/
#define SRAM1_BASE_ADDR				(0x20000000UL) 	/* SRAM1 base address (112 KB)	*/
#define SRAM2_BASE_ADDR				(0x2001C000UL) 	/* SRAM2 base address (16 KB) 	*/


/*
 *  Peripheral's Base Addresses
 */

#define PERIPH_BASE_ADDR			(0x40000000UL)						/* Base address for all peripherals	*/

#define APB1_BASE_ADDR				PERIPH_BASE_ADDR					/* APB1 Bus Domain base address		*/
#define APB2_BASE_ADDR				(PERIPH_BASE_ADDR + 0x00010000UL)	/* APB2 Bus Domain base address		*/
#define AHB1_BASE_ADDR				(PERIPH_BASE_ADDR + 0x00020000UL)	/* AHB1 Bus Domain base address		*/
#define AHB2_BASE_ADDR				(PERIPH_BASE_ADDR + 0x10000000UL)	/* AHB2 Bus Domain base address		*/


/*
 *  APB1 Peripherals' Base Addresses
 */

#define TIM2_BASE_ADDR				(APB1_BASE_ADDR + 0x00000000UL)		/* Timer 2 Base Address */
#define TIM3_BASE_ADDR				(APB1_BASE_ADDR + 0x00000400UL)		/* Timer 3 Base Address */
#define TIM4_BASE_ADDR				(APB1_BASE_ADDR + 0x00000800UL)		/* Timer 4 Base Address */
#define TIM5_BASE_ADDR				(APB1_BASE_ADDR + 0x00000C00UL)		/* Timer 5 Base Address */
#define TIM6_BASE_ADDR				(APB1_BASE_ADDR + 0x00001000UL)		/* Timer 6 Base Address */
#define TIM7_BASE_ADDR				(APB1_BASE_ADDR + 0x00001400UL)		/* Timer 7 Base Address */

#define SPI2_BASE_ADDR				(APB1_BASE_ADDR + 0x00003800UL)		/* SPI 2 Base Address 	*/
#define SPI3_BASE_ADDR				(APB1_BASE_ADDR + 0x00003C00UL)		/* SPI 3 Base Address 	*/

#define USART2_BASE_ADDR			(APB1_BASE_ADDR + 0x00004400UL)		/* USART 2 Base Address */
#define USART3_BASE_ADDR			(APB1_BASE_ADDR + 0x00004800UL)		/* USART 3 Base Address */
#define UART4_BASE_ADDR				(APB1_BASE_ADDR + 0x00004C00UL)		/* UART 4 Base Address 	*/
#define UART5_BASE_ADDR				(APB1_BASE_ADDR + 0x00005000UL)		/* UART 5 Base Address 	*/

#define I2C1_BASE_ADDR				(APB1_BASE_ADDR + 0x00005400UL)		/* I2C 1 Base Address 	*/
#define I2C2_BASE_ADDR				(APB1_BASE_ADDR + 0x00005800UL)		/* I2C 2 Base Address 	*/
#define I2C3_BASE_ADDR				(APB1_BASE_ADDR + 0x00005C00UL)		/* I2C 3 Base Address 	*/


/*
 *  APB2 Peripherals' Base Addresses
 */

#define TIM1_BASE_ADDR				(APB2_BASE_ADDR + 0x00000000UL)		/* Timer 1 Base Address */
#define TIM8_BASE_ADDR				(APB2_BASE_ADDR + 0x00000400UL)		/* Timer 8 Base Address */

#define USART1_BASE_ADDR			(APB2_BASE_ADDR + 0x00001000UL)		/* USART 1 Base Address */
#define USART6_BASE_ADDR			(APB2_BASE_ADDR + 0x00001400UL)		/* USART 6 Base Address */

#define SPI1_BASE_ADDR				(APB2_BASE_ADDR + 0x00003000UL)		/* SPI 1 Base Address 	*/
#define SPI4_BASE_ADDR				(APB2_BASE_ADDR + 0x00003400UL)		/* SPI 4 Base Address 	*/
#define SPI5_BASE_ADDR				(APB2_BASE_ADDR + 0x00005000UL)		/* SPI 5 Base Address 	*/
#define SPI6_BASE_ADDR				(APB2_BASE_ADDR + 0x00005400UL)		/* SPI 6 Base Address 	*/

#define SYSCFG_BASE_ADDR			(APB2_BASE_ADDR + 0x00003800UL)		/* SYSCFG Base Address 	*/

#define EXTI_BASE_ADDR				(APB2_BASE_ADDR + 0x00003C00UL)		/* EXTI Base Address 	*/



/*
 *  AHB1 Peripherals' Base Addresses
 */

#define GPIOA_BASE_ADDR				(AHB1_BASE_ADDR + 0x00000000UL)		/* GPRIOA Base Address	*/
#define GPIOB_BASE_ADDR				(AHB1_BASE_ADDR + 0x00000400UL)		/* GPRIOB Base Address	*/
#define GPIOC_BASE_ADDR				(AHB1_BASE_ADDR + 0x00000800UL)		/* GPRIOC Base Address	*/
#define GPIOD_BASE_ADDR				(AHB1_BASE_ADDR + 0x00000C00UL)		/* GPRIOD Base Address	*/
#define GPIOE_BASE_ADDR				(AHB1_BASE_ADDR + 0x00001000UL)		/* GPRIOE Base Address	*/
#define GPIOF_BASE_ADDR				(AHB1_BASE_ADDR + 0x00001400UL)		/* GPRIOF Base Address	*/
#define GPIOG_BASE_ADDR				(AHB1_BASE_ADDR + 0x00001800UL)		/* GPRIOG Base Address	*/
#define GPIOH_BASE_ADDR				(AHB1_BASE_ADDR + 0x00001C00UL)		/* GPRIOH Base Address	*/
#define GPIOI_BASE_ADDR				(AHB1_BASE_ADDR + 0x00002000UL)		/* GPRIOI Base Address	*/
#define GPIOJ_BASE_ADDR				(AHB1_BASE_ADDR + 0x00002400UL)		/* GPRIOJ Base Address	*/
#define GPIOK_BASE_ADDR				(AHB1_BASE_ADDR + 0x00002800UL)		/* GPRIOK Base Address	*/

#define RCC_BASE_ADDR				(AHB1_BASE_ADDR + 0x00003800UL)		/* RCCBase Address		*/



/*
 *  Peripheral Structure Definitions
 */


typedef struct{
	__IO uint32_t MODER;			/*!< GPIO port mode register					address offset = 0x0000 */
	__IO uint32_t OTYPER;			/*!< GPIO port output type register 			address offset = 0x0004 */
	__IO uint32_t OSPEEDR;			/*!< GPIO port output speed register			address offset = 0x0008 */
	__IO uint32_t PUPDR;			/*!< GPIO port pull-up/pull-down register		address offset = 0x000C */
	__IO uint32_t IDR;				/*!< GPIO port input data register				address offset = 0x0010 */
	__IO uint32_t ODR;				/*!< GPIO port output data register				address offset = 0x0014 */
	__IO uint32_t BSRR;				/*!< GPIO port bit set/reset register			address offset = 0x0018 */
	__IO uint32_t LCKR;				/*!< GPIO port configuration lock register		address offset = 0x001C */
	__IO uint32_t AFR[2];			/*!< GPIO port alternate function register		address offset = 0x0020 */
}GPIO_Typedef_t;


#define GPIOA				( (GPIO_Typedef_t *)(GPIOA_BASE_ADDR) )
#define GPIOB				( (GPIO_Typedef_t *)(GPIOB_BASE_ADDR) )
#define GPIOC				( (GPIO_Typedef_t *)(GPIOC_BASE_ADDR) )
#define GPIOD				( (GPIO_Typedef_t *)(GPIOD_BASE_ADDR) )
#define GPIOE				( (GPIO_Typedef_t *)(GPIOE_BASE_ADDR) )
#define GPIOF				( (GPIO_Typedef_t *)(GPIOF_BASE_ADDR) )
#define GPIOG				( (GPIO_Typedef_t *)(GPIOG_BASE_ADDR) )
#define GPIOH				( (GPIO_Typedef_t *)(GPIOH_BASE_ADDR) )
#define GPIOI				( (GPIO_Typedef_t *)(GPIOI_BASE_ADDR) )
#define GPIOJ				( (GPIO_Typedef_t *)(GPIOJ_BASE_ADDR) )
#define GPIOK				( (GPIO_Typedef_t *)(GPIOK_BASE_ADDR) )






















#endif /* INC_STM32F407XX_H_ */

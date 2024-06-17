/*
 * stm32f407xx.h
 *
 *  Created on: Jun 3, 2024
 *      Author: Yusuf
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>
#include <string.h>
#include <stddef.h>

/*
 * Microprocessor Defines
 */

#define NVIC_ISER0			 ( (uint32_t *)(0xE000E100) )



#define __IO volatile

#define SET_BIT(REG, BIT)		((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)		((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)		((REG) & (BIT))
#define TOGGLE_BIT(REG, BIT)	((REG) ^= (BIT))
#define UNUSED(x)				(void)x

typedef enum{
	DISABLE	= 0x0U,
	ENABLE = !DISABLE
}FUNCTIONALState_t;

/*
 * IRQ Numbers of MCU == Vector Table
 */
typedef enum{
	 EXTI0_IRQNumber = 6,
	 EXTI1_IRQNumber,
	 EXTI2_IRQNumber,
	 EXTI3_IRQNumber,
	 EXTI4_IRQNumber,
	 SPI1_IRQNumber = 35
}IRQNumber_Typedef_t;

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
	__IO uint32_t MODER;			/*!< GPIO port mode register									address offset = 0x0000 */
	__IO uint32_t OTYPER;			/*!< GPIO port output type register 							address offset = 0x0004 */
	__IO uint32_t OSPEEDR;			/*!< GPIO port output speed register							address offset = 0x0008 */
	__IO uint32_t PUPDR;			/*!< GPIO port pull-up/pull-down register						address offset = 0x000C */
	__IO uint32_t IDR;				/*!< GPIO port input data register								address offset = 0x0010 */
	__IO uint32_t ODR;				/*!< GPIO port output data register								address offset = 0x0014 */
	__IO uint32_t BSRR;				/*!< GPIO port bit set/reset register							address offset = 0x0018 */
	__IO uint32_t LCKR;				/*!< GPIO port configuration lock register						address offset = 0x001C */
	__IO uint32_t AFR[2];			/*!< GPIO port alternate function register						address offset = 0x0020 */
}GPIO_Typedef_t;



typedef struct {
	__IO uint32_t CR;				/*!< clock control register										address offset = 0x0000 */
	__IO uint32_t PLLCFRG;			/*!< PLL configuration register									address offset = 0x0004 */
	__IO uint32_t CFRG;				/*!< clock configuration register								address offset = 0x0008 */
	__IO uint32_t CIR;				/*!< clock interrupt register									address offset = 0x000C */
	__IO uint32_t AHB1RSTR;			/*!< AHB1 peripheral reset register								address offset = 0x0010 */
	__IO uint32_t AHB2RSTR;			/*!< AHB2 peripheral reset register								address offset = 0x0014 */
	__IO uint32_t AHB3RSTR;			/*!< AHB3 peripheral reset register								address offset = 0x0018 */
	__IO uint32_t RESERVED0;		/*!< RESERVED BLCOK												address offset = 0x001C */
	__IO uint32_t APB1RSTR;			/*!< APB1 peripheral reset register								address offset = 0x0020 */
	__IO uint32_t APB2RSTR;			/*!< APB2 peripheral reset register								address offset = 0x0024 */
	__IO uint32_t RESERVED1[2];		/*!< RESERVED BLCOK												address offset = 0x0028 */
	__IO uint32_t AHB1ENR;			/*!< AHB1 peripheral clock enable register						address offset = 0x0030 */
	__IO uint32_t AHB2ENR;			/*!< AHB2 peripheral clock enable register						address offset = 0x0034 */
	__IO uint32_t AHB3ENR;			/*!< AHB3 peripheral clock enable register						address offset = 0x0038 */
	__IO uint32_t RESERVED2;		/*!< RESERVED BLCOK												address offset = 0x003C */
	__IO uint32_t APB1ENR;			/*!< APB1 peripheral clock enable register						address offset = 0x0040 */
	__IO uint32_t APB2ENR;			/*!< APB2 peripheral clock enable register						address offset = 0x0044 */
	__IO uint32_t RESERVED3[2];		/*!< RESERVED BLCOK												address offset = 0x0048 */
	__IO uint32_t AHB1LPENR;		/*!< AHB1 peripheral clock enable in low power mode register	address offset = 0x0050 */
	__IO uint32_t AHB2LPENR;		/*!< AHB2 peripheral clock enable in low power mode register	address offset = 0x0054 */
	__IO uint32_t AHB3LPENR;		/*!< AHB3 peripheral clock enable in low power mode register	address offset = 0x0058 */
	__IO uint32_t RESERVED4;		/*!< RESERVED BLCOK												address offset = 0x005C */
	__IO uint32_t APB1LPENR;		/*!< APB1 peripheral clock enable in low power mode register	address offset = 0x0060 */
	__IO uint32_t APB2LPENR;		/*!< APB2 peripheral clock enable in low power mode register	address offset = 0x0064 */
	__IO uint32_t RESERVED5[2];		/*!< RESERVED BLCOK												address offset = 0x0068 */
	__IO uint32_t BDCR;				/*!< Backup domain control register								address offset = 0x0070 */
	__IO uint32_t CSR;				/*!< Clock control & status register							address offset = 0x0074 */
	__IO uint32_t RESERVED6[2];		/*!< RESERVED BLCOK												address offset = 0x0078 */
	__IO uint32_t SSCGR;			/*!< Spread spectrum clock generation register					address offset = 0x0080 */
	__IO uint32_t PLLI2SCFGR;		/*!< PLI2S configuration register								address offset = 0x0084 */
} RCC_Typedef_t;


typedef struct {
	__IO uint32_t MEMRMP;			/*!< SYSCFG Memory Remap Register								address offset = 0x0000 */
	__IO uint32_t PMC;				/*!< SYSCFG Peripheral Mode Configuration Register				address offset = 0x0004 */
	__IO uint32_t EXTI_CR[4];		/*!< SYSCFG External Interrupt Configuration Registers			address offset = 0x0008 */
	__IO uint32_t RESERVED[2];		/*!< SYSCFG RESERVED AREA 										address offset = 0x0018 */
	__IO uint32_t CMPCR;			/*!< SYSCFG Compensation Cell Control Register					address offset = 0x0020 */
}SYSCFG_Typedef_t;

typedef struct {
	__IO uint32_t IMR;				/*!< EXTI Interrupt mask register								address offset = 0x0000 */
	__IO uint32_t EMR;				/*!< EXTI Event mask register									address offset = 0x0004 */
	__IO uint32_t RTSR;				/*!< EXTI Rising trigger selection register						address offset = 0x0008 */
	__IO uint32_t FTSR;				/*!< EXTI Falling trigger selection register					address offset = 0x000C */
	__IO uint32_t SWIER;			/*!< EXTI Software interrupt event register						address offset = 0x0010 */
	__IO uint32_t PR;				/*!< EXTI Pending Register										address offset = 0x0014 */
}EXTI_Typedef_t;

typedef struct{
	__IO uint32_t CR1;				/*!< SPI Control Register 1										address offset = 0x0000 */
	__IO uint32_t CR2;				/*!< SPI Control Register 2										address offset = 0x0004 */
	__IO uint32_t SR;				/*!< SPI Status Register										address offset = 0x0008 */
	__IO uint32_t DR;				/*!< SPI Data Register											address offset = 0x000C */
	__IO uint32_t CRCPR;			/*!< SPI CRC Polynomial Register								address offset = 0x0010 */
	__IO uint32_t RXCRCR;			/*!< SPI RX CRC Polynomial Register								address offset = 0x0014 */
	__IO uint32_t TXCRCR;			/*!< SPI TX CRC Register										address offset = 0x0018 */
	__IO uint32_t I2SCFGR;			/*!< SPI I2S Configuration Register								address offset = 0x001C */
	__IO uint32_t I2SPR;			/*!< SPI I2S Prescaler Register									address offset = 0x0020 */
}SPI_Typedef_t;


#define GPIOA						( (GPIO_Typedef_t *)(GPIOA_BASE_ADDR)	)
#define GPIOB						( (GPIO_Typedef_t *)(GPIOB_BASE_ADDR)	)
#define GPIOC						( (GPIO_Typedef_t *)(GPIOC_BASE_ADDR)	)
#define GPIOD						( (GPIO_Typedef_t *)(GPIOD_BASE_ADDR)	)
#define GPIOE						( (GPIO_Typedef_t *)(GPIOE_BASE_ADDR)	)
#define GPIOF						( (GPIO_Typedef_t *)(GPIOF_BASE_ADDR)	)
#define GPIOG						( (GPIO_Typedef_t *)(GPIOG_BASE_ADDR) 	)
#define GPIOH						( (GPIO_Typedef_t *)(GPIOH_BASE_ADDR) 	)
#define GPIOI						( (GPIO_Typedef_t *)(GPIOI_BASE_ADDR) 	)

#define RCC							( (RCC_Typedef_t *)(RCC_BASE_ADDR) 		)

#define SYSCFG						( (SYSCFG_Typedef_t *)(SYSCFG_BASE_ADDR))

#define EXTI						( (EXTI_Typedef_t *)(EXTI_BASE_ADDR) 	)

#define SPI1						( (SPI_Typedef_t *)(SPI1_BASE_ADDR) 	)
#define SPI2						( (SPI_Typedef_t *)(SPI2_BASE_ADDR)	 	)
#define SPI3						( (SPI_Typedef_t *)(SPI3_BASE_ADDR) 	)
#define SPI4						( (SPI_Typedef_t *)(SPI4_BASE_ADDR) 	)
#define SPI5						( (SPI_Typedef_t *)(SPI5_BASE_ADDR) 	)
#define SPI6						( (SPI_Typedef_t *)(SPI6_BASE_ADDR) 	)


/*
 * Bit Definitions
 */

#define RCC_AHB1ENR_GPIOAEN_Pos		(0U)								/*!< RCC AH1BENR GPIOA Clock Enable Bit Position */
#define RCC_AHB1ENR_GPIOAEN_Msk		(0x1 << RCC_AHB1ENR_GPIOAEN_Pos )		/*!< RCC AH1BENR GPIOA Clock Enable Bit Mask */
#define RCC_AHB1ENR_GPIOAEN			RCC_AHB1ENR_GPIOAEN_Msk				/*!< RCC AH1BENR GPIOA Clock Enable Macro */

#define RCC_AHB1ENR_GPIOBEN_Pos		(1U)								/*!< RCC AH1BENR GPIOB Clock Enable Bit Position */
#define RCC_AHB1ENR_GPIOBEN_Msk		(0x1 << RCC_AHB1ENR_GPIOBEN_Pos )		/*!< RCC AH1BENR GPIOB Clock Enable Bit Mask */
#define RCC_AHB1ENR_GPIOBEN			RCC_AHB1ENR_GPIOBEN_Msk				/*!< RCC AH1BENR GPIOB Clock Enable Macro */

#define RCC_AHB1ENR_GPIOCEN_Pos		(2U)								/*!< RCC AH1BENR GPIOC Clock Enable Bit Position */
#define RCC_AHB1ENR_GPIOCEN_Msk		(0x1 << RCC_AHB1ENR_GPIOCEN_Pos )		/*!< RCC AH1BENR GPIOC Clock Enable Bit Mask */
#define RCC_AHB1ENR_GPIOCEN			RCC_AHB1ENR_GPIOCEN_Msk				/*!< RCC AH1BENR GPIOC Clock Enable Macro */

#define RCC_AHB1ENR_GPIODEN_Pos		(3U)								/*!< RCC AH1BENR GPIOD Clock Enable Bit Position */
#define RCC_AHB1ENR_GPIODEN_Msk		(0x1 << RCC_AHB1ENR_GPIODEN_Pos )		/*!< RCC AH1BENR GPIOD Clock Enable Bit Mask */
#define RCC_AHB1ENR_GPIODEN			RCC_AHB1ENR_GPIODEN_Msk				/*!< RCC AH1BENR GPIOD Clock Enable Macro */

#define RCC_AHB1ENR_GPIOEEN_Pos		(4U)								/*!< RCC AH1BENR GPIOE Clock Enable Bit Position */
#define RCC_AHB1ENR_GPIOEEN_Msk		(0x1 << RCC_AHB1ENR_GPIOE_Pos )		/*!< RCC AH1BENR GPIOE Clock Enable Bit Mask */
#define RCC_AHB1ENR_GPIOEEN			RCC_AHB1ENR_GPIOEEN_Msk				/*!< RCC AH1BENR GPIOE Clock Enable Macro */

#define RCC_AHB1ENR_GPIOFEN_Pos		(5U)								/*!< RCC AH1BENR GPIOF Clock Enable Bit Position */
#define RCC_AHB1ENR_GPIOFEN_Msk		(0x1 << RCC_AHB1ENR_GPIOF_Pos )		/*!< RCC AH1BENR GPIOF Clock Enable Bit Mask */
#define RCC_AHB1ENR_GPIOFEN			RCC_AHB1ENR_GPIOFEN_Msk				/*!< RCC AH1BENR GPIOF Clock Enable Macro */

#define RCC_AHB1ENR_GPIOGEN_Pos		(6U)								/*!< RCC AH1BENR GPIOG Clock Enable Bit Position */
#define RCC_AHB1ENR_GPIOGEN_Msk		(0x1 << RCC_AHB1ENR_GPIOGEN_Pos )		/*!< RCC AH1BENR GPIOG Clock Enable Bit Mask */
#define RCC_AHB1ENR_GPIOGEN			RCC_AHB1ENR_GPIOGEN_Msk				/*!< RCC AH1BENR GPIOG Clock Enable Macro */

#define RCC_AHB1ENR_GPIOHEN_Pos		(7U)								/*!< RCC AH1BENR GPIOH Clock Enable Bit Position */
#define RCC_AHB1ENR_GPIOHEN_Msk		(0x1 << RCC_AHB1ENR_GPIOHEN_Pos )		/*!< RCC AH1BENR GPIOH Clock Enable Bit Mask */
#define RCC_AHB1ENR_GPIOHEN			RCC_AHB1ENR_GPIOHEN_Msk				/*!< RCC AH1BENR GPIOH Clock Enable Macro */

#define RCC_AHB1ENR_GPIOIEN_Pos		(8U)								/*!< RCC AH1BENR GPIOI Clock Enable Bit Position */
#define RCC_AHB1ENR_GPIOIEN_Msk		(0x1 << RCC_AHB1ENR_GPIOIEN_Pos )		/*!< RCC AH1BENR GPIOI Clock Enable Bit Mask */
#define RCC_AHB1ENR_GPIOIEN			RCC_AHB1ENR_GPIOIEN_Msk				/*!< RCC AH1BENR GPIOI Clock Enable Macro */

#define RCC_APB2ENR_SYSCFGEN_Pos		(14U)								/*!< RCC APB2ENR SYSCFG Clock Enable Bit Position */
#define RCC_APB2ENR_SYSCFGEN_Msk		(0x1 << RCC_APB2ENR_SYSCFGEN_Pos)		/*!< RCC APB2ENR SYSCFG Clock Enable Bit Mask */
#define RCC_APB2ENR_SYSCFGEN			RCC_APB2ENR_SYSCFGEN_Msk				/*!< RCC APB2ENR SYSCFG Clock Enable Macro */

#define RCC_APB2ENR_SPI1EN_Pos		(12U)								/*!< RCC APB2ENR SPI1	Clock Enable Bit Position */
#define RCC_APB2ENR_SPI1EN_Msk		(0x1 << RCC_APB2ENR_SPI1EN_Pos)		/*!< RCC APB2ENR SPI1	Clock Enable Bit Mask */
#define RCC_APB2ENR_SPI1EN			RCC_APB2ENR_SPI1EN_Msk				/*!< RCC APB2ENR SPI1	Clock Enable Macro */

#define RCC_APB1ENR_SPI2EN_Pos		(14U)								/*!< RCC APB1ENR SPI2	Clock Enable Bit Position */
#define RCC_APB1ENR_SPI2EN_Msk		(0x1 << RCC_APB1ENR_SPI2EN_Pos)		/*!< RCC APB1ENR SPI2	Clock Enable Bit Mask */
#define RCC_APB1ENR_SPI2EN			RCC_APB1ENR_SPI2EN_Msk				/*!< RCC APB1ENR SPI2	Clock Enable Macro */

#define RCC_APB1ENR_SPI3EN_Pos		(15U)								/*!< RCC APB1ENR SPI3	Clock Enable Bit Position */
#define RCC_APB1ENR_SPI3EN_Msk		(0x1 << RCC_APB1ENR_SPI3EN_Pos)		/*!< RCC APB1ENR SPI3	Clock Enable Bit Mask */
#define RCC_APB1ENR_SPI3EN			RCC_APB1ENR_SPI3EN_Msk				/*!< RCC APB1ENR SPI3	Clock Enable Macro */


#define SPI_SR_RXNE					(0U)								/*!< SPI Status Register Receive Buffer Not Empty Flag */
#define SPI_SR_TXE						(1U)								/*!< SPI Status Register Transmit Buffer Empty Flag */
#define SPI_SR_BSY						(7U)								/*!< SPI Status Register Busy Flag */

#define SPI_CR1_SPE					(6U)								/*!< SPI CR1 Peripheral Enable Bit Position */
#define SPI_CR1_DFF					(11U)								/*!< SPI CR1 Data Frame Format Bit Position */

#define SPI_CR2_TXEIE					(7U)								/*!< SPI CR2 Transmit Buffer Empty Interrupt Enable Bit Position*/
#define SPI_CR2_RXNEIE				(6U)								/*!< SPI CR2 Receive Buffer Not Empty Interrupt Enable Bit Position*/



#include "RCC.h"
#include "GPIO.h"
#include "EXTI.h"
#include "SPI.h"

#endif /* INC_STM32F407XX_H_ */

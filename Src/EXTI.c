/*
 * EXTI.c
 *
 *  Created on: Jun 12, 2024
 *      Author: Yusuf
 */

#include "EXTI.h"


/*
 * @brief Initializes the EXTI port
 * @param EXTI_InitStruct = struct that contains information about EXTI to be initialized.
 * @retval none
 *
 */
void EXTI_Init(EXTI_InitTypedef_t *EXTI_InitStruct){
	uint32_t tempValue =0;
	tempValue = (uint32_t)EXTI_BASE_ADDR;
	tempValue += EXTI_InitStruct->EXTI_Mode;		// Figure out if its event mode or interrupt mode


	if (EXTI_InitStruct->EXTI_LineCmd == DISABLE){
		*((__IO uint32_t*)tempValue) = ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);
	}else{
		EXTI->IMR &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);	// Clear the bits before writing
		EXTI->EMR &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);
		*((__IO uint32_t*)tempValue) = (0x1U << EXTI_InitStruct->EXTI_LineNumber);

		tempValue = (uint32_t)EXTI_BASE_ADDR;

		EXTI->RTSR &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);
		EXTI->FTSR &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);
		if (EXTI_InitStruct->TriggerSelection == EXTI_TRIGGER_RF){
			// configure for both rising and falling
			EXTI->RTSR |= (0x1U << EXTI_InitStruct->EXTI_LineNumber);
			EXTI->FTSR |= (0x1U << EXTI_InitStruct->EXTI_LineNumber);
		}else{
			// otherwise...
			tempValue += EXTI_InitStruct->TriggerSelection;
			*(( __IO uint32_t*)tempValue) = (0x1U << EXTI_InitStruct->EXTI_LineNumber);

		}
	}
}


/*
 * @brief Configures the SYSCFG  port and pin for listening the interrupt from.
 * @param EXTI_PortSource = EXTI_PORTSOURCE_GPIO[A-K] 	@def_group Port_Values
 * @param EXTI_LineSource = EXTI_LineSource_[0-F]		@def_group EXTI_Line_Values
 * @retval none
 *
 */
void EXTI_LineConfig(uint8_t EXTI_PortSource,uint8_t EXTI_LineSource ){

	uint32_t tempValue;
	uint8_t pin = (EXTI_LineSource & 0x3U) << 2U; 				// (EXTI_LineSource % 4 ) * 4

    tempValue = SYSCFG->EXTI_CR[EXTI_LineSource >> 2U];
	tempValue &= ~(0xFU << pin);
	tempValue = (EXTI_PortSource << pin);

	SYSCFG->EXTI_CR[EXTI_LineSource >> 2U] = tempValue;
}

/*
 * @brief Configures the NVIC to enable interrupt for specified IRQ.
 * @param IRQNumber = IRQ number of line
 * @retval none
 *
 */
void NVIC_EnableInterrupt(uint8_t IRQNumber){
	uint32_t tempValue =0 ;

	tempValue  = *((IRQNumber >> 5U) + NVIC_ISER0); // Find address of corresponding register for IRQ Number and de-ref it.
	tempValue &= ~(0x1U << (IRQNumber & 0x1FU ));	// Clear the corresponding bit (modulus).
	tempValue |= (0x1U <<(IRQNumber & 0x1FU ) );

	*((IRQNumber >> 5U) + NVIC_ISER0) = tempValue;
}

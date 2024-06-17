/*
 * GPIO.c
 *
 *  Created on: Jun 5, 2024
 *      Author: Yusuf
 */

#include "GPIO.h"

/*
 * @brief Initializes the GPIO port.
 * @param GPIOx = GPIO(A - I)
 * @param GPIO_Config = configuration to apply to  the GPIOx
 * @retval none
 *
 */
void GPIO_Init(GPIO_Typedef_t *GPIOx, GPIO_InitTypedef_t *GPIO_Config){
	uint32_t position;
	uint32_t fakePosition = 0;
	uint32_t lastPosition = 0;
	uint32_t tempValue = 0;
	for (position = 0 ; position < 16 ; position++){

		fakePosition = (0x1 << position);
		lastPosition = (uint32_t)(GPIO_Config->pinNumber) & fakePosition;

		if (fakePosition == lastPosition){

			// MODE CONFIG
		    tempValue = GPIOx->MODER;
			tempValue &= ~(0x3U << (position*2));
			tempValue |= (GPIO_Config->Mode << (position*2));
			GPIOx->MODER = tempValue;


			// It only makes sense to configure OTYPER and OSPEEDR registers if the Mode is either output of alternating function.
			// Otherwise these are ignored anyways.
			if (GPIO_Config->Mode == GPIO_MODE_OUTPUT || GPIO_Config->Mode == GPIO_MODE_AF){
				// OTYPE & OSPEED CONFIG
				tempValue = GPIOx->OTYPER;
				tempValue &= ~(0x1U << position);
				tempValue |= (GPIO_Config->Otype << position);
				GPIOx->OTYPER = tempValue;

				tempValue = GPIOx->OSPEEDR;
				tempValue &= ~(0x3U << (position * 2));
				tempValue |= (GPIO_Config->Speed << (position * 2));
				GPIOx->OSPEEDR = tempValue;
			}

			// PUPDR CONFIG
			tempValue = GPIOx->PUPDR;
			tempValue &= ~(0x3U << (position * 2));
			tempValue |= (GPIO_Config->PuPd << (position * 2));
			GPIOx->PUPDR = tempValue;
		}

		if (GPIO_Config->Mode == GPIO_MODE_AF){
			tempValue = GPIOx->AFR[position >> 3U];				// find correct register
			tempValue &= ~(0xFU << ((position & 0x7U ) >> 2)); 	// find correct pin
			tempValue |= (GPIO_Config->Alternate << ((position & 0x7U) >> 2));
			GPIOx->AFR[position >> 3U] |= tempValue;
		}
	}
}




/*
 * @brief Makes given pin on pinNumber for GPIOX high or low depending on the state parameter.
 * @param GPIOx = GPIO(A - I)
 * @param pinNumber = GPIO pin numbers 0 - 15
 * @param state = state of the pin, enabled (high) or disabled (low)
 * @retval none
 *
 */

void GPIO_WritePin(GPIO_Typedef_t *GPIOx, uint16_t pinNumber, GPIO_PinState_t state ){
	if (state == GPIO_Pin_Set){
		GPIOx->BSRR = pinNumber;
	}else{
		GPIOx->BSRR = (pinNumber << 16U);
	}
}

/*
 * @brief Returns the state of the requested pin.
 * @param GPIOx = GPIO(A - I)
 * @param pinNumber = GPIO pin numbers 0 - 15
 * @retval the state of the requested pin (GPIO_PinState_t)
 *
 */
GPIO_PinState_t GPIO_ReadPin(GPIO_Typedef_t *GPIOx, uint16_t pinNumber){
	if (GPIOx->IDR &  pinNumber){
		return GPIO_Pin_Set;
	}

	return GPIO_Pin_Reset;
}

/*
 * @brief Locks the specified pin(s) for modification on GPIOx.
 * 			lock sequence is described in the reference manual.
 * @param GPIOx = GPIO(A - I)
 * @param pinNumber = GPIO pin numbers 0 - 15
 * @retval none
 *
 */
void GPIO_LockPin(GPIO_Typedef_t *GPIOx,  uint16_t pinNumber){
	uint32_t tempVal = (0x1U << 16U) | pinNumber;

	// lock sequence defined in reference manual.
	GPIOx->LCKR = tempVal;
	GPIOx->LCKR = pinNumber;
	GPIOx->LCKR = tempVal;

	tempVal = GPIOx->LCKR;
}

/*
 * @brief Toggles the specified pin(s) on GPIOx.
 * @param GPIOx = GPIO(A - I)
 * @param pinNumber = GPIO pin numbers 0 - 15
 * @retval none
 *
 */
void GPIO_TogglePin(GPIO_Typedef_t *GPIOx,  uint16_t pinNumber){
	uint32_t  tempODR = GPIOx->ODR;
	GPIOx->BSRR = ((tempODR & pinNumber) << 16U) | (~tempODR & pinNumber);
}

/*
 * RCC.c
 *
 *  Created on: Jun 5, 2024
 *      Author: Yusuf
 */

#include "RCC.h"

const uint8_t AHB_Prescalers[] = {0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
const uint8_t APB_Prescalers[] = {0, 0, 0, 0, 1, 2, 3, 4};

/*
 * @brief Returns the value of System Clock
 *
 * @retval none
 */
uint32_t RCC_GetSystemCLK(void){
	uint32_t sysCoreClk = 0;
	uint8_t clkSource = 0;

	clkSource = ((RCC->CFRG >> 2U) & 0x3U);		// Get System Clock Switch Status

	switch (clkSource) {
		case 0:	sysCoreClk =	16000000;	break;	// HSI
		case 1:	sysCoreClk =	8000000;	break;	// HSE
		default: sysCoreClk =	16000000;	break;	// HSI
	}

	return sysCoreClk;
}

/*
 * @brief Returns the value of AHB System Clock
 *
 * @retval none
 */
uint32_t RCC_GetHClk(void){
	uint32_t AHB_PeriphClk =0;
	uint32_t sysCoreClk =0;
	uint8_t HPRE_Value = 0;

	sysCoreClk = RCC_GetSystemCLK();

	HPRE_Value = ((RCC->CFRG >> 4) & 0xFU );
	AHB_PeriphClk = sysCoreClk >> AHB_Prescalers[HPRE_Value];

	return AHB_PeriphClk;
}

/*
 * @brief Returns the value of APB1 System Clock
 *
 * @retval none
 */
uint32_t RCC_GetPClk1(void){
	uint32_t APB1_PeriphClk = 0;
	uint32_t hClk = 0;
	uint8_t PPRE_Value= 0;

	hClk = RCC_GetHClk();

	PPRE_Value = ((RCC->CFRG >> 10) & 0x7U);

	APB1_PeriphClk = hClk >> APB_Prescalers[PPRE_Value];

	return APB1_PeriphClk;
}

/*
 * @brief Returns the value of APB2 System Clock
 *
 * @retval none
 */
uint32_t RCC_GetPClk2(void){
	uint32_t APB2_PeriphClk = 0;
	uint32_t hClk = 0;
	uint8_t PPRE_Value= 0;

	hClk = RCC_GetHClk();

	PPRE_Value = ((RCC->CFRG >> 13) & 0x7U);

	APB2_PeriphClk = hClk >> APB_Prescalers[PPRE_Value];

	return APB2_PeriphClk;
}


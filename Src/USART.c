/*
 * USART.c
 *
 *  Created on: Jun 17, 2024
 *      Author: Yusuf
 */

#include "USART.h"

static void USART_CloseISR_RX(USART_HandleTypedef_t *USART_Handle){
	USART_Handle->rxBufferSize = 0;
	USART_Handle->pRxBuffer= NULL;
	USART_Handle->rxStatus = USART_BUS_FREE;
	USART_Handle->Instance->CR1 &= ~(0x1U << USART_CR1_RXNEIE);

}

static void USART_CloseISR_TX(USART_HandleTypedef_t *USART_Handle){
	USART_Handle->txBufferSize = 0;
	USART_Handle->pTxBuffer= NULL;
	USART_Handle->txStatus = USART_BUS_FREE;
	USART_Handle->Instance->CR1 &= ~(0x1U << USART_CR1_TXEIE);

}

static void USART_SendWith_INT(USART_HandleTypedef_t *USART_Handle){
	if ((USART_Handle->Init.WordLength == USART_WORDLENGTH_9BITS) && (USART_Handle->Init.Parity == USART_PARITY_NONE)){
		uint16_t *p16BitsData =(uint16_t *)USART_Handle->pTxBuffer;
		USART_Handle->Instance->DR = (uint16_t)(*p16BitsData & (uint16_t)0x01FFU);
		USART_Handle->pTxBuffer+= sizeof(uint16_t);
		USART_Handle->txBufferSize-=2;
	}else{
		USART_Handle->Instance->DR = (uint8_t)(*(USART_Handle->pTxBuffer) & (uint8_t)0x00FF);
		USART_Handle->pTxBuffer++;
		USART_Handle->txBufferSize--;
	}

	if (USART_Handle->txBufferSize ==0){
		USART_CloseISR_TX(USART_Handle);
	}
}

static void USART_ReceiveWith_INT(USART_HandleTypedef_t *USART_Handle){
	uint16_t *p16BitsBuffer = NULL;
	uint8_t *p8BitsBuffer = NULL;

	if ((USART_Handle->Init.WordLength == USART_WORDLENGTH_9BITS) &&  (USART_Handle->Init.Parity == USART_PARITY_NONE)){
		p16BitsBuffer = (uint16_t *)(USART_Handle->pRxBuffer);
	}else{
		p8BitsBuffer = (uint8_t *)(USART_Handle->pRxBuffer);
	}

	if (p8BitsBuffer == NULL){
		*p16BitsBuffer = (uint16_t)(USART_Handle->Instance->DR  & 0x01FFU);
		USART_Handle->pRxBuffer+=sizeof(uint16_t);
		USART_Handle->rxBufferSize-=2;
	}else{

		if((USART_Handle->Init.WordLength == USART_WORDLENGTH_9BITS) &&  (USART_Handle->Init.Parity != USART_PARITY_NONE)){
			// 9 Bit data, with parity
			*p8BitsBuffer = (uint8_t)((USART_Handle->Instance->DR) & 0x00FFU);
		}else if ((USART_Handle->Init.WordLength == USART_WORDLENGTH_8BITS) &&  (USART_Handle->Init.Parity == USART_PARITY_NONE)){
			// 8 Bit data, no parity
			*p8BitsBuffer = (uint8_t)((USART_Handle->Instance->DR) & 0x00FFU);
		}else{
			// 8 Bit data, with parity
			*p8BitsBuffer = (uint8_t)((USART_Handle->Instance->DR) & 0x007FU);
		}

		USART_Handle->pRxBuffer+=sizeof(uint8_t);
		USART_Handle->rxBufferSize--;
	}

	if (USART_Handle->rxBufferSize ==0){
		USART_CloseISR_RX(USART_Handle);
	}
}

/*
 * @brief Initializes the U(S)ART port
 * @param USART_Handle = struct that contains information about U(S)ART to be initialized.
 * @retval none
 *
 */
void USART_Init(USART_HandleTypedef_t *USART_Handle){
	uint32_t tempValue = 0;
	uint32_t periphClk = 0;
	uint32_t mantissa = 0;
	uint32_t fraction =0 ;
	uint32_t USARTDivValue = 0;

	// CR1 Configuration
	tempValue = USART_Handle->Instance->CR1;
	tempValue |= (USART_Handle->Init.OverSampling) | (USART_Handle->Init.WordLength) |
		 (USART_Handle->Init.Mode) | (USART_Handle->Init.Parity);

	USART_Handle->Instance->CR1 = tempValue;

	// CR2 Configuration
	tempValue = USART_Handle->Instance->CR2;
	tempValue &= ~(0x3U << USART_CR2_STOP);
	tempValue |= (USART_Handle->Init.StopBits) ;

	USART_Handle->Instance->CR2 = tempValue;

	// CR3 Configuration

	tempValue = USART_Handle->Instance->CR3;
	tempValue |= (USART_Handle->Init.HardWareFlowControl);

	USART_Handle->Instance->CR3 = tempValue;

	// BaudRate Configuration

	if ((USART_Handle->Instance == USART1) || (USART_Handle->Instance== USART6)){
		// APB2 CLK
		periphClk = RCC_GetPClk2();
	}else{
		// APB1 CLK
		periphClk = RCC_GetPClk1();
	}

	if (USART_Handle->Init.OverSampling == USART_OVERSAMPLING_8BITS){
		// 8 bits sampling
		USARTDivValue = __USART_DIV_VALUE_8(periphClk, USART_Handle->Init.BaudRate);
		mantissa = (USARTDivValue / 100U);
		fraction = (USARTDivValue) - (mantissa *100U);
		fraction = (((fraction * 8U) + 50U)/ 100U) & 0x7U	;
	}else{
		// 16 bits sampling
		USARTDivValue = __USART_DIV_VALUE_16(periphClk, USART_Handle->Init.BaudRate);
		mantissa = (USARTDivValue / 100U);
		fraction = (USARTDivValue) - (mantissa *100U);
		fraction = (((fraction * 16U) + 50U)/ 100U)  & 0xFU;
	}


	tempValue |= (mantissa << 4U);
	tempValue |= (fraction);

	USART_Handle->Instance->BRR = tempValue;
}

/*
 * @brief Transmits the data over the U(S)ART port.
 *
 * @param USART_Handle = Struct that contains the address
 *  of the configured U(S)ART instance.
 *
 * @param *pData = Pointer to the data to be transmitted.
 *
 * @param sizeOfData = Size of the data in bytes.
 *
 * @retval none
 */
void USART_TransmitData(USART_HandleTypedef_t *USART_Handle, uint8_t *pData, uint16_t sizeOfData){
	uint16_t *data16Bits;				// In case of 9 bits with no parity

	if((USART_Handle->Init.WordLength == USART_WORDLENGTH_9BITS) && (USART_Handle->Init.Parity == USART_PARITY_NONE)){
		// 9 bit data no parity
		data16Bits = (uint16_t*)pData;
	}else{
		data16Bits = NULL;
	}

	while(sizeOfData > 0){
		while(!(USART_GetFlagStatus(USART_Handle, USART_FLAG_TXE)));		// Check TxE flag if its one than buffer empty if not then block

		if (data16Bits == NULL){
			USART_Handle->Instance->DR = *pData;
			pData++;
			sizeOfData--;
		}else{
			USART_Handle->Instance->DR = (uint16_t)(*data16Bits * (0x01FFU));			// write the 9 bit LSB to the DR
			data16Bits++;
			sizeOfData-=2;
		}
	}

	// Wait untill Transmission Complete flag is set
	while(!(USART_GetFlagStatus(USART_Handle, USART_FLAG_TC )));


}

/*
 * @brief Receives the data over the U(S)ART port.
 *
 * @param USART_Handle = Struct that contains the address
 *  of the configured U(S)ART instance.
 *
 * @param *pBuffer = Pointer to the data to be stored.
 *
 * @param sizeOfBuffer = Size of the buffer in bytes.
 *
 * @retval none
 */
void USART_ReceiveData(USART_HandleTypedef_t *USART_Handle, uint8_t *pBuffer, uint16_t sizeOfBuffer){
	uint16_t *p16BitsBuffer = NULL;
	uint8_t *p8BitsBuffer = NULL;

	if ((USART_Handle->Init.WordLength == USART_WORDLENGTH_9BITS) &&  (USART_Handle->Init.Parity == USART_PARITY_NONE)){
		p16BitsBuffer = (uint16_t *)pBuffer;
	}else{
		p8BitsBuffer = (uint8_t *)pBuffer;
	}

	while(sizeOfBuffer > 0){
		while(!(USART_GetFlagStatus(USART_Handle, USART_FLAG_RXNE)));

		if (p8BitsBuffer == NULL){
			// 9 Bit data, no parity
			*p16BitsBuffer = (uint16_t)(USART_Handle->Instance->DR & 0x01FFU);
			p16BitsBuffer++;
			sizeOfBuffer-=2;
		}else{

			if((USART_Handle->Init.WordLength == USART_WORDLENGTH_9BITS) &&  (USART_Handle->Init.Parity != USART_PARITY_NONE)){
				// 9 Bit data, with parity
				*p8BitsBuffer = (uint8_t)((USART_Handle->Instance->DR) & 0x00FFU);

			}else if ((USART_Handle->Init.WordLength == USART_WORDLENGTH_8BITS) &&  (USART_Handle->Init.Parity == USART_PARITY_NONE)){
				// 8 Bit data, no parity
				*p8BitsBuffer = (uint8_t)((USART_Handle->Instance->DR) & 0x00FFU);
			}else{
				// 8 Bit data, with parity
				*p8BitsBuffer = (uint8_t)((USART_Handle->Instance->DR) & 0x007FU);
			}

			p8BitsBuffer++;
			sizeOfBuffer--;
		}

	}
}




void USART_TransmitDataINT(USART_HandleTypedef_t *USART_Handle, uint8_t *pData, uint16_t sizeOfData){
	USART_BusState_t usartBusState = USART_Handle->txStatus;

	if(usartBusState != USART_BUS_Tx){
		USART_Handle->txStatus = USART_BUS_Tx;
		USART_Handle->pTxBuffer = pData;
		USART_Handle->txBufferSize = sizeOfData;
		USART_Handle->TxISRFunction = USART_SendWith_INT;


		USART_Handle->Instance->CR1 |= (0x1U << USART_CR1_TXEIE);
	}
}

void USART_ReceiveDataINT(USART_HandleTypedef_t *USART_Handle, uint8_t *pBuffer, uint16_t sizeOfBuffer){
	USART_BusState_t usartBusState = USART_Handle->rxStatus;

		if(usartBusState != USART_BUS_Rx){
			USART_Handle->rxStatus = USART_BUS_Rx;
			USART_Handle->pRxBuffer = pBuffer;
			USART_Handle->rxBufferSize = sizeOfBuffer;
			USART_Handle->RxISRFunction = USART_ReceiveWith_INT;


			USART_Handle->Instance->CR1 |= (0x1U << USART_CR1_RXNEIE);
		}
}



/*
 * @brief Returns the status of given flag on U(S)ART.
 *
 * @param USART_Handle = Struct that contains the address
 *  of the configured U(S)ART instance.
 *
 * @param USART_Flag = Flag value on SR @def_group USART_SR_FlagValues.
 *
 * @retval Status of the flag.
 */
USART_FlagStatus_t USART_GetFlagStatus(USART_HandleTypedef_t *USART_Handle, uint16_t USART_Flag){
	return (USART_FlagStatus_t)(USART_Handle->Instance->SR & USART_Flag);
}




/*
 * @brief Changes the state of the U(S)ART.
 *
 * @param USART_Handle = struct that contains the address
 *  of the SPI instance.
 *
 * @param Cmd = State to apply to the U(S)ART (enable | disable).
 *
 * @retval none
 */
void USART_Peripheral_Cmd(USART_HandleTypedef_t *USART_Handle, FunctionalState_t Cmd){
	if (Cmd == ENABLE){
		USART_Handle->Instance->CR1 |= (0x1U << USART_CR1_UE);
	}else{
		USART_Handle->Instance->CR1 &= ~(0x1U << USART_CR1_UE);

	}
}

/*
 * @brief Handles the interrupt for U(S)ART port.
 *
 * @param USART_Handle = Struct that contains the address
 *  of the configured U(S)ART instance.
 *
 * @retval none
 */
void USART_InterruptHandler(USART_HandleTypedef_t *USART_Handle){
	uint8_t flagValue = 0;
	uint8_t interruptValue = 0;

	// TXI
	flagValue = (uint8_t)((USART_Handle->Instance->SR >> 7U) & 0x1U);			// Get TxE
	interruptValue = (uint8_t)((USART_Handle->Instance->CR1 >> 7U) & 0x1U);		// Get TxEIE

	if (flagValue && interruptValue){
		USART_Handle->TxISRFunction(USART_Handle);
	}

	// RXI
	flagValue = (uint8_t)((USART_Handle->Instance->SR >> 5U) & 0x1U);			// Get RxE
	interruptValue = (uint8_t)((USART_Handle->Instance->CR1 >> 5U) & 0x1U);		// Get RxNEIE

	if (flagValue && interruptValue){
		USART_Handle->RxISRFunction(USART_Handle);
	}

}










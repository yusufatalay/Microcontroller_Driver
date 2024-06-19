/*
 * USART.h
 *
 *  Created on: Jun 17, 2024
 *      Author: Yusuf
 */

#ifndef INC_USART_H_
#define INC_USART_H_
#include "stm32f407xx.h"

/*
 * @def_group MODE_Types
 */
#define USART_MODE_Rx						((uint32_t)(0x00000004))
#define USART_MODE_Tx						((uint32_t)(0x00000008))
#define USART_MODE_TxRx					((uint32_t)(0x0000000C))

/*
 * @def_group WL_Values
 */
#define USART_WORDLENGTH_8BITS			((uint32_t)(0x00000000))
#define USART_WORDLENGTH_9BITS			((uint32_t)(0x00001000))

/*
 * @def_group PARITY_Modes
 */
#define USART_PARITY_NONE					((uint32_t)(0x00000000))
#define USART_PARITY_EVEN					((uint32_t)(0x00000400))
#define USART_PARITY_ODD					((uint32_t)(0x00000600))

/*
 * @def_group STOPBITS_Values
 */
#define USART_STOPBITS_1					((uint32_t)(0x00000000))
#define USART_STOPBITS_0_5				((uint32_t)(0x00001000))
#define USART_STOPBITS_2					((uint32_t)(0x00002000))
#define USART_STOPBITS_1_5				((uint32_t)(0x00003000))

/*
 * @def_group OVERSAMPLING_Values
 */
#define USART_OVERSAMPLING_16BITS		((uint32_t)(0x00000000))
#define USART_OVERSAMPLING_8BITS			((uint32_t)(0x00008000))

/*
 * @def_group HWFLOWCONTROL_Modes
 */
#define USART_HWFLOWCTRL_NONE				((uint32_t)(0x00000000))
#define USART_HWFLOWCTRL_RTS				((uint32_t)(0x00000100))
#define USART_HWFLOWCTRL_CTS				((uint32_t)(0x00000200))
#define USART_HWFLOWCTRL_RTS_CTS			((uint32_t)(0x00000300))

/*
 * @def_group USART_SR_FlagValues
 */
#define USART_FLAG_TXE					( 0x1U << USART_SR_TXE )
#define USART_FLAG_TC						( 0x1U << USART_SR_TC  )
#define USART_FLAG_RXNE					( 0x1U << USART_SR_RXNE)

typedef enum{
	USART_FLAG_RESET = 0x0U,
	USART_FLAG_SET = !USART_FLAG_RESET
}USART_FlagStatus_t;


typedef struct{
	uint32_t Mode;							/*!< Transmission and Receiving Modes @def_group MODE_Types */
	uint32_t BaudRate;						/*!< User value for U(S)ART Baud Rate */
	uint32_t OverSampling;					/*!< Oversampling by 8 or 16 Bits @def_group OVERSAMPLING_Values */
	uint32_t WordLength;					/*!< 8 Bits and 9 Bits @def_group WL_Values */
	uint32_t Parity;						/*!< Even | Odd Parity Modes @def_group PARITY_Modes */
	uint32_t StopBits;						/*!< 1, 0.5, 2, 1.5 Stop Bits (0.5 and 1.5 are not available for UART ports) @def_group STOPBITS_Values */
	uint32_t HardWareFlowControl;			/*!< CTSE and RTSE Configuration @def_group HWFLOWCONTROL_Modes */
}USART_InitTypedef_t;

typedef struct USART_HandleTypedef_t{
	USART_Typedef_t *Instance;
	USART_InitTypedef_t Init;
	uint8_t *pTxBuffer;
	uint8_t *pRxBuffer;
	uint16_t txBufferSize;
	uint16_t rxBufferSize;
	uint8_t  txStatus;
	uint8_t  rxStatus;
	void (*TxISRFunction)(struct USART_HandleTypedef_t *USART_Handle);
	void (*RxISRFunction)(struct USART_HandleTypedef_t *USART_Handle);
}USART_HandleTypedef_t;




#define __USART_DIV_VALUE_8(__PCLOCK__, __BAUDRATE__)						((25U * (uint32_t)(__PCLOCK__) ) / (2U * (uint32_t)(__BAUDRATE__)))
#define __USART_DIV_VALUE_16(__PCLOCK__, __BAUDRATE__)					((25U * (uint32_t)(__PCLOCK__) ) / (4U * (uint32_t)(__BAUDRATE__)))

typedef enum{
	USART_BUS_FREE = 0x0U,
	USART_BUS_Tx   =  0x1U,
	USART_BUS_Rx   = 0x2U
}USART_BusState_t;


void USART_Init(USART_HandleTypedef_t *USART_Handle);
void USART_TransmitData(USART_HandleTypedef_t *USART_Handle, uint8_t *pData, uint16_t sizeOfData);
void USART_ReceiveData(USART_HandleTypedef_t *USART_Handle, uint8_t *pBuffer, uint16_t sizeOfBuffer);
void USART_TransmitDataINT(USART_HandleTypedef_t *USART_Handle, uint8_t *pData, uint16_t sizeOfData);
void USART_ReceiveDataINT(USART_HandleTypedef_t *USART_Handle, uint8_t *pBuffer, uint16_t sizeOfBuffer);
void USART_Peripheral_Cmd(USART_HandleTypedef_t *USART_Handle, FunctionalState_t Cmd);
void USART_InterruptHandler(USART_HandleTypedef_t *USART_Handle);
USART_FlagStatus_t USART_GetFlagStatus(USART_HandleTypedef_t *USART_Handle, uint16_t USART_Flag);
#endif /* INC_USART_H_ */

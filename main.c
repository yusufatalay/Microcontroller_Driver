#include "stm32f407xx.h"


static void GPIO_LEDConfig();
static void GPIO_PButtonConfig();
static void LockTest();
static void GPIO_BUTTON_POLLING_CONFIG();
static void GPIO_BUTTON_INTERRUPT_CONFIG();

void EXTI0_IRQHandler(){
	if (EXTI->PR & 0x1){
		// interrupt arrived
		EXTI->PR |= (0x1U << 0U);	// This register is cleared by writing 1 to it
		GPIO_TogglePin(GPIOD, GPIO_PIN_ALL);
	}
}

int main(void)
{
	// GPIO_BUTTON_POLLING_CONFIG();


	//GPIO_BUTTON_INTERRUPT_CONFIG();


	for(;;);
}

static void GPIO_BUTTON_INTERRUPT_CONFIG(){\
	GPIO_LEDConfig();
	GPIO_PButtonConfig();

	EXTI_InitTypedef_t EXTI_Struct = {0};

	RCC_SYSCFG_CLK_ENABLE();

	EXTI_LineConfig(EXTI_PORTSOURCE_GPIOA, EXTI_LineSource_0);

	EXTI_Struct.EXTI_LineCmd = ENABLE;
	EXTI_Struct.EXTI_LineNumber = EXTI_LineSource_0;
	EXTI_Struct.EXTI_Mode = EXTI_MODE_Interrupt;
	EXTI_Struct.TriggerSelection = EXTI_TRIGGER_Rising;

	EXTI_Init(&EXTI_Struct);

	NVIC_EnableInterrupt(EXTI0_IRQNumber);

}

static void GPIO_BUTTON_POLLING_CONFIG(){
	GPIO_LEDConfig();

	GPIO_PButtonConfig();

	for(;;){
		if (GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_Pin_Set){
			GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15 , GPIO_Pin_Set);
		}else{
			GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15 , GPIO_Pin_Reset);
		}
	}
}

static void GPIO_LEDConfig(){
	GPIO_InitTypedef_t GPIO_InitStruct = {0};

	RCC_GPIOD_CLK_ENABLE();

	GPIO_InitStruct.pinNumber = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = GPIO_OSPEED_LOW;
	GPIO_InitStruct.Otype = GPIO_OTYPE_PP;
	GPIO_InitStruct.PuPd = GPIO_PUPD_NOPULL;

	GPIO_Init(GPIOD, &GPIO_InitStruct);
}

static void GPIO_PButtonConfig(){
	GPIO_InitTypedef_t GPIO_InitStruct = {0};

	RCC_GPIOA_CLK_ENABLE();

	GPIO_InitStruct.pinNumber = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.PuPd = GPIO_PUPD_PULLDOWN;

	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

static void LockTest(){
	GPIO_InitTypedef_t GPIO_InitStruct = {0};

		RCC_GPIOA_CLK_ENABLE();

		GPIO_InitStruct.pinNumber = GPIO_PIN_0;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT;
		GPIO_InitStruct.PuPd = GPIO_PUPD_NOPULL;

		GPIO_Init(GPIOA, &GPIO_InitStruct);
}

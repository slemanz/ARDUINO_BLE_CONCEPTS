#include <string.h>

#include "driver_gpio.h"
#include "driver_uart.h"
#include "driver_systick.h"

#define LED_PORT		GPIOC
#define LED_PIN			GPIO_PIN_NO_13

#define BLINK_PERIOD_MS	500U

/*
 * PC13 -> onboard led 
 * PA2  -> UART2 TX
 * PA3  -> UART2 RX
 */
static const GPIO_PinConfig_t pins[] =
{
	{
		.pGPIOx					= LED_PORT,
		.GPIO_PinNumber			= LED_PIN,
		.GPIO_PinMode			= GPIO_MODE_OUT,
		.GPIO_PinSpeed			= GPIO_SPEED_LOW,
		.GPIO_PinOPType			= GPIO_OP_TYPE_PP,
		.GPIO_PinPuPdControl	= GPIO_NO_PUPD,
		.GPIO_PinAltFunMode		= GPIO_PIN_NO_ALTFN,
	},
	{
		.pGPIOx					= GPIOA,
		.GPIO_PinNumber			= GPIO_PIN_NO_2,
		.GPIO_PinMode			= GPIO_MODE_ALTFN,
		.GPIO_PinSpeed			= GPIO_SPEED_FAST,
		.GPIO_PinOPType			= GPIO_OP_TYPE_PP,
		.GPIO_PinPuPdControl	= GPIO_PIN_PU,
		.GPIO_PinAltFunMode		= PA2_ALTFN_UART2_TX,
	},
	{
		.pGPIOx					= GPIOA,
		.GPIO_PinNumber			= GPIO_PIN_NO_3,
		.GPIO_PinMode			= GPIO_MODE_ALTFN,
		.GPIO_PinSpeed			= GPIO_SPEED_FAST,
		.GPIO_PinOPType			= GPIO_OP_TYPE_PP,
		.GPIO_PinPuPdControl	= GPIO_PIN_PU,
		.GPIO_PinAltFunMode		= PA3_ALTFN_UART2_RX,
	},
};

static void serial_init(void)
{
	UART_Config_t uart =
	{
		.pUARTx				= UART2,
		.UART_Mode			= UART_MODE_TXRX,
		.UART_Baud			= UART_STD_BAUD_115200,
		.UART_NoOfStopBits	= UART_STOPBITS_1,
		.UART_WordLength	= UART_WORDLEN_8BITS,
		.UART_ParityControl	= UART_PARITY_DISABLE,
		.UART_HWFlowControl	= UART_HW_FLOW_CTRL_NONE,
	};

	UART_Init(&uart);
	UART_PeripheralControl(UART2, ENABLE);
}

static void serial_print(const char *msg)
{
	UART_Write(UART2, (const uint8_t *)msg, strlen(msg));
}

int main(void)
{
	systick_init(TICK_HZ);

	GPIO_Init_table(pins, sizeof(pins)/sizeof(pins[0]));

	serial_init();
	
	serial_print("Hello World\r\n");

	while(1)
	{
		GPIO_ToggleOutputPin(LED_PORT, LED_PIN);

		ticks_delay(BLINK_PERIOD_MS);
	}
}

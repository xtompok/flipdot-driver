#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

#include "hardware.h"


static void clock_setup(void){
	rcc_clock_setup_in_hse_8mhz_out_24mhz();

	/* Enable clocks for GPIO port A (for GPIO_USART1_TX) and USART1. */
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);


	rcc_periph_clock_enable(RCC_USART1);

}

static void usart_setup(void){
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ,
		      GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART1_TX);
	
	gpio_set_mode(GPIOA, GPIO_MODE_INPUT,
		      GPIO_CNF_INPUT_FLOAT, GPIO_USART1_RX);

	/* Setup UART parameters. */
	usart_set_baudrate(USART1, 115200);
	usart_set_databits(USART1, 8);
	usart_set_stopbits(USART1, USART_STOPBITS_1);
	usart_set_mode(USART1, USART_MODE_TX_RX);
	usart_set_parity(USART1, USART_PARITY_NONE);
	usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);

	/* Finally enable the USART. */
	usart_enable(USART1);
}

static void gpio_setup(void){

	gpio_set_mode(LEDS_PORT, GPIO_MODE_OUTPUT_2_MHZ,
		      GPIO_CNF_OUTPUT_PUSHPULL, LED1_PIN);
	gpio_set_mode(LEDS_PORT, GPIO_MODE_OUTPUT_2_MHZ,
		      GPIO_CNF_OUTPUT_PUSHPULL, LED2_PIN);
}

void led1_toggle(void){
	gpio_toggle(LEDS_PORT,LED1_PIN);	
}
void led2_toggle(void){
	gpio_toggle(LEDS_PORT,LED2_PIN);
}


int main(void){
	int i;

	clock_setup();
	usart_setup();
	gpio_setup();
	led1_toggle();

	usart_send_blocking(USART1,'t');
	usart_send_blocking(USART1,'\r');
	usart_send_blocking(USART1,'\n');
	/* Blink the LED (PC12) on the board. */
	while (1) {
		led1_toggle();
		led2_toggle();
		for (i = 0; i < 800000; i++)	/* Wait a bit. */
			__asm__("nop");
	}

	return 0;
}

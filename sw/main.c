#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/spi.h>

#include "hardware.h"
#include "delay.h"
#include "font.h"
#include "display_ll.h"


static void clock_setup(void){
	rcc_clock_setup_in_hse_8mhz_out_24mhz();

	rcc_periph_clock_enable(RCC_AFIO);

	AFIO_MAPR |= AFIO_MAPR_SWJ_CFG_JTAG_OFF_SW_ON;
	AFIO_MAPR |= AFIO_MAPR_SPI1_REMAP;

	/* Enable clocks for GPIO port A (for GPIO_USART1_TX) and USART1. */
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);


	rcc_periph_clock_enable(RCC_USART1);
	// SPI for rows shift registers
	rcc_periph_clock_enable(RCC_SPI1);

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


static void print_char(unsigned char ch, uint16_t pos){
	uint16_t col;
	col = pos*5;
	rows_off();
	column_start();
	for (int i=0; i< col; i++){
		column_shift();
	}
	uint16_t idx;
	idx=ch-32; // First 32 chars are not printable, thus not in font array
	idx*=5;  // Font is one-dimensional, display has 5 columns per character
	for (int i=0; i<5; i++){
		rows_set((Font5x7[idx+i]));
		delay_ms(70);
		rows_off();
		delay_ms(20);
		column_shift();	
		delay_ms(1);
	}
		
}

static void fill(uint8_t pattern){
		column_start();
	for (int j=0;j<25;j++){
		/*for (int i=0;i<j-1;i++){
		}*/
		rows_set(pattern);
		delay_ms(70);
		rows_off();
		delay_ms(20);
		column_shift();
		pattern=0xFF^pattern;
//		delay_ms(500);
	}

}

static void gpio_setup(void){

	gpio_set_mode(LEDS_PORT, GPIO_MODE_OUTPUT_2_MHZ,
		      GPIO_CNF_OUTPUT_PUSHPULL, LED1_PIN);
	gpio_set_mode(LEDS_PORT, GPIO_MODE_OUTPUT_2_MHZ,
		      GPIO_CNF_OUTPUT_PUSHPULL, LED2_PIN);
	gpio_set_mode(STEPUP_PORT, GPIO_MODE_OUTPUT_2_MHZ,
		      GPIO_CNF_OUTPUT_PUSHPULL, STEPUP_PIN);
}

void led1_toggle(void){
	gpio_toggle(LEDS_PORT,LED1_PIN);	
}
void led2_toggle(void){
	gpio_toggle(LEDS_PORT,LED2_PIN);
}


int main(void){

	clock_setup();
	usart_setup();
	gpio_setup();
	rows_spi_setup();
	led1_toggle();
	column_setup();

	usart_send_blocking(USART1,'t');
	usart_send_blocking(USART1,'\r');
	usart_send_blocking(USART1,'\n');

	gpio_clear(ROW_OE_PORT,ROW_OE_PIN);
	gpio_set(STEPUP_PORT,STEPUP_PIN);
	
	//column_start();
	uint8_t iteration;
	iteration=0;

	uint16_t ncols;
	ncols = count_columns();

	while (1) {
		fill(0xFF^0x00);
		fill(0x00);
//		continue;
/*		column_start();
		for (int i=0;i<25;i++){
			delay_ms(100);
			column_shift();
		}
		led1_toggle();
		continue;
*/
		print_char('A',iteration%5);
//		delay_ms(1000);
//		print_char('!',iteration%5);
//		delay_ms(1000);
		print_char('h',(iteration+1)%5);
//		delay_ms(1000);
		print_char('j',(iteration+3)%5);
//		delay_ms(1000);
		print_char('o',(iteration+2)%5);
//		delay_ms(1000);
		print_char('!',(iteration+4)%5);
		delay_ms(1000);
		led1_toggle();
		iteration++;
	}

	return 0;
}

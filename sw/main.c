#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/spi.h>

#include "hardware.h"
#include "delay.h"


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

static void rows_spi_setup(void){
	gpio_set_mode(ROWS_PORT, GPIO_MODE_OUTPUT_50_MHZ,
		      GPIO_CNF_OUTPUT_PUSHPULL, ROW_STROBE_PIN);
	gpio_set_mode(ROWS_PORT, GPIO_MODE_OUTPUT_50_MHZ,
		      GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, ROW_CLK_PIN);
	gpio_set_mode(ROWS_PORT, GPIO_MODE_OUTPUT_50_MHZ,
		      GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, ROW_DATA_PIN);
	// ! OE is on other port than other pins!
	gpio_set_mode(ROW_OE_PORT, GPIO_MODE_OUTPUT_50_MHZ,
		      GPIO_CNF_OUTPUT_PUSHPULL, ROW_OE_PIN);

	spi_set_unidirectional_mode(ROWS_SPI);
	spi_disable_crc(ROWS_SPI);
	spi_set_full_duplex_mode(ROWS_SPI);
	spi_set_baudrate_prescaler(ROWS_SPI,SPI_CR1_BR_FPCLK_DIV_256);
	spi_set_clock_phase_1(ROWS_SPI);
	spi_set_clock_polarity_0(ROWS_SPI);
	spi_set_dff_8bit(ROWS_SPI);
	spi_send_lsb_first(ROWS_SPI);
	spi_enable_software_slave_management(ROWS_SPI);
	spi_set_nss_high(ROWS_SPI);
	spi_set_master_mode(ROWS_SPI);
	spi_enable(ROWS_SPI);

}
static volatile void column_shift(void){
	delay_ms(COL_DELAY_US);
	gpio_set(COLS_PORT, COL_CLK_PIN);
	delay_ms(COL_DELAY_US);
	gpio_clear(COLS_PORT, COL_CLK_PIN);
	led2_toggle();
}

static void column_setup(void){
	gpio_set_mode(COLS_PORT, GPIO_MODE_OUTPUT_2_MHZ,
		      GPIO_CNF_OUTPUT_PUSHPULL, COL_RST_PIN);
	gpio_set_mode(COLS_PORT, GPIO_MODE_OUTPUT_2_MHZ,
		      GPIO_CNF_OUTPUT_PUSHPULL, COL_CLK_PIN);
	gpio_set_mode(COLS_PORT, GPIO_MODE_OUTPUT_2_MHZ,
		      GPIO_CNF_OUTPUT_PUSHPULL, COL_DATA_PIN);
	gpio_set_mode(COLS_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, COL_RET_PIN);
	


}

static void column_start(void){
	// Reset registers
	gpio_set(COLS_PORT, COL_RST_PIN);
	delay_us(COL_DELAY_US);
	gpio_clear(COLS_PORT, COL_RST_PIN);

	//Send one "1"
	gpio_set(COLS_PORT, COL_DATA_PIN);
	delay_us(COL_DELAY_US);
	gpio_set(COLS_PORT, COL_CLK_PIN);
	delay_us(COL_DELAY_US);
	gpio_clear(COLS_PORT, COL_DATA_PIN);
	gpio_clear(COLS_PORT, COL_CLK_PIN);
}

static volatile uint16_t count_columns(void){
	uint16_t count;
	count = 1;

	column_start();
	while (gpio_get(COLS_PORT,COL_RET_PIN) == 0){
//	while (count<50){
		column_shift();
		count += 1;
		if (count > 1000){
			return 0xFFFF;
		}
	}
	return count;
	
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
	int i;

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
	//gpio_set(STEPUP_PORT,STEPUP_PIN);
	
	//column_start();

	while (1) {
		led1_toggle();
		spi_send(ROWS_SPI,0x55);
		spi_send(ROWS_SPI,~0x55);
		gpio_set(ROWS_PORT,ROW_STROBE_PIN);
		count_columns();
		delay_ms(1);
		gpio_clear(ROWS_PORT,ROW_STROBE_PIN);
		delay_ms(1000);
	}

	return 0;
}

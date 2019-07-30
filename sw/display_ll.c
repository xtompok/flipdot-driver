#include "display_ll.h"

#include <libopencm3/stm32/spi.h>

#include "hardware.h"
#include "delay.h"

void rows_spi_setup(void){
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

void rows_set(uint8_t bitmap){
	spi_send(ROWS_SPI,bitmap);	
	spi_send(ROWS_SPI,~bitmap);	
	gpio_set(ROWS_PORT,ROW_STROBE_PIN);
	delay_us(10000);
	gpio_clear(ROWS_PORT, ROW_STROBE_PIN);
}

void rows_off(void){
	spi_send(ROWS_SPI,0x00);	
	spi_send(ROWS_SPI,0x00);	
	gpio_set(ROWS_PORT,ROW_STROBE_PIN);
	delay_us(10000);
	gpio_clear(ROWS_PORT, ROW_STROBE_PIN);

}

void column_shift(void){
	delay_us(COL_DELAY_US);
	gpio_set(COLS_PORT, COL_CLK_PIN);
	delay_us(COL_DELAY_US);
	gpio_clear(COLS_PORT, COL_CLK_PIN);
	led2_toggle();
}

void column_setup(void){
	gpio_set_mode(COLS_PORT, GPIO_MODE_OUTPUT_2_MHZ,
		      GPIO_CNF_OUTPUT_PUSHPULL, COL_RST_PIN);
	gpio_set_mode(COLS_PORT, GPIO_MODE_OUTPUT_2_MHZ,
		      GPIO_CNF_OUTPUT_PUSHPULL, COL_CLK_PIN);
	gpio_set_mode(COLS_PORT, GPIO_MODE_OUTPUT_2_MHZ,
		      GPIO_CNF_OUTPUT_PUSHPULL, COL_DATA_PIN);
	gpio_set_mode(COLS_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, COL_RET_PIN);
	


}

void column_start(void){
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

uint16_t count_columns(void){
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

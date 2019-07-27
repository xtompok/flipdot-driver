#ifndef HARDWARE_H
#define HARDWARE_H

#include <libopencm3/stm32/gpio.h>

#define STEPUP_PORT	GPIOA
#define STEPUP_PIN	GPIO6

#define LEDS_PORT	GPIOA
#define LED1_PIN	GPIO1
#define LED2_PIN	GPIO2

#define COLS_PORT	GPIOB
#define COL_RST_PIN	GPIO6
#define COL_CLK_PIN	GPIO7
#define COL_DATA_PIN	GPIO8
#define COL_RET_PIN	GPIO9

#define ROWS_PORT	GPIOB
#define ROW_STROBE	GPIO4
#define ROW_CLK		GPIO5
#define ROW_DATA	GPIO6

#define USART_PORT	GPIOA


#endif

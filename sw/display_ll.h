#ifndef DISPLAY_LL_H
#define DISPLAY_LL_H

#include <stdint.h>

void rows_spi_setup(void);

void rows_set(uint8_t bitmap);
void rows_off(void);

void column_shift(void);

void column_setup(void);

void column_start(void);

uint16_t count_columns(void);

#endif

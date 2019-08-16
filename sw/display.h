#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

void fill(uint8_t row_pattern);
void print_char(unsigned char ch, uint16_t pos);
void print_str(char * str, uint16_t pos);

#endif

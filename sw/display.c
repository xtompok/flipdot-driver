#include "display.h"
#include "display_ll.h"
#include "delay.h"
#include "font.h"


void print_str(char * str, uint16_t pos){
	while (*str != '\0'){
		print_char((unsigned char)*str,pos);
		str++;
		pos++;	
	}	
}

void print_char(unsigned char ch, uint16_t pos){
	uint16_t col;
	col = pos*5;
	// HACK
	if (col >=30){
		col-=1;
	}
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
		delay(15);
		rows_off();
		delay(10);
		column_shift();	
		delay(1);
	}
		
}

void fill(uint8_t row_pattern){
	column_start();
	for (int j=0;j<50;j++){
		rows_set(row_pattern);
		delay(15);
		rows_off();
		delay(10);
		column_shift();
	}

}

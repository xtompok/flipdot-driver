#include <stdint.h>
#include <stdio.h>

#include "clock.h"
#include "delay.h"
#include "display.h"

static uint64_t start;
static uint8_t mem_hour;
static uint8_t mem_min;
static uint8_t mem_sec;


void cl_clock_setup(void){


}

void cl_timer_setup(void){
	start = millis();	
	print_str("00:00:00",0);
	mem_hour = 0;
	mem_min = 0;
	mem_sec = 0;
}

void cl_counter_setup(void){
	

}

void cl_clock_refresh(void){
		
}

void cl_timer_refresh(void){
	uint64_t now = millis();
	uint64_t dtime = now-start;
	uint8_t sec = (dtime/1000)%60;
	uint8_t min = (dtime/(1000*60))%60;
	uint8_t hour = dtime/(1000*60*60);
	if (hour != mem_hour){
		char hstr[3];
		snprintf(hstr,3,"%02d",hour);
		print_str(hstr,0);
		mem_hour = hour;
	}
	if (min != mem_min){
		char mstr[3];
		snprintf(mstr,3,"%02d",min);
		print_str(mstr,3);
		mem_min = min;
	}
	if (sec != mem_sec){
		char sstr[3];
		snprintf(sstr,3,"%02d",sec);
		print_str(sstr,6);
		mem_sec = sec;
	}
}

void cl_counter_refresh(void){
	
}

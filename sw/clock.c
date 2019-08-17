#include <stdint.h>
#include <stdio.h>

#include "clock.h"
#include "delay.h"
#include "display.h"

static uint64_t start;
static uint64_t end;
static uint8_t mem_hour;
static uint8_t mem_min;
static uint8_t mem_sec;


void cl_clock_setup(void){
	start = (13*60+20)*60*1000;	
	print_str("13:15:00",0);
	mem_hour = 255;
	mem_min = 255;
	mem_sec = 255;

}

void cl_timer_setup(void){
	start = millis();	
	print_str("00:00:00",0);
	mem_hour = 255;
	mem_min = 255;
	mem_sec = 255;
}

uint64_t cl_counter_setup(uint32_t sec){
	start = millis();	
	end = start + sec*1000;
	char timestr[6];
	snprintf(timestr,6,"%2d:%02d",sec/60,sec%60);
	print_inv_str(timestr,0);
	mem_hour = 255;
	mem_min = 255;
	mem_sec = 255;
	return end;
}

void cl_clock_refresh(void){
	uint64_t now = millis();
	uint64_t dtime = now-start;
	uint8_t sec = (dtime/1000)%60;
	uint8_t min = (dtime/(1000*60))%60;
	uint8_t hour = dtime/(1000*60*60);
	if (hour != mem_hour){
		char hstr[3];
		snprintf(hstr,4,"%02d:",hour);
		print_str(hstr,0);
		mem_hour = hour;
	}
	if (min != mem_min){
		char mstr[3];
		snprintf(mstr,4,"%02d:",min);
		print_str(mstr,3);
		mem_min = min;
	}/*
	if (sec != mem_sec){
		char sstr[3];
		snprintf(sstr,3,"%02d",sec);
		print_str(sstr,3);
		mem_sec = sec;
	}*/
		
}

void cl_timer_refresh(void){
	uint64_t now = millis();
	uint64_t dtime = now-start;
	uint8_t sec = (dtime/1000)%60;
	uint8_t min = (dtime/(1000*60))%60;
	uint8_t hour = dtime/(1000*60*60);
/*	if (hour != mem_hour){
		char hstr[3];
		snprintf(hstr,4,"%02d:",hour);
		print_str(hstr,0);
		mem_hour = hour;
	}
*/
	if (min != mem_min){
		if (min == 0){
			print_str("   ",0);	
			mem_min = min;
			return;
		}
		char mstr[3];
		snprintf(mstr,4,"%2d:",min);
		print_str(mstr,0);
		mem_min = min;
	}
	if (sec != mem_sec){
		char sstr[3];
		snprintf(sstr,3,"%02d",sec);
		print_str(sstr,3);
		mem_sec = sec;
	}
}

void cl_counter_refresh(void){
	uint64_t now = millis();
	uint64_t dtime = end-now;
	uint8_t sec = (dtime/1000)%60;
	uint8_t min = (dtime/(1000*60))%60;
	uint8_t hour = dtime/(1000*60*60);
/*	if (hour != mem_hour){
		char hstr[3];
		snprintf(hstr,4,"%02d:",hour);
		print_str(hstr,0);
		mem_hour = hour;
	}
*/
	if (min != mem_min){
		if (min == 0){
			print_inv_str("   ",0);	
			mem_min = min;
			return;
		}
		char mstr[3];
		snprintf(mstr,4,"%2d:",min);
		print_inv_str(mstr,0);
		mem_min = min;
	}
	if (sec != mem_sec){
		char sstr[3];
		snprintf(sstr,3,"%02d",sec);
		print_inv_str(sstr,3);
		mem_sec = sec;
	}
	
}

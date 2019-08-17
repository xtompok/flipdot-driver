#ifndef CLOCK_H
#define CLOCK_H

void cl_clock_setup(void);
void cl_timer_setup(void);
uint64_t cl_counter_setup(uint32_t sec);
void cl_clock_refresh(void);
void cl_timer_refresh(void);
void cl_counter_refresh(void);

#endif

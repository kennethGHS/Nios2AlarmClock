/*
 * clock.h
 *
 *  Created on: May 4, 2021
 *      Author: marco
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include "stdbool.h"
#include "sys/alt_stdio.h"


typedef enum clock_element{second, minute, hour} clock_element;
typedef enum clock_state{none, editing_alarm, editing_timer, editing_time} clock_state;

typedef struct _time {
	int seconds;
	int minutes;
	int hours;
} _time;

typedef struct _clock{
	_time* _time;
	_time* alarm;
	_time* timer;
	bool alarm_active;
	bool timer_active;
	clock_state state;
	clock_element selected;
}_clock;


_clock* clock_constructor();
_time* time_constructor();

void reset_clock(_clock* clock);
void reset_time(_time* time);
void increment(_time* clock, clock_element element);
void decrement(_time* clock, clock_element element);
void set_clock_state(_clock* clock, clock_state state);
void select_next_element(_clock* clock);
void select_previous_element(_clock* clock);
void tick(_clock* clock);
void increment_selected(_clock* clock);
void decrement_selected(_clock* clock);
void print_clock(_clock* clock);
bool times_are_equal(_time* time_1, _time* time_2);
bool time_is_zero(_time* time_1);
void reset_clock(_clock* clock);
_time* get_display_time(_clock* clock);

void print_time(_time* time);
void print_two_digits(int num);
void print_digit(int number);

#endif /* CLOCK_H_ */

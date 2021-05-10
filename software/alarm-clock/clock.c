/*
 * clock.c
 *
 *  Created on: May 4, 2021
 *      Author: Marco
 */

#include "clock.h"
#include "stdlib.h"
#include <stdio.h>

_clock* clock_constructor(){
	_clock* clock = malloc(sizeof(_clock));
	clock->_time = time_constructor();
	clock->timer = time_constructor();
	clock->alarm = time_constructor();
	clock->alarm_active = false;
	clock->timer_active = false;
	clock->state = none;
	clock->selected = second;

	return clock;
}

_time* time_constructor(){
	_time* time = malloc(sizeof(time));
	time->hours = 0;
	time->minutes = 0;
	time->seconds = 0;
	return time;
}

void reset_clock(_clock* clock){
	reset_time(clock->_time);
	reset_time(clock->alarm);
	reset_time(clock->timer);

}

void reset_time(_time* time){
	time->hours = 0;
	time->minutes = 0;
	time->seconds = 0;
}

void increment(_time* clock, clock_element element){
	if (element == second){
		if (clock->seconds == 59){
			clock->seconds = 0;
			increment(clock, minute);
		}else{
			clock->seconds++;
		}
	}else if (element == minute){
		if (clock->minutes == 59){
			clock->minutes = 0;
			increment(clock, hour);
		}else{
			clock->minutes++;
		}
	}else if (element == hour){
		if (clock->hours == 23){
			clock->hours = 0;
		}else{
			clock->hours++;
		}
	}
}

void decrement(_time* clock, clock_element element){
	if (element == second){
		if (clock->seconds == 0){
			clock->seconds = 59;
			decrement(clock, minute);
		}else{
			clock->seconds--;
		}
	}else if (element == minute){
		if (clock->minutes == 0){
			clock->minutes = 59;
			decrement(clock, hour);
		}else{
			clock->minutes--;
		}
	}else if (element == hour){
		if (clock->hours == 0){
			clock->hours = 23;
		}else{
			clock->hours--;
		}
	}
}

void set_clock_state(_clock* clock, clock_state state){
	clock->state = state;
}

void select_next_element(_clock* clock){

	if (clock->state == none) return;

	if (clock->selected == hour){
		clock->selected = second;
	}
	else{
		clock->selected++;
	}
}

void select_previous_element(_clock* clock){

	if (clock->state == none) return;

	if (clock->selected == second){
		clock->selected = hour;
	}
	else{
		clock->selected--;
	}
}

void tick(_clock* clock){
	increment(clock->_time, second);
	if(clock->alarm_active && times_are_equal(clock->_time, clock->alarm)){
		alt_putstr("Alarm went off");
	}
	if(clock->timer_active){
		decrement(clock->timer, second);
		if(time_is_zero(clock->timer)){
			alt_putstr("Timer went off");
			clock->timer_active = false;
		}

	}
}

void increment_selected(_clock* clock){
	if (clock->state == editing_alarm){
		increment(clock->alarm, clock->selected);
	}else if (clock->state == editing_timer){
		increment(clock->timer, clock->selected);
	}else if (clock->state == editing_time){
		increment(clock->_time, clock->selected);
	}
}

void decrement_selected(_clock* clock){
	if (clock->state == editing_alarm){
		decrement(clock->alarm, clock->selected);
	}else if (clock->state == editing_timer){
		decrement(clock->timer, clock->selected);
	}else if (clock->state == editing_time){
		decrement(clock->_time, clock->selected);
	}
}

_time* get_display_time(_clock* clock){
	if (clock->state == editing_alarm){
		return clock->alarm;
	}else if (clock->state == editing_timer){
		return clock->timer;
	}else {
		return clock->_time;
	}
}

void print_clock(_clock* clock){
	print_time(clock->_time);
	print_time(clock->alarm);
	print_time(clock->timer);
}


void print_time(_time* time){
	print_two_digits(time->hours);
	alt_putstr(":");
	print_two_digits(time->minutes);
	alt_putstr(":");
	print_two_digits(time->seconds);
	alt_putstr("\n");
}

void print_two_digits(int num){
	int dig1 = num%10;
	int dig2 = num/10 % 10;
	print_digit(dig2);
	print_digit(dig1);

}

void print_digit(int number){
	if (number == 0){
		alt_putstr("0");
	}
	else if (number == 1){
		alt_putstr("1");
	}
	else if (number == 2){
		alt_putstr("2");
	}
	else if (number == 3){
		alt_putstr("3");
	}
	else if (number == 4){
		alt_putstr("4");
	}
	else if (number == 5){
		alt_putstr("5");
	}
	else if (number == 6){
		alt_putstr("6");
	}
	else if (number == 7){
		alt_putstr("7");
	}
	else if (number == 8){
		alt_putstr("8");
	}
	else if (number == 9){
		alt_putstr("9");
	}
	else{
		alt_putstr("X");
	}
}

bool times_are_equal(_time* time_1, _time* time_2){
	return (time_1->seconds == time_2->seconds)
			&& (time_1->minutes == time_2->minutes)
			&& (time_1->hours == time_2->hours);
}

bool time_is_zero(_time* time_1){
	return (time_1->seconds == 0)
			&& (time_1->minutes == 0)
			&& (time_1->hours == 0);
}


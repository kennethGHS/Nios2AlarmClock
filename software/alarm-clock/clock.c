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
	return time;
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
//		printf("Alarm went off\n");

	}
	if(clock->timer_active){

		decrement(clock->timer, second);
		if(time_is_zero(clock->timer)){
//			printf("Timer went off\n");
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

void print_clock(_clock* clock){
	printf("time:  %02d:%02d:%02d\n", clock->_time->hours, clock->_time->minutes,clock->_time->seconds);
	printf("alarm: %02d:%02d:%02d\n", clock->alarm->hours, clock->alarm->minutes,clock->alarm->seconds);
	printf("timer: %02d:%02d:%02d\n\n", clock->timer->hours, clock->timer->minutes,clock->timer->seconds);
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


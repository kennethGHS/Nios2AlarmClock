#include "clock.h"


int main()
{
  _clock* clock = clock_constructor();
  print_clock(clock); 
  clock->alarm_active = 1;
  clock->timer_active = 1;
  clock->state = editing_alarm;
  select_next_element(clock);
  increment_selected(clock);
  clock->state = editing_timer;
  increment_selected(clock);
  clock->state = none;
  print_clock(clock);
  for (int i = 0; i < 100; i++){
    tick(clock);
  }
  print_clock(clock);
  return 0;
}

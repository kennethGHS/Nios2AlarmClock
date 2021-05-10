#include <altera_avalon_timer_regs.h>
#include "sys/alt_stdio.h"
#include <sys/alt_irq.h>
#include "altera_avalon_pio_regs.h"
#include "system.h"
#include "segment_display.h"
#include "clock.h"
#include <stdio.h>
#include "uart.h"

#define BAUD_RATE 115200

volatile int edge_capture_up, edge_capture_down, edge_capture_left,
		edge_capture_right;
volatile int edge_capture_alarm_active, edge_capture_timer_active,
		edge_capture_save;
volatile int edge_capture_alarm_editing, edge_capture_timer_editing,
		edge_capture_time_editing;

_clock* clock;

void handle_timer_interrupt();
void update_displays();
void handle_up_button_interrupt(void* context);
void handle_down_button_interrupt(void* context);
void handle_left_button_interrupt(void* context);
void handle_right_button_interrupt(void* context);

void handle_alarm_active_switch_interrupt(void* context);
void handle_timer_active_switch_interrupt(void* context);
void handle_alarm_editing_switch_interrupt(void* context);
void handle_timer_editing_switch_interrupt(void* context);
void handle_time_editing_switch_interrupt(void* context);
void handle_save_switch_interrupt(void* context);

void init_interrupts();
void add_pio_interrupt(int pio_base, alt_u32 ic_id, alt_u32 irq,
		alt_isr_func isr, void *isr_context);

volatile int * displays[] = { (int *) SEG_1_BASE, (int *) SEG_2_BASE,
		(int *) SEG_3_BASE, (int *) SEG_4_BASE, (int *) SEG_5_BASE,
		(int *) SEG_6_BASE };

volatile int * leds = (int *) LEDS_BASE;

int main() {

	*leds = 0b0000000000;
	clock = clock_constructor();
	reset_clock(clock);
	update_displays();


	init_interrupts();

	/* Event loop never exits. */
	while (1)
		;

	return 0;
}
void init_interrupts() {
	alt_irq_cpu_enable_interrupts();

	//Enables UART
	InitUart(BAUD_RATE, clock, leds);
	alt_ic_isr_register(UART_IRQ_INTERRUPT_CONTROLLER_ID, UART_IRQ, IsrUart, 0,
	 	0);
	alt_ic_irq_enable(UART_IRQ_INTERRUPT_CONTROLLER_ID, UART_IRQ);

	//Enables the timer
	IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_BASE,
			ALTERA_AVALON_TIMER_CONTROL_CONT_MSK | ALTERA_AVALON_TIMER_CONTROL_START_MSK | ALTERA_AVALON_TIMER_CONTROL_ITO_MSK);
	//Enables the timer interrupts
	alt_ic_isr_register(TIMER_IRQ_INTERRUPT_CONTROLLER_ID, TIMER_IRQ,
			handle_timer_interrupt, 0x00, 0x00);

	//Sets the PIO interrupts
	void* edge_capture_ptr_up = (void*) &edge_capture_up;
	add_pio_interrupt(PIOUPBUTTON_BASE, PIOUPBUTTON_IRQ_INTERRUPT_CONTROLLER_ID,
			PIOUPBUTTON_IRQ, handle_up_button_interrupt, edge_capture_ptr_up);

	void* edge_capture_ptr_down = (void*) &edge_capture_down;
	add_pio_interrupt(PIODOWNBUTTON_BASE,
			PIODOWNBUTTON_IRQ_INTERRUPT_CONTROLLER_ID, PIODOWNBUTTON_IRQ,
			handle_down_button_interrupt, edge_capture_ptr_down);

	void* edge_capture_ptr_left = (void*) &edge_capture_left;
	add_pio_interrupt(PIOLEFTBUTTON_BASE,
			PIOLEFTBUTTON_IRQ_INTERRUPT_CONTROLLER_ID, PIOLEFTBUTTON_IRQ,
			handle_left_button_interrupt, edge_capture_ptr_left);

	void* edge_capture_ptr_right = (void*) &edge_capture_right;
	add_pio_interrupt(PIORIGHTBUTTON_BASE,
			PIORIGHTBUTTON_IRQ_INTERRUPT_CONTROLLER_ID, PIORIGHTBUTTON_IRQ,
			handle_right_button_interrupt, edge_capture_ptr_right);

	void * edge_capture_ptr_alarm_active = (void *) &edge_capture_alarm_active;
	add_pio_interrupt(ALARMACTIVESWITCH_BASE,
			ALARMACTIVESWITCH_IRQ_INTERRUPT_CONTROLLER_ID,
			ALARMACTIVESWITCH_IRQ, handle_alarm_active_switch_interrupt,
			edge_capture_ptr_alarm_active);

	void * edge_capture_ptr_timer_active = (void *) &edge_capture_timer_active;
	add_pio_interrupt(TIMERACTIVESWITCH_BASE,
			TIMERACTIVESWITCH_IRQ_INTERRUPT_CONTROLLER_ID,
			TIMERACTIVESWITCH_IRQ, handle_timer_active_switch_interrupt,
			edge_capture_ptr_timer_active);

	void * edge_capture_ptr_alarm_editing = (void *) &edge_capture_alarm_editing;
	add_pio_interrupt(EDITALARMSWITCH_BASE,
			EDITALARMSWITCH_IRQ_INTERRUPT_CONTROLLER_ID, EDITALARMSWITCH_IRQ,
			handle_alarm_editing_switch_interrupt,
			edge_capture_ptr_alarm_editing);

	void * edge_capture_ptr_timer_editing = (void *) &edge_capture_timer_editing;
	add_pio_interrupt(EDITTIMERSWITCH_BASE,
			EDITTIMERSWITCH_IRQ_INTERRUPT_CONTROLLER_ID, EDITTIMERSWITCH_IRQ,
			handle_timer_editing_switch_interrupt,
			edge_capture_ptr_timer_editing);

	void * edge_capture_ptr_time_editing = (void *) &edge_capture_time_editing;
	add_pio_interrupt(EDITTIMESWITCH_BASE,
			EDITTIMESWITCH_IRQ_INTERRUPT_CONTROLLER_ID, EDITTIMESWITCH_IRQ,
			handle_time_editing_switch_interrupt,
			edge_capture_ptr_time_editing);

	void * edge_capture_ptr_save = (void *) &edge_capture_save;
	add_pio_interrupt(SAVESWITCH_BASE, SAVESWITCH_IRQ_INTERRUPT_CONTROLLER_ID,
			SAVESWITCH_IRQ, handle_save_switch_interrupt,
			edge_capture_ptr_save);
}

void add_pio_interrupt(int pio_base, alt_u32 ic_id, alt_u32 irq,
		alt_isr_func isr, void *isr_context) {

	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(pio_base, 0x1);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(pio_base, 0x0);
	alt_ic_isr_register(ic_id, irq, isr, isr_context, 0x0);
}

void handle_timer_interrupt() {
//	alt_putstr("Executed interruption \n");
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_BASE, 0);
	//Do things
	tick(clock, leds);
	update_displays();
}

void update_displays() {
	_time* display_time = get_display_time(clock);
	two_digit_conversion(display_time->hours, displays[5], displays[4]);
	two_digit_conversion(display_time->minutes, displays[3], displays[2]);
	two_digit_conversion(display_time->seconds, displays[1], displays[0]);
}

void handle_up_button_interrupt(void* context) {
//	alt_putstr("Executed interruption up button \n");
	volatile int* edge_capture_ptr = (volatile int*) context;
	*edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIOUPBUTTON_BASE);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIOUPBUTTON_BASE, 0);
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIOUPBUTTON_BASE);
	//Do things
	increment_selected(clock);

}

void handle_down_button_interrupt(void* context) {
//	alt_putstr("Executed interruption down button \n");
	volatile int* edge_capture_ptr = (volatile int*) context;
	*edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIODOWNBUTTON_BASE);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIODOWNBUTTON_BASE, 0);
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIODOWNBUTTON_BASE);
	//Do things
	decrement_selected(clock);
}

void handle_left_button_interrupt(void* context) {
//	alt_putstr("Executed interruption down button \n");
	volatile int* edge_capture_ptr = (volatile int*) context;
	*edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIOLEFTBUTTON_BASE);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIOLEFTBUTTON_BASE, 0);
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIOLEFTBUTTON_BASE);
	//Do things
	select_next_element(clock);
}

void handle_right_button_interrupt(void* context) {
//	alt_putstr("Executed interruption down button \n");
	volatile int* edge_capture_ptr = (volatile int*) context;
	*edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIORIGHTBUTTON_BASE);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIORIGHTBUTTON_BASE, 0);
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIORIGHTBUTTON_BASE);
	//Do things
	select_previous_element(clock);
}

void handle_alarm_active_switch_interrupt(void* context) {
//	alt_putstr("Executed interruption alarm active switch \n");
	volatile int* edge_capture_ptr = (volatile int*) context;
	*edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(ALARMACTIVESWITCH_BASE);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(ALARMACTIVESWITCH_BASE, 0);
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(ALARMACTIVESWITCH_BASE);
	//Do things
	if(clock->alarm_active){
		clock->alarm_active = 0;
		*leds = 0b0000000000;
	}else{
		clock->alarm_active = 1;
		*leds = 0b1000000000;
	}
 }

void handle_timer_active_switch_interrupt(void* context) {
//	alt_putstr("Executed interruption timer active switch \n");
	volatile int* edge_capture_ptr = (volatile int*) context;
	*edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(TIMERACTIVESWITCH_BASE);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(TIMERACTIVESWITCH_BASE, 0);
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(TIMERACTIVESWITCH_BASE);
	//Do things
	clock->timer_active = 1;
}

void handle_alarm_editing_switch_interrupt(void* context) {
//	alt_putstr("Executed interruption alarm editing switch \n");
	volatile int* edge_capture_ptr = (volatile int*) context;
	*edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(EDITALARMSWITCH_BASE);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(EDITALARMSWITCH_BASE, 0);
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(EDITALARMSWITCH_BASE);
	//Do things
	set_clock_state(clock, editing_alarm);
	*leds = 0b0000000000;
}

void handle_timer_editing_switch_interrupt(void* context) {
//	alt_putstr("Executed interruption timer editing switch \n");
	volatile int* edge_capture_ptr = (volatile int*) context;
	*edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(EDITTIMERSWITCH_BASE);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(EDITTIMERSWITCH_BASE, 0);
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(EDITTIMERSWITCH_BASE);
	//Do things
	set_clock_state(clock, editing_timer);
	*leds = 0b0000000000;
}

void handle_time_editing_switch_interrupt(void* context) {
//	alt_putstr("Executed interruption time editing switch \n");
	volatile int* edge_capture_ptr = (volatile int*) context;
	*edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(EDITTIMESWITCH_BASE);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(EDITTIMESWITCH_BASE, 0);
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(EDITTIMESWITCH_BASE);
	//Do things
	set_clock_state(clock, editing_time);
}

void handle_save_switch_interrupt(void* context) {
//	alt_putstr("Executed interruption save switch \n");
	volatile int* edge_capture_ptr = (volatile int*) context;
	*edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(SAVESWITCH_BASE);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SAVESWITCH_BASE, 0);
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(SAVESWITCH_BASE);
	//Do things
	set_clock_state(clock, none);
}


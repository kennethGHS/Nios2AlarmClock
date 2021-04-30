#include <altera_avalon_timer_regs.h>
//#include "sys/alt_stdio.h"
#include <sys/alt_irq.h>
#include "altera_avalon_pio_regs.h"
#include "system.h"

void handle_timer_interrupt();
void handle_button_interrupt(void * context);
void init_interrupts();

volatile int edge_capture;

int main()
{ 
  alt_putstr("Hello from Nios II!\n");
  /* Event loop never exits. */
  while (1);

  return 0;
}
void init_interrupts(){
	  alt_irq_cpu_enable_interrupts();
	  //Enables the timer
	  IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_BASE,
	                    ALTERA_AVALON_TIMER_CONTROL_CONT_MSK
	                  | ALTERA_AVALON_TIMER_CONTROL_START_MSK
	                  | ALTERA_AVALON_TIMER_CONTROL_ITO_MSK);
	  //Enables the timer interrupts
	    alt_ic_isr_register(TIMER_IRQ_INTERRUPT_CONTROLLER_ID,TIMER_IRQ, handle_timer_interrupt,0x00,0x00);

	    //Sets the button interrupts

	    void* edge_capture_ptr = (void*) &edge_capture;
	    /* Enable all 4 button interrupts. */
	    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIOBUTTOM_BASE, 0xf);
	    /* Reset the edge capture register. */
	    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIOBUTTOM_BASE, 0x0);
	    /* Register the ISR. */
	    alt_ic_isr_register(PIOBUTTOM_IRQ_INTERRUPT_CONTROLLER_ID,
	    		PIOBUTTOM_IRQ,
	    handle_button_interrupt,
	    edge_capture_ptr, 0x0);


}
void handle_timer_interrupt(){
	  alt_putstr("Executed interruption");
	  IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_BASE, 0);
	  //Do things
}
void handle_button_interrupt(void * context){
	volatile int* edge_capture_ptr = (volatile int*) context;
	*edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIOBUTTOM_BASE);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIOBUTTOM_BASE, 0);
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIOBUTTOM_BASE);
	//Do things
}
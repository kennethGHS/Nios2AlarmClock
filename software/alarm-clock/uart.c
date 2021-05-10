#include "uart.h"
#include "system.h"
#include "altera_avalon_uart_regs.h"
#include "sys/alt_stdio.h"

#define RX_BUFFER_SIZE_1 1024

#define TX_BUFFER_SIZE_1 1024

unsigned short TxHead_1 = 0;

unsigned short TxTail_1 = 0;

unsigned char tx_buffer_1[TX_BUFFER_SIZE_1];

unsigned short RxHead_1 = 0;

unsigned short RxTail_1 = 0;

unsigned char rx_buffer_1[RX_BUFFER_SIZE_1];

_clock *clock_ptr;

volatile int * leds_ptr;

void InitUart(unsigned int BaudRate, _clock *clock, volatile int *leds)

{

	unsigned int divisor;

	divisor = (ALT_CPU_FREQ / BaudRate) + 1;

	IOWR_ALTERA_AVALON_UART_DIVISOR(UART_BASE, divisor);

	IOWR_ALTERA_AVALON_UART_CONTROL(UART_BASE,
			ALTERA_AVALON_UART_CONTROL_RRDY_MSK);

	clock_ptr = clock;
	leds_ptr = leds;
}

void IsrUart(void* context, unsigned int id)

{

	int sr;
	sr = IORD_ALTERA_AVALON_UART_STATUS(UART_BASE);

	if (sr & ALTERA_AVALON_UART_STATUS_RRDY_MSK)
		;
	{
		rx_buffer_1[RxHead_1] = IORD_ALTERA_AVALON_UART_RXDATA(UART_BASE);
		IOWR_ALTERA_AVALON_UART_STATUS(UART_BASE, 0);
		if (++RxHead_1 > (RX_BUFFER_SIZE_1 - 1))
			RxHead_1 = 0;
	}

	if (sr & ALTERA_AVALON_UART_STATUS_TRDY_MSK) {
		if (IORD_ALTERA_AVALON_UART_CONTROL(
				UART_BASE) & ALTERA_AVALON_UART_CONTROL_TRDY_MSK)
			;
		{
			if (TxTail_1 != TxHead_1) {
				IOWR_ALTERA_AVALON_UART_TXDATA(UART_BASE,
						tx_buffer_1[TxTail_1]);

				if (++TxTail_1 > (TX_BUFFER_SIZE_1 - 1))
					TxTail_1 = 0;
			} else
				IOWR_ALTERA_AVALON_UART_CONTROL(UART_BASE,
						ALTERA_AVALON_UART_CONTROL_RRDY_MSK);
		}

	}

	parseReceived();

}

unsigned char EmptyUart()

{

	if (RxHead_1 == RxTail_1)
		return 1;

	return 0;

}

unsigned char GetUart(void)

{

	unsigned char rxChar;

	/* buffer is empty */

	rxChar = rx_buffer_1[RxTail_1];

	if (++RxTail_1 > (RX_BUFFER_SIZE_1 - 1))
		RxTail_1 = 0;

	return rxChar;

}

unsigned char PutUart(unsigned char in_char)

{

	unsigned short size;

	unsigned int z;

	z = IORD_ALTERA_AVALON_UART_STATUS(
			UART_BASE) & ALTERA_AVALON_UART_STATUS_TRDY_MSK;

	if ((TxHead_1 == TxTail_1) && z)
		IOWR_ALTERA_AVALON_UART_TXDATA(UART_BASE, in_char);

	else

	{

		if (TxHead_1 >= TxTail_1)
			size = TxHead_1 - TxTail_1;

		else
			size = ((TX_BUFFER_SIZE_1 - 1) - TxTail_1) + TxHead_1;

		if (size > (TX_BUFFER_SIZE_1 - 3))
			return (-1);

		tx_buffer_1[TxHead_1] = in_char;

		if (++TxHead_1 > (TX_BUFFER_SIZE_1 - 1))
			TxHead_1 = 0;

		z = IORD_ALTERA_AVALON_UART_CONTROL(
				UART_BASE) | ALTERA_AVALON_UART_CONTROL_TRDY_MSK;

		IOWR_ALTERA_AVALON_UART_CONTROL(UART_BASE, z);

	}

	return (1);

}

void parseReceived() {
	volatile int received, hour, min;
	unsigned char msc, lsc;
	volatile int msd, lsd;

	if (RxTail_1 > RxHead_1) {
		received = RxHead_1 + (RX_BUFFER_SIZE_1 - RxTail_1);
	} else {
		received = RxHead_1 - RxTail_1;
	}

	if (5 <= received) {

		// Hour
		msc = GetUart();

		while (!(msc > 47 && msc < 58)) {
			msc = GetUart();
		}

		msd = (int) msc - 48;
		lsc = GetUart();
		lsd = (int) lsc - 48;

		hour = msd * 10 + lsd;

		if (hour > 23) {
			return;
		}

		// Minutes
		msc = GetUart();

		msd = (int) msc - 48;
		lsc = GetUart();
		lsd = (int) lsc - 48;
		min = msd * 10 + lsd;

		if (min >= 60) {
			return;
		}

		// Set if all verifications pass
		if (clock_ptr->state == editing_alarm) {
			set_clock_alarm(clock_ptr, hour, min);
			*leds_ptr = 0b1000000000;
		} else {
			set_clock_time(clock_ptr, hour, min);
		}
	}
}

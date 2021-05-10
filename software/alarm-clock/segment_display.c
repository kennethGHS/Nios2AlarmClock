#include "segment_display.h"

volatile int single_digit_conversion(volatile int value) {
	int result = 0b01111111;

	switch (value) {
	case 0:
		result = 0b01000000;
		break;
	case 1:
		result = 0b01111001;
		break;
	case 2:
		result = 0b00100100;
		break;
	case 3:
		result = 0b00110000;
		break;
	case 4:
		result = 0b00011001;
		break;
	case 5:
		result = 0b00010010;
		break;
	case 6:
		result = 0b00000010;
		break;
	case 7:
		result = 0b01111000;
		break;
	case 8:
		result = 0b00000000;
		break;
	case 9:
		result = 0b00010000;
		break;
	default:
		result = 0b01111111;
	}

	return result;
}

void two_digit_conversion(volatile int value, volatile int *msd,
		volatile int *lsd) {
	*msd = single_digit_conversion(value / 10);
	*lsd = single_digit_conversion(value % 10);
}

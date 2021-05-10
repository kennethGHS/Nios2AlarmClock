
module ProjectFile (
	alarm_active_switch_export,
	clk_clk,
	down_button_export,
	edit_alarm_switch_export,
	edit_time_switch_export,
	edit_timer_switch_export,
	leds_export,
	left_button_export,
	reset_reset_n,
	right_button_export,
	save_switch_export,
	segment1_export,
	segment2_export,
	segment3_export,
	segment4_export,
	segment5_export,
	segment6_export,
	timer_active_switch_export,
	up_button_export,
	uart_rxd,
	uart_txd);	

	input		alarm_active_switch_export;
	input		clk_clk;
	input		down_button_export;
	input		edit_alarm_switch_export;
	input		edit_time_switch_export;
	input		edit_timer_switch_export;
	output	[9:0]	leds_export;
	input		left_button_export;
	input		reset_reset_n;
	input		right_button_export;
	input		save_switch_export;
	output	[7:0]	segment1_export;
	output	[7:0]	segment2_export;
	output	[7:0]	segment3_export;
	output	[7:0]	segment4_export;
	output	[7:0]	segment5_export;
	output	[7:0]	segment6_export;
	input		timer_active_switch_export;
	input		up_button_export;
	input		uart_rxd;
	output		uart_txd;
endmodule

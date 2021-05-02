
module ProjectFile (
	clk_clk,
	interrupbutton_export,
	reset_reset_n,
	segment1_export,
	segment2_export,
	segment3_export,
	segment4_export,
	segment5_export,
	segment6_export);	

	input		clk_clk;
	input		interrupbutton_export;
	input		reset_reset_n;
	output	[7:0]	segment1_export;
	output	[7:0]	segment2_export;
	output	[7:0]	segment3_export;
	output	[7:0]	segment4_export;
	output	[7:0]	segment5_export;
	output	[7:0]	segment6_export;
endmodule

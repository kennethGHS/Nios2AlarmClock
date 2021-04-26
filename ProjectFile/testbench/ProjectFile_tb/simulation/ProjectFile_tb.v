// ProjectFile_tb.v

// Generated using ACDS version 20.1 720

`timescale 1 ps / 1 ps
module ProjectFile_tb (
	);

	wire        projectfile_inst_clk_bfm_clk_clk;       // ProjectFile_inst_clk_bfm:clk -> [ProjectFile_inst:clk_clk, ProjectFile_inst_reset_bfm:clk]
	wire  [7:0] projectfile_inst_regs_export;           // ProjectFile_inst:regs_export -> ProjectFile_inst_regs_bfm:sig_export
	wire        projectfile_inst_reset_bfm_reset_reset; // ProjectFile_inst_reset_bfm:reset -> ProjectFile_inst:reset_reset_n

	ProjectFile projectfile_inst (
		.clk_clk       (projectfile_inst_clk_bfm_clk_clk),       //   clk.clk
		.regs_export   (projectfile_inst_regs_export),           //  regs.export
		.reset_reset_n (projectfile_inst_reset_bfm_reset_reset)  // reset.reset_n
	);

	altera_avalon_clock_source #(
		.CLOCK_RATE (50000000),
		.CLOCK_UNIT (1)
	) projectfile_inst_clk_bfm (
		.clk (projectfile_inst_clk_bfm_clk_clk)  // clk.clk
	);

	altera_conduit_bfm projectfile_inst_regs_bfm (
		.sig_export (projectfile_inst_regs_export)  // conduit.export
	);

	altera_avalon_reset_source #(
		.ASSERT_HIGH_RESET    (0),
		.INITIAL_RESET_CYCLES (50)
	) projectfile_inst_reset_bfm (
		.reset (projectfile_inst_reset_bfm_reset_reset), // reset.reset_n
		.clk   (projectfile_inst_clk_bfm_clk_clk)        //   clk.clk
	);

endmodule

// ProjectFile.v

// Generated using ACDS version 20.1 720

`timescale 1 ps / 1 ps
module ProjectFile (
		input  wire       clk_clk,       //   clk.clk
		output wire [7:0] regs_export,   //  regs.export
		input  wire       reset_reset_n  // reset.reset_n
	);

	wire  [31:0] cpu_data_master_readdata;                             // mm_interconnect_0:CPU_data_master_readdata -> CPU:d_readdata
	wire         cpu_data_master_waitrequest;                          // mm_interconnect_0:CPU_data_master_waitrequest -> CPU:d_waitrequest
	wire         cpu_data_master_debugaccess;                          // CPU:debug_mem_slave_debugaccess_to_roms -> mm_interconnect_0:CPU_data_master_debugaccess
	wire  [14:0] cpu_data_master_address;                              // CPU:d_address -> mm_interconnect_0:CPU_data_master_address
	wire   [3:0] cpu_data_master_byteenable;                           // CPU:d_byteenable -> mm_interconnect_0:CPU_data_master_byteenable
	wire         cpu_data_master_read;                                 // CPU:d_read -> mm_interconnect_0:CPU_data_master_read
	wire         cpu_data_master_write;                                // CPU:d_write -> mm_interconnect_0:CPU_data_master_write
	wire  [31:0] cpu_data_master_writedata;                            // CPU:d_writedata -> mm_interconnect_0:CPU_data_master_writedata
	wire  [31:0] cpu_instruction_master_readdata;                      // mm_interconnect_0:CPU_instruction_master_readdata -> CPU:i_readdata
	wire         cpu_instruction_master_waitrequest;                   // mm_interconnect_0:CPU_instruction_master_waitrequest -> CPU:i_waitrequest
	wire  [13:0] cpu_instruction_master_address;                       // CPU:i_address -> mm_interconnect_0:CPU_instruction_master_address
	wire         cpu_instruction_master_read;                          // CPU:i_read -> mm_interconnect_0:CPU_instruction_master_read
	wire         mm_interconnect_0_jtag_avalon_jtag_slave_chipselect;  // mm_interconnect_0:JTAG_avalon_jtag_slave_chipselect -> JTAG:av_chipselect
	wire  [31:0] mm_interconnect_0_jtag_avalon_jtag_slave_readdata;    // JTAG:av_readdata -> mm_interconnect_0:JTAG_avalon_jtag_slave_readdata
	wire         mm_interconnect_0_jtag_avalon_jtag_slave_waitrequest; // JTAG:av_waitrequest -> mm_interconnect_0:JTAG_avalon_jtag_slave_waitrequest
	wire   [0:0] mm_interconnect_0_jtag_avalon_jtag_slave_address;     // mm_interconnect_0:JTAG_avalon_jtag_slave_address -> JTAG:av_address
	wire         mm_interconnect_0_jtag_avalon_jtag_slave_read;        // mm_interconnect_0:JTAG_avalon_jtag_slave_read -> JTAG:av_read_n
	wire         mm_interconnect_0_jtag_avalon_jtag_slave_write;       // mm_interconnect_0:JTAG_avalon_jtag_slave_write -> JTAG:av_write_n
	wire  [31:0] mm_interconnect_0_jtag_avalon_jtag_slave_writedata;   // mm_interconnect_0:JTAG_avalon_jtag_slave_writedata -> JTAG:av_writedata
	wire  [31:0] mm_interconnect_0_cpu_debug_mem_slave_readdata;       // CPU:debug_mem_slave_readdata -> mm_interconnect_0:CPU_debug_mem_slave_readdata
	wire         mm_interconnect_0_cpu_debug_mem_slave_waitrequest;    // CPU:debug_mem_slave_waitrequest -> mm_interconnect_0:CPU_debug_mem_slave_waitrequest
	wire         mm_interconnect_0_cpu_debug_mem_slave_debugaccess;    // mm_interconnect_0:CPU_debug_mem_slave_debugaccess -> CPU:debug_mem_slave_debugaccess
	wire   [8:0] mm_interconnect_0_cpu_debug_mem_slave_address;        // mm_interconnect_0:CPU_debug_mem_slave_address -> CPU:debug_mem_slave_address
	wire         mm_interconnect_0_cpu_debug_mem_slave_read;           // mm_interconnect_0:CPU_debug_mem_slave_read -> CPU:debug_mem_slave_read
	wire   [3:0] mm_interconnect_0_cpu_debug_mem_slave_byteenable;     // mm_interconnect_0:CPU_debug_mem_slave_byteenable -> CPU:debug_mem_slave_byteenable
	wire         mm_interconnect_0_cpu_debug_mem_slave_write;          // mm_interconnect_0:CPU_debug_mem_slave_write -> CPU:debug_mem_slave_write
	wire  [31:0] mm_interconnect_0_cpu_debug_mem_slave_writedata;      // mm_interconnect_0:CPU_debug_mem_slave_writedata -> CPU:debug_mem_slave_writedata
	wire         mm_interconnect_0_ram_s1_chipselect;                  // mm_interconnect_0:RAM_s1_chipselect -> RAM:chipselect
	wire  [31:0] mm_interconnect_0_ram_s1_readdata;                    // RAM:readdata -> mm_interconnect_0:RAM_s1_readdata
	wire   [9:0] mm_interconnect_0_ram_s1_address;                     // mm_interconnect_0:RAM_s1_address -> RAM:address
	wire   [3:0] mm_interconnect_0_ram_s1_byteenable;                  // mm_interconnect_0:RAM_s1_byteenable -> RAM:byteenable
	wire         mm_interconnect_0_ram_s1_write;                       // mm_interconnect_0:RAM_s1_write -> RAM:write
	wire  [31:0] mm_interconnect_0_ram_s1_writedata;                   // mm_interconnect_0:RAM_s1_writedata -> RAM:writedata
	wire         mm_interconnect_0_ram_s1_clken;                       // mm_interconnect_0:RAM_s1_clken -> RAM:clken
	wire         mm_interconnect_0_reg_s1_chipselect;                  // mm_interconnect_0:REG_s1_chipselect -> REG:chipselect
	wire  [31:0] mm_interconnect_0_reg_s1_readdata;                    // REG:readdata -> mm_interconnect_0:REG_s1_readdata
	wire   [1:0] mm_interconnect_0_reg_s1_address;                     // mm_interconnect_0:REG_s1_address -> REG:address
	wire         mm_interconnect_0_reg_s1_write;                       // mm_interconnect_0:REG_s1_write -> REG:write_n
	wire  [31:0] mm_interconnect_0_reg_s1_writedata;                   // mm_interconnect_0:REG_s1_writedata -> REG:writedata
	wire         irq_mapper_receiver0_irq;                             // JTAG:av_irq -> irq_mapper:receiver0_irq
	wire  [31:0] cpu_irq_irq;                                          // irq_mapper:sender_irq -> CPU:irq
	wire         rst_controller_reset_out_reset;                       // rst_controller:reset_out -> [CPU:reset_n, JTAG:rst_n, RAM:reset, REG:reset_n, irq_mapper:reset, mm_interconnect_0:CPU_reset_reset_bridge_in_reset_reset, rst_translator:in_reset]
	wire         rst_controller_reset_out_reset_req;                   // rst_controller:reset_req -> [CPU:reset_req, RAM:reset_req, rst_translator:reset_req_in]

	ProjectFile_CPU cpu (
		.clk                                 (clk_clk),                                           //                       clk.clk
		.reset_n                             (~rst_controller_reset_out_reset),                   //                     reset.reset_n
		.reset_req                           (rst_controller_reset_out_reset_req),                //                          .reset_req
		.d_address                           (cpu_data_master_address),                           //               data_master.address
		.d_byteenable                        (cpu_data_master_byteenable),                        //                          .byteenable
		.d_read                              (cpu_data_master_read),                              //                          .read
		.d_readdata                          (cpu_data_master_readdata),                          //                          .readdata
		.d_waitrequest                       (cpu_data_master_waitrequest),                       //                          .waitrequest
		.d_write                             (cpu_data_master_write),                             //                          .write
		.d_writedata                         (cpu_data_master_writedata),                         //                          .writedata
		.debug_mem_slave_debugaccess_to_roms (cpu_data_master_debugaccess),                       //                          .debugaccess
		.i_address                           (cpu_instruction_master_address),                    //        instruction_master.address
		.i_read                              (cpu_instruction_master_read),                       //                          .read
		.i_readdata                          (cpu_instruction_master_readdata),                   //                          .readdata
		.i_waitrequest                       (cpu_instruction_master_waitrequest),                //                          .waitrequest
		.irq                                 (cpu_irq_irq),                                       //                       irq.irq
		.debug_reset_request                 (),                                                  //       debug_reset_request.reset
		.debug_mem_slave_address             (mm_interconnect_0_cpu_debug_mem_slave_address),     //           debug_mem_slave.address
		.debug_mem_slave_byteenable          (mm_interconnect_0_cpu_debug_mem_slave_byteenable),  //                          .byteenable
		.debug_mem_slave_debugaccess         (mm_interconnect_0_cpu_debug_mem_slave_debugaccess), //                          .debugaccess
		.debug_mem_slave_read                (mm_interconnect_0_cpu_debug_mem_slave_read),        //                          .read
		.debug_mem_slave_readdata            (mm_interconnect_0_cpu_debug_mem_slave_readdata),    //                          .readdata
		.debug_mem_slave_waitrequest         (mm_interconnect_0_cpu_debug_mem_slave_waitrequest), //                          .waitrequest
		.debug_mem_slave_write               (mm_interconnect_0_cpu_debug_mem_slave_write),       //                          .write
		.debug_mem_slave_writedata           (mm_interconnect_0_cpu_debug_mem_slave_writedata),   //                          .writedata
		.dummy_ci_port                       ()                                                   // custom_instruction_master.readra
	);

	ProjectFile_JTAG jtag (
		.clk            (clk_clk),                                              //               clk.clk
		.rst_n          (~rst_controller_reset_out_reset),                      //             reset.reset_n
		.av_chipselect  (mm_interconnect_0_jtag_avalon_jtag_slave_chipselect),  // avalon_jtag_slave.chipselect
		.av_address     (mm_interconnect_0_jtag_avalon_jtag_slave_address),     //                  .address
		.av_read_n      (~mm_interconnect_0_jtag_avalon_jtag_slave_read),       //                  .read_n
		.av_readdata    (mm_interconnect_0_jtag_avalon_jtag_slave_readdata),    //                  .readdata
		.av_write_n     (~mm_interconnect_0_jtag_avalon_jtag_slave_write),      //                  .write_n
		.av_writedata   (mm_interconnect_0_jtag_avalon_jtag_slave_writedata),   //                  .writedata
		.av_waitrequest (mm_interconnect_0_jtag_avalon_jtag_slave_waitrequest), //                  .waitrequest
		.av_irq         (irq_mapper_receiver0_irq)                              //               irq.irq
	);

	ProjectFile_RAM ram (
		.clk        (clk_clk),                             //   clk1.clk
		.address    (mm_interconnect_0_ram_s1_address),    //     s1.address
		.clken      (mm_interconnect_0_ram_s1_clken),      //       .clken
		.chipselect (mm_interconnect_0_ram_s1_chipselect), //       .chipselect
		.write      (mm_interconnect_0_ram_s1_write),      //       .write
		.readdata   (mm_interconnect_0_ram_s1_readdata),   //       .readdata
		.writedata  (mm_interconnect_0_ram_s1_writedata),  //       .writedata
		.byteenable (mm_interconnect_0_ram_s1_byteenable), //       .byteenable
		.reset      (rst_controller_reset_out_reset),      // reset1.reset
		.reset_req  (rst_controller_reset_out_reset_req),  //       .reset_req
		.freeze     (1'b0)                                 // (terminated)
	);

	ProjectFile_REG reg_inst (
		.clk        (clk_clk),                             //                 clk.clk
		.reset_n    (~rst_controller_reset_out_reset),     //               reset.reset_n
		.address    (mm_interconnect_0_reg_s1_address),    //                  s1.address
		.write_n    (~mm_interconnect_0_reg_s1_write),     //                    .write_n
		.writedata  (mm_interconnect_0_reg_s1_writedata),  //                    .writedata
		.chipselect (mm_interconnect_0_reg_s1_chipselect), //                    .chipselect
		.readdata   (mm_interconnect_0_reg_s1_readdata),   //                    .readdata
		.out_port   (regs_export)                          // external_connection.export
	);

	ProjectFile_mm_interconnect_0 mm_interconnect_0 (
		.CLK_clk_clk                           (clk_clk),                                              //                         CLK_clk.clk
		.CPU_reset_reset_bridge_in_reset_reset (rst_controller_reset_out_reset),                       // CPU_reset_reset_bridge_in_reset.reset
		.CPU_data_master_address               (cpu_data_master_address),                              //                 CPU_data_master.address
		.CPU_data_master_waitrequest           (cpu_data_master_waitrequest),                          //                                .waitrequest
		.CPU_data_master_byteenable            (cpu_data_master_byteenable),                           //                                .byteenable
		.CPU_data_master_read                  (cpu_data_master_read),                                 //                                .read
		.CPU_data_master_readdata              (cpu_data_master_readdata),                             //                                .readdata
		.CPU_data_master_write                 (cpu_data_master_write),                                //                                .write
		.CPU_data_master_writedata             (cpu_data_master_writedata),                            //                                .writedata
		.CPU_data_master_debugaccess           (cpu_data_master_debugaccess),                          //                                .debugaccess
		.CPU_instruction_master_address        (cpu_instruction_master_address),                       //          CPU_instruction_master.address
		.CPU_instruction_master_waitrequest    (cpu_instruction_master_waitrequest),                   //                                .waitrequest
		.CPU_instruction_master_read           (cpu_instruction_master_read),                          //                                .read
		.CPU_instruction_master_readdata       (cpu_instruction_master_readdata),                      //                                .readdata
		.CPU_debug_mem_slave_address           (mm_interconnect_0_cpu_debug_mem_slave_address),        //             CPU_debug_mem_slave.address
		.CPU_debug_mem_slave_write             (mm_interconnect_0_cpu_debug_mem_slave_write),          //                                .write
		.CPU_debug_mem_slave_read              (mm_interconnect_0_cpu_debug_mem_slave_read),           //                                .read
		.CPU_debug_mem_slave_readdata          (mm_interconnect_0_cpu_debug_mem_slave_readdata),       //                                .readdata
		.CPU_debug_mem_slave_writedata         (mm_interconnect_0_cpu_debug_mem_slave_writedata),      //                                .writedata
		.CPU_debug_mem_slave_byteenable        (mm_interconnect_0_cpu_debug_mem_slave_byteenable),     //                                .byteenable
		.CPU_debug_mem_slave_waitrequest       (mm_interconnect_0_cpu_debug_mem_slave_waitrequest),    //                                .waitrequest
		.CPU_debug_mem_slave_debugaccess       (mm_interconnect_0_cpu_debug_mem_slave_debugaccess),    //                                .debugaccess
		.JTAG_avalon_jtag_slave_address        (mm_interconnect_0_jtag_avalon_jtag_slave_address),     //          JTAG_avalon_jtag_slave.address
		.JTAG_avalon_jtag_slave_write          (mm_interconnect_0_jtag_avalon_jtag_slave_write),       //                                .write
		.JTAG_avalon_jtag_slave_read           (mm_interconnect_0_jtag_avalon_jtag_slave_read),        //                                .read
		.JTAG_avalon_jtag_slave_readdata       (mm_interconnect_0_jtag_avalon_jtag_slave_readdata),    //                                .readdata
		.JTAG_avalon_jtag_slave_writedata      (mm_interconnect_0_jtag_avalon_jtag_slave_writedata),   //                                .writedata
		.JTAG_avalon_jtag_slave_waitrequest    (mm_interconnect_0_jtag_avalon_jtag_slave_waitrequest), //                                .waitrequest
		.JTAG_avalon_jtag_slave_chipselect     (mm_interconnect_0_jtag_avalon_jtag_slave_chipselect),  //                                .chipselect
		.RAM_s1_address                        (mm_interconnect_0_ram_s1_address),                     //                          RAM_s1.address
		.RAM_s1_write                          (mm_interconnect_0_ram_s1_write),                       //                                .write
		.RAM_s1_readdata                       (mm_interconnect_0_ram_s1_readdata),                    //                                .readdata
		.RAM_s1_writedata                      (mm_interconnect_0_ram_s1_writedata),                   //                                .writedata
		.RAM_s1_byteenable                     (mm_interconnect_0_ram_s1_byteenable),                  //                                .byteenable
		.RAM_s1_chipselect                     (mm_interconnect_0_ram_s1_chipselect),                  //                                .chipselect
		.RAM_s1_clken                          (mm_interconnect_0_ram_s1_clken),                       //                                .clken
		.REG_s1_address                        (mm_interconnect_0_reg_s1_address),                     //                          REG_s1.address
		.REG_s1_write                          (mm_interconnect_0_reg_s1_write),                       //                                .write
		.REG_s1_readdata                       (mm_interconnect_0_reg_s1_readdata),                    //                                .readdata
		.REG_s1_writedata                      (mm_interconnect_0_reg_s1_writedata),                   //                                .writedata
		.REG_s1_chipselect                     (mm_interconnect_0_reg_s1_chipselect)                   //                                .chipselect
	);

	ProjectFile_irq_mapper irq_mapper (
		.clk           (clk_clk),                        //       clk.clk
		.reset         (rst_controller_reset_out_reset), // clk_reset.reset
		.receiver0_irq (irq_mapper_receiver0_irq),       // receiver0.irq
		.sender_irq    (cpu_irq_irq)                     //    sender.irq
	);

	altera_reset_controller #(
		.NUM_RESET_INPUTS          (1),
		.OUTPUT_RESET_SYNC_EDGES   ("deassert"),
		.SYNC_DEPTH                (2),
		.RESET_REQUEST_PRESENT     (1),
		.RESET_REQ_WAIT_TIME       (1),
		.MIN_RST_ASSERTION_TIME    (3),
		.RESET_REQ_EARLY_DSRT_TIME (1),
		.USE_RESET_REQUEST_IN0     (0),
		.USE_RESET_REQUEST_IN1     (0),
		.USE_RESET_REQUEST_IN2     (0),
		.USE_RESET_REQUEST_IN3     (0),
		.USE_RESET_REQUEST_IN4     (0),
		.USE_RESET_REQUEST_IN5     (0),
		.USE_RESET_REQUEST_IN6     (0),
		.USE_RESET_REQUEST_IN7     (0),
		.USE_RESET_REQUEST_IN8     (0),
		.USE_RESET_REQUEST_IN9     (0),
		.USE_RESET_REQUEST_IN10    (0),
		.USE_RESET_REQUEST_IN11    (0),
		.USE_RESET_REQUEST_IN12    (0),
		.USE_RESET_REQUEST_IN13    (0),
		.USE_RESET_REQUEST_IN14    (0),
		.USE_RESET_REQUEST_IN15    (0),
		.ADAPT_RESET_REQUEST       (0)
	) rst_controller (
		.reset_in0      (~reset_reset_n),                     // reset_in0.reset
		.clk            (clk_clk),                            //       clk.clk
		.reset_out      (rst_controller_reset_out_reset),     // reset_out.reset
		.reset_req      (rst_controller_reset_out_reset_req), //          .reset_req
		.reset_req_in0  (1'b0),                               // (terminated)
		.reset_in1      (1'b0),                               // (terminated)
		.reset_req_in1  (1'b0),                               // (terminated)
		.reset_in2      (1'b0),                               // (terminated)
		.reset_req_in2  (1'b0),                               // (terminated)
		.reset_in3      (1'b0),                               // (terminated)
		.reset_req_in3  (1'b0),                               // (terminated)
		.reset_in4      (1'b0),                               // (terminated)
		.reset_req_in4  (1'b0),                               // (terminated)
		.reset_in5      (1'b0),                               // (terminated)
		.reset_req_in5  (1'b0),                               // (terminated)
		.reset_in6      (1'b0),                               // (terminated)
		.reset_req_in6  (1'b0),                               // (terminated)
		.reset_in7      (1'b0),                               // (terminated)
		.reset_req_in7  (1'b0),                               // (terminated)
		.reset_in8      (1'b0),                               // (terminated)
		.reset_req_in8  (1'b0),                               // (terminated)
		.reset_in9      (1'b0),                               // (terminated)
		.reset_req_in9  (1'b0),                               // (terminated)
		.reset_in10     (1'b0),                               // (terminated)
		.reset_req_in10 (1'b0),                               // (terminated)
		.reset_in11     (1'b0),                               // (terminated)
		.reset_req_in11 (1'b0),                               // (terminated)
		.reset_in12     (1'b0),                               // (terminated)
		.reset_req_in12 (1'b0),                               // (terminated)
		.reset_in13     (1'b0),                               // (terminated)
		.reset_req_in13 (1'b0),                               // (terminated)
		.reset_in14     (1'b0),                               // (terminated)
		.reset_req_in14 (1'b0),                               // (terminated)
		.reset_in15     (1'b0),                               // (terminated)
		.reset_req_in15 (1'b0)                                // (terminated)
	);

endmodule

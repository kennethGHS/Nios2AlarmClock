	component ProjectFile is
		port (
			clk_clk       : in  std_logic                    := 'X'; -- clk
			regs_export   : out std_logic_vector(7 downto 0);        -- export
			reset_reset_n : in  std_logic                    := 'X'  -- reset_n
		);
	end component ProjectFile;

	u0 : component ProjectFile
		port map (
			clk_clk       => CONNECTED_TO_clk_clk,       --   clk.clk
			regs_export   => CONNECTED_TO_regs_export,   --  regs.export
			reset_reset_n => CONNECTED_TO_reset_reset_n  -- reset.reset_n
		);


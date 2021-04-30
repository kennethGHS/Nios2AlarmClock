	component ProjectFile is
		port (
			clk_clk               : in  std_logic                    := 'X'; -- clk
			interrupbutton_export : in  std_logic                    := 'X'; -- export
			reset_reset_n         : in  std_logic                    := 'X'; -- reset_n
			segment1_export       : out std_logic_vector(7 downto 0);        -- export
			segment2_export       : out std_logic_vector(7 downto 0);        -- export
			segment3_export       : out std_logic_vector(7 downto 0);        -- export
			segment4_export       : out std_logic_vector(7 downto 0);        -- export
			segment5_export       : out std_logic_vector(7 downto 0);        -- export
			segment6_export       : out std_logic_vector(7 downto 0)         -- export
		);
	end component ProjectFile;

	u0 : component ProjectFile
		port map (
			clk_clk               => CONNECTED_TO_clk_clk,               --            clk.clk
			interrupbutton_export => CONNECTED_TO_interrupbutton_export, -- interrupbutton.export
			reset_reset_n         => CONNECTED_TO_reset_reset_n,         --          reset.reset_n
			segment1_export       => CONNECTED_TO_segment1_export,       --       segment1.export
			segment2_export       => CONNECTED_TO_segment2_export,       --       segment2.export
			segment3_export       => CONNECTED_TO_segment3_export,       --       segment3.export
			segment4_export       => CONNECTED_TO_segment4_export,       --       segment4.export
			segment5_export       => CONNECTED_TO_segment5_export,       --       segment5.export
			segment6_export       => CONNECTED_TO_segment6_export        --       segment6.export
		);


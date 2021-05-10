	component ProjectFile is
		port (
			alarm_active_switch_export : in  std_logic                    := 'X'; -- export
			clk_clk                    : in  std_logic                    := 'X'; -- clk
			down_button_export         : in  std_logic                    := 'X'; -- export
			edit_alarm_switch_export   : in  std_logic                    := 'X'; -- export
			edit_time_switch_export    : in  std_logic                    := 'X'; -- export
			edit_timer_switch_export   : in  std_logic                    := 'X'; -- export
			leds_export                : out std_logic_vector(9 downto 0);        -- export
			left_button_export         : in  std_logic                    := 'X'; -- export
			reset_reset_n              : in  std_logic                    := 'X'; -- reset_n
			right_button_export        : in  std_logic                    := 'X'; -- export
			save_switch_export         : in  std_logic                    := 'X'; -- export
			segment1_export            : out std_logic_vector(7 downto 0);        -- export
			segment2_export            : out std_logic_vector(7 downto 0);        -- export
			segment3_export            : out std_logic_vector(7 downto 0);        -- export
			segment4_export            : out std_logic_vector(7 downto 0);        -- export
			segment5_export            : out std_logic_vector(7 downto 0);        -- export
			segment6_export            : out std_logic_vector(7 downto 0);        -- export
			timer_active_switch_export : in  std_logic                    := 'X'; -- export
			up_button_export           : in  std_logic                    := 'X'; -- export
			uart_rxd                   : in  std_logic                    := 'X'; -- rxd
			uart_txd                   : out std_logic                            -- txd
		);
	end component ProjectFile;

	u0 : component ProjectFile
		port map (
			alarm_active_switch_export => CONNECTED_TO_alarm_active_switch_export, -- alarm_active_switch.export
			clk_clk                    => CONNECTED_TO_clk_clk,                    --                 clk.clk
			down_button_export         => CONNECTED_TO_down_button_export,         --         down_button.export
			edit_alarm_switch_export   => CONNECTED_TO_edit_alarm_switch_export,   --   edit_alarm_switch.export
			edit_time_switch_export    => CONNECTED_TO_edit_time_switch_export,    --    edit_time_switch.export
			edit_timer_switch_export   => CONNECTED_TO_edit_timer_switch_export,   --   edit_timer_switch.export
			leds_export                => CONNECTED_TO_leds_export,                --                leds.export
			left_button_export         => CONNECTED_TO_left_button_export,         --         left_button.export
			reset_reset_n              => CONNECTED_TO_reset_reset_n,              --               reset.reset_n
			right_button_export        => CONNECTED_TO_right_button_export,        --        right_button.export
			save_switch_export         => CONNECTED_TO_save_switch_export,         --         save_switch.export
			segment1_export            => CONNECTED_TO_segment1_export,            --            segment1.export
			segment2_export            => CONNECTED_TO_segment2_export,            --            segment2.export
			segment3_export            => CONNECTED_TO_segment3_export,            --            segment3.export
			segment4_export            => CONNECTED_TO_segment4_export,            --            segment4.export
			segment5_export            => CONNECTED_TO_segment5_export,            --            segment5.export
			segment6_export            => CONNECTED_TO_segment6_export,            --            segment6.export
			timer_active_switch_export => CONNECTED_TO_timer_active_switch_export, -- timer_active_switch.export
			up_button_export           => CONNECTED_TO_up_button_export,           --           up_button.export
			uart_rxd                   => CONNECTED_TO_uart_rxd,                   --                uart.rxd
			uart_txd                   => CONNECTED_TO_uart_txd                    --                    .txd
		);


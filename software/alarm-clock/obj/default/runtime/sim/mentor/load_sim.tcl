# ------------------------------------------------------------------------------
# Top Level Simulation Script to source msim_setup.tcl
# ------------------------------------------------------------------------------
set QSYS_SIMDIR obj/default/runtime/sim
source msim_setup.tcl
# Copy generated memory initialization hex and dat file(s) to current directory
file copy -force a:/Nios2AlarmClock/software/alarm-clock/mem_init/hdl_sim/ProjectFile_RAM.dat ./ 
file copy -force a:/Nios2AlarmClock/software/alarm-clock/mem_init/ProjectFile_RAM.hex ./ 

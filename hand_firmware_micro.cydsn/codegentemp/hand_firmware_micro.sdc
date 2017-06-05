# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\MattiaCP\Documents\GITHUB\SoftHand\hand_firmware_micro.cydsn\hand_firmware_micro.cyprj
# Date: Tue, 04 Apr 2017 13:56:42 GMT
#set_units -time ns
create_clock -name {ADC_Ext_CP_Clk(routed)} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/dclk_1}]]
create_clock -name {CyILO} -period 10000 -waveform {0 5000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_clock -name {CyBUS_CLK(fixed-function)} -period 20.833333333333332 -waveform {0 10.4166666666667} [get_pins {ClockBlock/clk_bus_glb_ff}]
create_generated_clock -name {CLOCK_UART} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3 7} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_clock -name {ADC_Ext_CP_Clk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {WATCHDOG_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 1966081 3932161} [list [get_pins {ClockBlock/dclk_glb_2}]]
create_clock -name {WATCHDOG_CLK(fixed-function)} -period 40960000 -waveform {0 20.8333333333333} [get_pins {ClockBlock/dclk_glb_ff_2}]
create_generated_clock -name {ADC_theACLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 23 45} [list [get_pins {ClockBlock/aclk_glb_0}]]
create_clock -name {ADC_theACLK(fixed-function)} -period 458.33333333333331 -waveform {0 229.166666666667} [get_pins {ClockBlock/aclk_glb_ff_0}]
create_generated_clock -name {timer_clock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 49 97} [list [get_pins {ClockBlock/dclk_glb_4}]]
create_generated_clock -name {CLOCK_ENCODERS} -source [get_pins {ClockBlock/clk_sync}] -edges {1 241 481} [list [get_pins {ClockBlock/dclk_glb_5}]]
create_generated_clock -name {CLOCK_PWM} -source [get_pins {ClockBlock/clk_sync}] -edges {1 25 49} [list [get_pins {ClockBlock/dclk_glb_3}]]

set_false_path -from [get_pins {__ONE__/q}]
set_false_path -from [get_pins {__ZERO__/q}]

# Component constraints for C:\Users\MattiaCP\Documents\GITHUB\SoftHand\hand_firmware_micro.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\MattiaCP\Documents\GITHUB\SoftHand\hand_firmware_micro.cydsn\hand_firmware_micro.cyprj
# Date: Tue, 04 Apr 2017 13:56:28 GMT

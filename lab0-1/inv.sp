skywater 130nm Inverter

.option scale=1E-6
.include "./pdk/nfet.spice"
.include "./pdk/pfet.spice"

X0 Vout Vin VGND VGND sky130_fd_pr__nfet_01v8 w=650000u l=150000u
X1 Vout Vin VPWR VPWR sky130_fd_pr__pfet_01v8_hvt w=1e+06u l=150000u

VDD VPWR 0 1.8V
VSS VGND 0 0V
Vgate Vin GND PWL(0ns 0V 1.8ns 1.8V)

.tran 0.01ns 1.8ns

.control
run
setplot tran1
plot Vout vs time Vin
.endc

.end

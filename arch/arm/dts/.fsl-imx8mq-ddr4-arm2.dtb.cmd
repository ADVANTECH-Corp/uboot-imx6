cmd_arch/arm/dts/fsl-imx8mq-ddr4-arm2.dtb := mkdir -p arch/arm/dts/ ; cat arch/arm/dts/fsl-imx8mq-ddr4-arm2.dts  | aarch64-poky-linux-gcc -E -Wp,-MD,arch/arm/dts/.fsl-imx8mq-ddr4-arm2.dtb.d.pre.tmp -nostdinc -I./arch/arm/dts -I./arch/arm/dts/include -Iinclude -I./include -I./arch/arm/include -include ./include/linux/kconfig.h -D__ASSEMBLY__ -undef -D__DTS__ -x assembler-with-cpp -o arch/arm/dts/.fsl-imx8mq-ddr4-arm2.dtb.dts.tmp - ; dtc -O dtb -o arch/arm/dts/fsl-imx8mq-ddr4-arm2.dtb -b 0 -i arch/arm/dts/  -Wno-unit_address_vs_reg  -d arch/arm/dts/.fsl-imx8mq-ddr4-arm2.dtb.d.dtc.tmp arch/arm/dts/.fsl-imx8mq-ddr4-arm2.dtb.dts.tmp ; cat arch/arm/dts/.fsl-imx8mq-ddr4-arm2.dtb.d.pre.tmp arch/arm/dts/.fsl-imx8mq-ddr4-arm2.dtb.d.dtc.tmp > arch/arm/dts/.fsl-imx8mq-ddr4-arm2.dtb.d

source_arch/arm/dts/fsl-imx8mq-ddr4-arm2.dtb := arch/arm/dts/fsl-imx8mq.dtsi

deps_arch/arm/dts/fsl-imx8mq-ddr4-arm2.dtb := \
  arch/arm/dts/fsl-imx8-ca53.dtsi \
  arch/arm/dts/include/dt-bindings/clock/imx8mq-clock.h \
  arch/arm/dts/include/dt-bindings/gpio/gpio.h \
  arch/arm/dts/include/dt-bindings/input/input.h \
  arch/arm/dts/include/dt-bindings/input/linux-event-codes.h \
  arch/arm/dts/include/dt-bindings/interrupt-controller/arm-gic.h \
  arch/arm/dts/include/dt-bindings/interrupt-controller/irq.h \
  arch/arm/dts/include/dt-bindings/pinctrl/pins-imx8mq.h \
  arch/arm/dts/include/dt-bindings/thermal/thermal.h \

arch/arm/dts/fsl-imx8mq-ddr4-arm2.dtb: $(deps_arch/arm/dts/fsl-imx8mq-ddr4-arm2.dtb)

$(deps_arch/arm/dts/fsl-imx8mq-ddr4-arm2.dtb):

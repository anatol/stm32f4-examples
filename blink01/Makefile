ARMGNU = arm-none-eabi
CFLAGS = -std=c11 -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16

%.o : %.c
	$(ARMGNU)-gcc $(CFLAGS) -mcpu=cortex-m4 -mthumb -c $< -o $@

app.bin app.dfu : app.o
	$(ARMGNU)-ld -o app.elf -T stm32f4.ld $^
	$(ARMGNU)-objcopy -O binary app.elf app.bin
	$(ARMGNU)-objdump -D -marm --disassembler-options=force-thumb --target binary app.bin > app.asm
	dfu-convert -b 0x08000000:app.bin app.dfu

default: app.bin

clean:
	rm -f *.o app.{bin,asm,elf,dfu}

BOOT_SRCS_S = boot.s
BOOT_OBJS_O = boot.o

KERNEL_SRCS_S = set_dt.s isr.s
KERNEL_SRCS_C = common.c kernel.c gdt.c idt.c isr.c
KERNEL_OBJS_O = common.o kernel.o gdt.o idt.o isr.o asm.o

all: boot kernel image

boot:
	i686-elf-as $(BOOT_SRCS_S) -o $(BOOT_OBJS_O)

kernel:
	i686-elf-gcc -c $(KERNEL_SRCS_C) -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-as -c $(KERNEL_SRCS_S) -o asm.o

image:
	i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib $(BOOT_OBJS_O) $(KERNEL_OBJS_O) -lgcc
	mkdir -p isodir/boot/grub
	cp myos.bin isodir/boot/myos.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir

clean:
	@rm -f *.o
	@rm -f *.bin
	@rm -f *.iso
	@rm -rf isodir
	@echo "Cleaned!"

re: clean all

qemu:
	qemu-system-i386 -cdrom myos.iso -curses

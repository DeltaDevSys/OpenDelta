CLANG = clang
LD = ld
NASM = nasm
OBJCOPY = objcopy
QEMU = qemu-system-i386

BOOTBIN = boot.bin
KERNELELF = kernel.elf
KERNELBIN = kernel.bin
IMG = open-delta.img

CFLAGS = -ffreestanding -nostdlib -target i386-pc-none-elf \
         -march=i386 -m32 -Wall -Wextra -O2

all: $(IMG)

$(BOOTBIN): boot.asm
	$(NASM) -f bin -o $@ $<

kernel.o: kernel.c
	$(CLANG) $(CFLAGS) -c -o $@ $<

$(KERNELELF): kernel.o link.ld
	$(LD) -m elf_i386 -T link.ld -o $@ kernel.o
	$(OBJCOPY) -O binary $@ $(KERNELBIN)

$(IMG): $(BOOTBIN) $(KERNELELF)
	dd if=/dev/zero of=$@ bs=1M count=1 status=none
	dd if=$(BOOTBIN)   of=$@ conv=notrunc bs=512 count=1
	dd if=$(KERNELBIN) of=$@ conv=notrunc seek=2048   # 2048 × 512 = 0x00100000

run: $(IMG)
	$(QEMU) -drive format=raw,file=$(IMG),index=0,media=disk

clean:
	rm -f *.o $(BOOTBIN) $(KERNELELF) $(KERNELBIN) $(IMG)

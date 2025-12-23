NASM = nasm
NASMFLAGS = -f elf32
LD = ld
LDFLAGS = -m elf_i386

TARGET = kernel_loader

OBJS = boot.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.asm
	$(NASM) $(NASMFLAGS) $< -o $@

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean


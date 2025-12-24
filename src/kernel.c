/*
    это лишь прототип будущего ядра.
*/
#include <stdint.h>
#include <stdbool.h>

#define KERNEL_MAGIC   0x12345678
#define KERNEL_VERSION 0x00000001

typedef struct {
    uint32_t magic;
    uint32_t version;
} KernelBase;

typedef struct {
    bool     init;
    uint32_t tick_count;
} SystemState;

static KernelBase base = {
    .magic   = KERNEL_MAGIC,
    .version = KERNEL_VERSION
};

static SystemState sys_state = {
    .init       = false,
    .tick_count = 0
};

#define VGA_WIDTH  80
#define VGA_HEIGHT 25

static uint16_t *const VGA_BUFFER = (uint16_t *)0xB8000;
static uint8_t bg_color = 0x00;
static uint8_t fg_color = 0x07;

static inline uint16_t vga_entry(unsigned char ch, uint8_t fg, uint8_t bg) {
    return (uint16_t)ch | ((uint16_t)fg << 8) | ((uint16_t)bg << 12);
}

static void vga_putchar_at(char c, int x, int y) {
    if (x < 0 || x >= VGA_WIDTH || y < 0 || y >= VGA_HEIGHT) return;
    VGA_BUFFER[y * VGA_WIDTH + x] = vga_entry((unsigned char)c, fg_color, bg_color);
}

static int cursor_x = 0;
static int cursor_y = 0;

static void vga_putchar(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } 
    
    else if (c == '\r') {
        cursor_x = 0;
    } 
    else {
        vga_putchar_at(c, cursor_x, cursor_y);
        cursor_x++;
        if (cursor_x >= VGA_WIDTH) {
            cursor_x = 0;
            cursor_y++;
        }
    }

    if (cursor_y >= VGA_HEIGHT) {
        for (int row = 1; row < VGA_HEIGHT; row++) {
            for (int col = 0; col < VGA_WIDTH; col++) {
                VGA_BUFFER[(row - 1) * VGA_WIDTH + col] = VGA_BUFFER[row * VGA_WIDTH + col];
            }
        }
        
        uint16_t blank = vga_entry(' ', fg_color, bg_color);
        for (int col = 0; col < VGA_WIDTH; col++) {
            VGA_BUFFER[(VGA_HEIGHT - 1) * VGA_WIDTH + col] = blank;
        }
        cursor_y = VGA_HEIGHT - 1;
    }
}

static void vga_puts(const char *s) {
    while (*s) {
        vga_putchar(*s++);
    }
}

static void itoa_decimal(int value, char *buf) {
    char tmp[12];
    int i = 0;
    bool neg = false;
    
    if (value == 0) {
        buf[0] = '0'; buf[1] = '\0'; return;
    }
    
    if (value < 0) {
        neg = true; value = -value;
    }

    while (value && i < (int)sizeof(tmp)-1) {
        tmp[i++] = '0' + (value % 10);
        value /= 10;
    }

    if (neg) tmp[i++] = '-';
    int j = 0;

    while (i > 0) {
        buf[j++] = tmp[--i];
    }

    buf[j] = '\0';
}

static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static void pit_init(uint32_t frequency) {
    if (frequency == 0) return;
    uint32_t divisor = 1193180 / frequency;
    outb(0x43, 0x34);
    outb(0x40, (uint8_t)(divisor & 0xFF));
    outb(0x40, (uint8_t)((divisor >> 8) & 0xFF));
}

__attribute__((noreturn))


static void panic(const char *msg) {
    vga_puts("KERNEL PANIC: ");
    vga_puts(msg);
    vga_putchar('\n');
    for (;; ) asm volatile ("hlt");
}

static void tick(void) {
    sys_state.tick_count++;
    char buf[32];
    itoa_decimal(sys_state.tick_count, buf);
    vga_puts("tick: ");
    vga_puts(buf);
    vga_puts("\n");
}

static void vga_clear(void) {
    uint16_t blank = vga_entry(' ', fg_color, bg_color);
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) VGA_BUFFER[i] = blank;
    cursor_x = 0; cursor_y = 0;
}

void _start(void) {
    vga_clear();
    vga_puts("Simple kernel starting...\n");
    if (base.magic != KERNEL_MAGIC) {
        panic("bad kernel magic");
    }

    if (base.version != KERNEL_VERSION) {
        panic("bad kernel version");
    }

    sys_state.init = true;
   
      /* output base info */
    vga_puts("System init: [ OK ]\n");
    vga_puts("OS: OpenDelta(OS)\n");
    vga_puts("OS version: v0.1\n");
    vga_puts("Shell: dltsh(not working)\n");
    vga_puts("Shell version: v.0.0.0.12-c");

    pit_init(10);
    for (;;) {
        tick();
        for (volatile uint32_t i = 0; i < 1000000; i++) {
            asm volatile ("pause");
        }
    }
}

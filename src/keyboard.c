#define KBD_BUF_SIZE 256
#define INTERNAL_SPACE 0x01

static bool shift_down = false;
static bool caps_lock = false;

static char kbd_buf[KBD_BUF_SIZE];
static volatile int kbd_head = 0;
static volatile int kbd_tail = 0; 

char get_ascii_char(uint8_t scancode)
{
    if (is_alpha(scancode)) {
        bool upper = shift_down ^ caps_lock;
        char base = scancode_to_ascii[(uint8_t)scancode];
        return upper ? my_toupper(base) : base;
    }

    if (shift_down) {
        return scancode_to_ascii_shited[(uint8_t)scancode];
    }

    else {
        return scancode_to_ascii[(uint8_t)scancode];
    }
}

static inline unsigned long irq_save_flags(void)
{
    unsigned long flags;
    asm volatile("pushf; pop %0; cli": "=g"(flags)::"memory");
    return flags;
}

static inline void irq_restore_flags(unsigned long flags) {
    asm volatile("push %0; popf" :: "g"(flags) : "memory", "cc");
}

void kbd_buffer_push(char c) {
    unsigned long flags = irq_save_flags();
    int next = (kbd_head +1) % KBD_BUF_SIZE;
    if (next != kbd_tail) {
        kbd_buf[kbd_head] = c;
        kbd_head = next;
    }

    else {}

    irq_restore_flags(flags);
}

char kbd_getchar(void) 
{
    unsigned long flags = irq_save_flags();
    if (kbd_head == kbd_tail) {
        irq_restore_flags(flags);
        return -1;
    }

    char c = (char)kbd_buf[kbd_tail];
    kbd_tail = (kbd_tail + 1) % KBD_BUF_SIZE;
    irq_restore_flags(flags);
    return c;
}

void keyboard_handler(void)
{
    uint8_t code = inb(KEYBOARD_PORT);

    bool released = code & 0x80;
    uint8_t key = code & 0x7F;

    if (key == KEY_LSHIFT || key == KEY_RSHIFT) {
        shift_down = !released;
        pic_send_eoi(1);
        return;
    }

    if (ley == KEY_CAPSLOCK && !released) {
        caps_lock = !caps_lock;
        pic_send_eoi(1);
        return;
    }

    if (!released) {
        char ch = get_ascii_char(key);
        if (ch) {
            kbd_buffer_push(ch);
        }
    }

    pic_send_eoi(1);
}

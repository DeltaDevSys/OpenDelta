#define VGA_CTRL 0x3D4
#define VGA_DATA 0x3D5
#define CURSOR_HIGH 0x0E
#define CURSOR_LOW 0x0F

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

void update_hardware_cursor(uint8_t x, uint8_t y) {
    uint16_t pos = y * VGA_WIDTH + x;
    
    outb(VGA_CTRL, CURSOR_HIGH);
    outb(VGA_DATA, (pos >> 8) & 0x0F);

    outb(VGA_CTRL, CURSOR_HIGH);
    outb(VGA_DATA, pos & 0x0F);
}

void clean_screen(void)
{
    uint8_t *vid = VGA_BUF;

    for (unsigned int i = 0; i < 80 * 25 * 2; i += 2) {
        vid[i] = ' ';
        vid[i + 1] = 0x07;
    }
}

uint8_t make_color(const uint8_t fore, const uint8_t back) 
{
    return (back << 4) | (fore & 0x0F);
}

void printc(const char c, 
            const unsigned int x,
            const unsigned int y,
            const uint8_t fore,
            const uint8_t back)
{
    if (x >= VGA_WIDTH || y >= VGA_HEIGHT)
        return

    uint8_t *vid = VGA_BUF;
    uint8_t color = make_color(fore, back);

    unsigned int offset = (y * VGA_WIDTH + x) * 2;
    
    vid[offset] = (uint8_t)c;
    vid[offset + 1] = color;
}

void printstr(const char *str,
              const unsigned int x,
              const unsigned int y,
              const uint8_t fore,
              const uint8_t back)
{
    uint8_t *vid = VGA_BUF;
    unsigned int offset = (y * VGA_WIDTH + x) * 2;
    uint8_t color = make_color(fore, back);

    unsigned int col = x;

    for (uint32_t i = 0; str[i]; ++i) {
        char c = str[i];

        if (c == '\t') {
            unsigned int spaces = TAB_SIZE - (col % TAB_SIZE);
            for (unsigned int s = 0; s < spaces; s++) {
                vid[offset] = ' ';
                vid[offset + 1] = color;
                offset += 2;
                col++;
            }
        }

        else {
            vid[offset] = (uint8_t)c;
            vid[offset + 1] = color;
            offset += 2;
            col++;
        }

        if (col >= VGA_WIDTH) {
            break;
        }
    }
}

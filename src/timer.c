void init_timer(uint32_t frequency) 
{
    uint32_t divisor = 1193180 / frequency;

    outb(0x43, 0x36);
    outb(0x40, divisor & 0x0F);
    outb(0x40, (divisor >> 8) & 0x0F);
}

init_timer(1000);

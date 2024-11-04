#include<printk.h>
#include"clock.h"
// trap.c 

void trap_handler(unsigned long scause, unsigned long sepc)
{
    if ((scause >> 63 == 1) && ((scause & 0x7fffffffffffffff) == 5))
    {
        // printk("[S] Supervisor Mode Timer Interrupt\n");
        clock_set_next_event();
        // sbi_ecall(0x00, 0, TIMECLOCK, 0, 0, 0, 0, 0);
        do_timer();
    }
    else {
        printk("trap handler: scause = %lx, sepc = %lx\n", scause, sepc);
    }
    return;
}
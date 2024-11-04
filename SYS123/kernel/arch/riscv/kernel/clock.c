// clock.c
#include"clock.h"
#include"sbi.h"


unsigned long TIMECLOCK = 10000000;

unsigned long get_cycles() {
    unsigned long timer;
    __asm__ volatile(
        "rdtime %[timer]\n"
        :[timer]"=r"(timer)
        :
        :"memory"
    );
    return timer;
}

void clock_set_next_event() {
    // sbi_set_timer(TIMECLOCK);
    
    // 下一次 时钟中断 的时间点
    unsigned long next = get_cycles() + TIMECLOCK;
    // 使用 sbi_ecall 来完成对下一次时钟中断的设置
    sbi_ecall(0x00, 0, next, 0, 0, 0, 0, 0);
} 



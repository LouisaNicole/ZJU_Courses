#include "print.h"
#include "sbi.h"
#include "types.h"

extern void test();

extern char _stext[];
extern char _srodata[];
extern char _sdata[];
extern char _sbss[];

int start_kernel() 
{
    // printk("%d", 2024);
    printk("2024 ZJU Computer System III\n");

    // printk("_stext = %ld\n", *_stext);
    // printk("_srodata = %ld\n", *_srodata);

    // *_stext = 0;
    // *_srodata = 0;

    // printk("_stext = %ld\n", *_stext);
    // printk("_srodata = %ld\n", *_srodata);

    test(); // DO NOT DELETE !!!

	return 0;
}

#include "defs.h"
#include "string.h"
#include "vm.h"
// arch/riscv/kernel/vm.c

/* early_pgtbl: 用于 setup_vm 进行 1GB 的 映射。 */
unsigned long early_pgtbl[512] __attribute__((__aligned__(0x1000)));
/* swapper_pg_dir: kernel pagetable 根目录， 在 setup_vm_final 进行映射。 */
unsigned long  swapper_pg_dir[512] __attribute__((__aligned__(0x1000)));

void setup_vm(void)
{
    /*
    1. 由于是进行 1GB 的映射 这里不需要使用多级页表
    2. 将 va 的 64bit 作为如下划分： | high bit | 9 bit | 30 bit |
        high bit 可以忽略
        中间9 bit 作为 early_pgtbl 的 index
        低 30 bit 作为 页内偏移 这里注意到 30 = 9 + 9 + 12， 即我们只使用根页表， 根页表的每个 entry 都对应 1GB 的区域。
    3. Page Table Entry 的权限 V | R | W | X 位设置为 1
    */
    memset(early_pgtbl, 0, PGSIZE);
    uint64 index, entry;
    // entry[53:28] = PPN[2], entry[3:0] = XWRV
    // PA == VA
    index = ((uint64)PHY_START >> 30) & 0x01FF;
    entry = ((PHY_START & 0x00FFFFFFC0000000) >> 2) | 0xCF;
    early_pgtbl[index] = entry;
    // PA + PV2VA_OFFSET == VA
    index = ((uint64)VM_START >> 30) & 0x01FF;
    entry = ((PHY_START & 0x00FFFFFFC0000000) >> 2) | 0xCF;
    early_pgtbl[index] = entry;
    printk("...setup_vm\n");
}

extern char _stext[];
extern char _srodata[];
extern char _sdata[];
extern char _sbss[];

void setup_vm_final(void) {
    memset(swapper_pg_dir, 0x0, PGSIZE);

    // No OpenSBI mapping required
    
    // mapping kernel text X|-|R|V
    uint64 va = (uint64)&_stext;
    uint64 pa = (uint64)(&_stext) - PA2VA_OFFSET;
    uint64 sz = (uint64)&_srodata - (uint64)(&_stext);
    create_mapping(swapper_pg_dir, va, pa, sz, 0xB | 0x40 | 0x80);

    // mapping kernel rodata -|-|R|V
    va = (uint64)(&_srodata);
    pa = (uint64)(&_srodata) - PA2VA_OFFSET;
    sz = (uint64)(&_sdata) - (uint64)(&_srodata);
    create_mapping(swapper_pg_dir, va, pa, sz, 0x3 | 0x40 | 0x80);
  
    // mapping other memory -|W|R|V
    va = (uint64)(&_sdata);
    pa = (uint64)(&_sdata) - PA2VA_OFFSET;
    sz = PHY_SIZE - ((uint64)(&_sdata) - (uint64)&_stext);
    create_mapping(swapper_pg_dir, va, pa, sz, 0x7 | 0x80 | 0x40);
  
    // set satp with swapper_pg_dir

    printk("...create_mapping\n");
    uint64 satp = (((uint64)(swapper_pg_dir) - PA2VA_OFFSET) >> 12) | (1L << 63);
    // 一定要写成 1L，写 1 是过不了的
    __asm__ volatile("csrw satp, %[_satp]" ::[_satp] "r" (satp) :);

    // flush TLB
    asm volatile("sfence.vma zero, zero");

    // flush icache
    asm volatile("fence.i");

    return;
}


/* 创建多级页表映射关系 */
void create_mapping(uint64 *pgtbl, uint64 va, uint64 pa, uint64 sz, uint64 perm) {
    /*
    pgtbl 为根页表的基地址
    va, pa 为需要映射的虚拟地址、物理地址
    sz 为映射的大小
    perm 为映射的读写权限

    将给定的一段虚拟内存映射到物理内存上
    物理内存需要分页
    创建多级页表的时候可以使用 kalloc() 来获取一页作为页表目录
    可以使用 V bit 来判断页表项是否存在
    */
   uint64 end = va + sz;
   uint64 vpn2, vpn1, vpn0;
   while (va < end)
   {
        vpn2 = (va & 0x7FC0000000) >> 30;
        vpn1 = (va & 0x3FE00000) >> 21;
        vpn0 = (va & 0x1FF000) >> 12;

        uint64 *pgtbl_first = pgtbl;
        uint64 *pgtbl_second;
        if(pgtbl_first[vpn2] & 0x1){
            pgtbl_second = (uint64)((pgtbl[vpn2] >> 10) << 12);
        }else {
            pgtbl_second = (uint64)(kalloc() - PA2VA_OFFSET);
            pgtbl_first[vpn2] = (((uint64)pgtbl_second >> 2) | 1);
        }

        uint64 *pgtbl_third;
        if(pgtbl_second[vpn1] & 0x1){
            pgtbl_third = (uint64)((pgtbl_second[vpn1] >> 10) << 12);
        }else {
            pgtbl_third = (uint64)(kalloc() - PA2VA_OFFSET);
            pgtbl_second[vpn1] = (((uint64)pgtbl_third >> 2) | 1);
        }

        if(!(pgtbl_third[vpn0] & 0x1)){
            pgtbl_third[vpn0] = (((pa >> 12) << 10) | perm);
        }

        va += PGSIZE;
        pa += PGSIZE;
   }
   
}

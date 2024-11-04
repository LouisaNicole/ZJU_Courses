
../../vmlinux:     file format elf64-littleriscv


Disassembly of section .text:

ffffffe000200000 <_skernel>:

.section .text.init
.globl _start
.globl _end
_start:
  la sp, boot_stack_top
ffffffe000200000:	00005117          	auipc	sp,0x5
ffffffe000200004:	02010113          	addi	sp,sp,32 # ffffffe000205020 <task>

  call setup_vm
ffffffe000200008:	391000ef          	jal	ra,ffffffe000200b98 <setup_vm>
  call relocate
ffffffe00020000c:	068000ef          	jal	ra,ffffffe000200074 <relocate>

  la t0, _traps
ffffffe000200010:	00000297          	auipc	t0,0x0
ffffffe000200014:	12028293          	addi	t0,t0,288 # ffffffe000200130 <_traps>
  csrw stvec, t0
ffffffe000200018:	10529073          	csrw	stvec,t0
  csrr t0, sie
ffffffe00020001c:	104022f3          	csrr	t0,sie
  ori t0, t0, 0x20
ffffffe000200020:	0202e293          	ori	t0,t0,32
  csrw sie, t0
ffffffe000200024:	10429073          	csrw	sie,t0
  
  rdtime a0
ffffffe000200028:	c0102573          	rdtime	a0
  li t0, 10000000
ffffffe00020002c:	009892b7          	lui	t0,0x989
ffffffe000200030:	6802829b          	addiw	t0,t0,1664 # 989680 <_skernel-0xffffffdfff876980>
  add a0, a0, t0
ffffffe000200034:	00550533          	add	a0,a0,t0

  xor a7, a7, a7
ffffffe000200038:	0118c8b3          	xor	a7,a7,a7
  xor a6, a6, a6
ffffffe00020003c:	01084833          	xor	a6,a6,a6
  xor a5, a5, a5
ffffffe000200040:	00f7c7b3          	xor	a5,a5,a5
  xor a4, a4, a4
ffffffe000200044:	00e74733          	xor	a4,a4,a4
  xor a3, a3, a3
ffffffe000200048:	00d6c6b3          	xor	a3,a3,a3
  xor a2, a2, a2
ffffffe00020004c:	00c64633          	xor	a2,a2,a2
  xor a1, a1, a1
ffffffe000200050:	00b5c5b3          	xor	a1,a1,a1
  ecall
ffffffe000200054:	00000073          	ecall

  csrr t0, sstatus
ffffffe000200058:	100022f3          	csrr	t0,sstatus
  ori t0, t0, 1<<1
ffffffe00020005c:	0022e293          	ori	t0,t0,2
  csrw sstatus, t0
ffffffe000200060:	10029073          	csrw	sstatus,t0

  call mm_init
ffffffe000200064:	3ac000ef          	jal	ra,ffffffe000200410 <mm_init>
  call setup_vm_final
ffffffe000200068:	3d5000ef          	jal	ra,ffffffe000200c3c <setup_vm_final>
  call task_init
ffffffe00020006c:	3ec000ef          	jal	ra,ffffffe000200458 <task_init>

  # li a0, 2022
  # j _srodata
  j start_kernel
ffffffe000200070:	7490006f          	j	ffffffe000200fb8 <start_kernel>

ffffffe000200074 <relocate>:

relocate:
    # set ra = ra + PA2VA_OFFSET
    # set sp = sp + PA2VA_OFFSET (If you have set the sp before)
    li t0, 0xffffffdf80000000
ffffffe000200074:	fbf0029b          	addiw	t0,zero,-65
ffffffe000200078:	01f29293          	slli	t0,t0,0x1f
    add ra, ra, t0
ffffffe00020007c:	005080b3          	add	ra,ra,t0
    add sp, sp, t0
ffffffe000200080:	00510133          	add	sp,sp,t0

    # la t0, _trap_vm
    # csrw stvec, t0

    # set satp with early_pgtbl
    li t1, 1
ffffffe000200084:	00100313          	li	t1,1
    slli t1, t1, 63
ffffffe000200088:	03f31313          	slli	t1,t1,0x3f
    la t2, early_pgtbl
ffffffe00020008c:	00006397          	auipc	t2,0x6
ffffffe000200090:	f7438393          	addi	t2,t2,-140 # ffffffe000206000 <early_pgtbl>
    srli t2, t2, 12
ffffffe000200094:	00c3d393          	srli	t2,t2,0xc
    or t1, t1, t2
ffffffe000200098:	00736333          	or	t1,t1,t2
    csrw satp, t1
ffffffe00020009c:	18031073          	csrw	satp,t1

    # flush tlb
    sfence.vma zero, zero
ffffffe0002000a0:	12000073          	sfence.vma

    # flush icache
    fence.i
ffffffe0002000a4:	0000100f          	fence.i

    ret
ffffffe0002000a8:	00008067          	ret

ffffffe0002000ac <__switch_to>:
    .globl __switch_to

__switch_to:
    # save state to prev process
    # YOUR CODE HERE
    sd ra, 40(a0)
ffffffe0002000ac:	02153423          	sd	ra,40(a0)
    sd sp, 48(a0)
ffffffe0002000b0:	02253823          	sd	sp,48(a0)
    sd s0, 56(a0)
ffffffe0002000b4:	02853c23          	sd	s0,56(a0)
    sd s1, 64(a0)
ffffffe0002000b8:	04953023          	sd	s1,64(a0)
    sd s2, 72(a0)
ffffffe0002000bc:	05253423          	sd	s2,72(a0)
    sd s3, 80(a0)
ffffffe0002000c0:	05353823          	sd	s3,80(a0)
    sd s4, 88(a0)
ffffffe0002000c4:	05453c23          	sd	s4,88(a0)
    sd s5, 96(a0)
ffffffe0002000c8:	07553023          	sd	s5,96(a0)
    sd s6, 104(a0)
ffffffe0002000cc:	07653423          	sd	s6,104(a0)
    sd s7, 112(a0)
ffffffe0002000d0:	07753823          	sd	s7,112(a0)
    sd s8, 120(a0)
ffffffe0002000d4:	07853c23          	sd	s8,120(a0)
    sd s9, 128(a0)
ffffffe0002000d8:	09953023          	sd	s9,128(a0)
    sd s10, 136(a0)
ffffffe0002000dc:	09a53423          	sd	s10,136(a0)
    sd s11, 144(a0)
ffffffe0002000e0:	09b53823          	sd	s11,144(a0)
    # restore state from next process
    # YOUR CODE HERE
    ld ra, 40(a1)
ffffffe0002000e4:	0285b083          	ld	ra,40(a1)
    ld sp, 48(a1)
ffffffe0002000e8:	0305b103          	ld	sp,48(a1)
    ld s0, 56(a1)
ffffffe0002000ec:	0385b403          	ld	s0,56(a1)
    ld s1, 64(a1)
ffffffe0002000f0:	0405b483          	ld	s1,64(a1)
    ld s2, 72(a1)
ffffffe0002000f4:	0485b903          	ld	s2,72(a1)
    ld s3, 80(a1)
ffffffe0002000f8:	0505b983          	ld	s3,80(a1)
    ld s4, 88(a1)
ffffffe0002000fc:	0585ba03          	ld	s4,88(a1)
    ld s5, 96(a1)
ffffffe000200100:	0605ba83          	ld	s5,96(a1)
    ld s6, 104(a1)
ffffffe000200104:	0685bb03          	ld	s6,104(a1)
    ld s7, 112(a1)
ffffffe000200108:	0705bb83          	ld	s7,112(a1)
    ld s8, 120(a1)
ffffffe00020010c:	0785bc03          	ld	s8,120(a1)
    ld s9, 128(a1)
ffffffe000200110:	0805bc83          	ld	s9,128(a1)
    ld s10, 136(a1)
ffffffe000200114:	0885bd03          	ld	s10,136(a1)
    ld s11, 144(a1)
ffffffe000200118:	0905bd83          	ld	s11,144(a1)
    ret
ffffffe00020011c:	00008067          	ret

ffffffe000200120 <__dummy>:

__dummy:
    # YOUR CODE HERE
    la t0, dummy
ffffffe000200120:	00000297          	auipc	t0,0x0
ffffffe000200124:	4ac28293          	addi	t0,t0,1196 # ffffffe0002005cc <dummy>
    csrw sepc, t0
ffffffe000200128:	14129073          	csrw	sepc,t0
    sret
ffffffe00020012c:	10200073          	sret

ffffffe000200130 <_traps>:

_traps:

    # 1. save 32 registers and sepc to stack
    sd sp, -8(sp)
ffffffe000200130:	fe213c23          	sd	sp,-8(sp)

    sd ra, -16(sp)
ffffffe000200134:	fe113823          	sd	ra,-16(sp)
    sd gp, -24(sp)
ffffffe000200138:	fe313423          	sd	gp,-24(sp)
    sd tp, -32(sp)
ffffffe00020013c:	fe413023          	sd	tp,-32(sp)
    sd t0, -40(sp)
ffffffe000200140:	fc513c23          	sd	t0,-40(sp)
    sd t1, -48(sp)
ffffffe000200144:	fc613823          	sd	t1,-48(sp)
    sd t2, -56(sp)
ffffffe000200148:	fc713423          	sd	t2,-56(sp)
    sd t3, -64(sp)
ffffffe00020014c:	fdc13023          	sd	t3,-64(sp)
    sd t4, -72(sp)
ffffffe000200150:	fbd13c23          	sd	t4,-72(sp)
    sd t5, -80(sp)
ffffffe000200154:	fbe13823          	sd	t5,-80(sp)
    sd t6, -88(sp)
ffffffe000200158:	fbf13423          	sd	t6,-88(sp)
    sd fp, -96(sp)
ffffffe00020015c:	fa813023          	sd	s0,-96(sp)
    sd s1, -104(sp)
ffffffe000200160:	f8913c23          	sd	s1,-104(sp)
    sd a0, -112(sp)
ffffffe000200164:	f8a13823          	sd	a0,-112(sp)
    sd a1, -120(sp)
ffffffe000200168:	f8b13423          	sd	a1,-120(sp)
    sd a2, -128(sp)
ffffffe00020016c:	f8c13023          	sd	a2,-128(sp)
    sd a3, -136(sp)
ffffffe000200170:	f6d13c23          	sd	a3,-136(sp)
    sd a4, -144(sp)
ffffffe000200174:	f6e13823          	sd	a4,-144(sp)
    sd a5, -152(sp)
ffffffe000200178:	f6f13423          	sd	a5,-152(sp)
    sd a6, -160(sp)
ffffffe00020017c:	f7013023          	sd	a6,-160(sp)
    sd a7, -168(sp)
ffffffe000200180:	f5113c23          	sd	a7,-168(sp)
    sd s2, -176(sp)
ffffffe000200184:	f5213823          	sd	s2,-176(sp)
    sd s3, -184(sp)
ffffffe000200188:	f5313423          	sd	s3,-184(sp)
    sd s4, -192(sp)
ffffffe00020018c:	f5413023          	sd	s4,-192(sp)
    sd s5, -200(sp)
ffffffe000200190:	f3513c23          	sd	s5,-200(sp)
    sd s6, -208(sp)
ffffffe000200194:	f3613823          	sd	s6,-208(sp)
    sd s7, -216(sp)
ffffffe000200198:	f3713423          	sd	s7,-216(sp)
    sd s8, -224(sp)
ffffffe00020019c:	f3813023          	sd	s8,-224(sp)
    sd s9, -232(sp)
ffffffe0002001a0:	f1913c23          	sd	s9,-232(sp)
    sd s10, -240(sp)
ffffffe0002001a4:	f1a13823          	sd	s10,-240(sp)
    sd s11, -248(sp)
ffffffe0002001a8:	f1b13423          	sd	s11,-248(sp)

    csrr a0, sepc
ffffffe0002001ac:	14102573          	csrr	a0,sepc
    sd a0, -256(sp)
ffffffe0002001b0:	f0a13023          	sd	a0,-256(sp)
    addi sp, sp, -256
ffffffe0002001b4:	f0010113          	addi	sp,sp,-256
    # -----------
    # 2. call trap_handler
    csrr a0, scause
ffffffe0002001b8:	14202573          	csrr	a0,scause
    csrr a1, sepc
ffffffe0002001bc:	141025f3          	csrr	a1,sepc
    call trap_handler
ffffffe0002001c0:	165000ef          	jal	ra,ffffffe000200b24 <trap_handler>
    # -----------
    # 3. restore sepc and 32 registers (x2(sp) should be restore last) from stack
    ld a0, 0(sp)    #===
ffffffe0002001c4:	00013503          	ld	a0,0(sp)
    
    li t1, 0x8000000000000005
ffffffe0002001c8:	fff0031b          	addiw	t1,zero,-1
ffffffe0002001cc:	03f31313          	slli	t1,t1,0x3f
ffffffe0002001d0:	00530313          	addi	t1,t1,5
    csrr t0, scause
ffffffe0002001d4:	142022f3          	csrr	t0,scause
    beq t0, t1, _csrwrite
ffffffe0002001d8:	00628463          	beq	t0,t1,ffffffe0002001e0 <_csrwrite>
    addi a0, a0, 4
ffffffe0002001dc:	00450513          	addi	a0,a0,4

ffffffe0002001e0 <_csrwrite>:
_csrwrite:
    csrw sepc, a0   #===
ffffffe0002001e0:	14151073          	csrw	sepc,a0

    ld s11, 8(sp)
ffffffe0002001e4:	00813d83          	ld	s11,8(sp)
    ld s10, 16(sp)
ffffffe0002001e8:	01013d03          	ld	s10,16(sp)
    ld s9, 24(sp)
ffffffe0002001ec:	01813c83          	ld	s9,24(sp)
    ld s8, 32(sp)
ffffffe0002001f0:	02013c03          	ld	s8,32(sp)
    ld s7, 40(sp)
ffffffe0002001f4:	02813b83          	ld	s7,40(sp)
    ld s6, 48(sp)
ffffffe0002001f8:	03013b03          	ld	s6,48(sp)
    ld s5, 56(sp)
ffffffe0002001fc:	03813a83          	ld	s5,56(sp)
    ld s4, 64(sp)
ffffffe000200200:	04013a03          	ld	s4,64(sp)
    ld s3, 72(sp)
ffffffe000200204:	04813983          	ld	s3,72(sp)
    ld s2, 80(sp)
ffffffe000200208:	05013903          	ld	s2,80(sp)
    ld a7, 88(sp)
ffffffe00020020c:	05813883          	ld	a7,88(sp)
    ld a6, 96(sp)
ffffffe000200210:	06013803          	ld	a6,96(sp)
    ld a5, 104(sp)
ffffffe000200214:	06813783          	ld	a5,104(sp)
    ld a4, 112(sp)
ffffffe000200218:	07013703          	ld	a4,112(sp)
    ld a3, 120(sp)
ffffffe00020021c:	07813683          	ld	a3,120(sp)
    ld a2, 128(sp)
ffffffe000200220:	08013603          	ld	a2,128(sp)
    ld a1, 136(sp)
ffffffe000200224:	08813583          	ld	a1,136(sp)
    ld a0, 144(sp)
ffffffe000200228:	09013503          	ld	a0,144(sp)
    ld s1, 152(sp)
ffffffe00020022c:	09813483          	ld	s1,152(sp)
    ld fp, 160(sp)
ffffffe000200230:	0a013403          	ld	s0,160(sp)
    ld t6, 168(sp)
ffffffe000200234:	0a813f83          	ld	t6,168(sp)
    ld t5, 176(sp)
ffffffe000200238:	0b013f03          	ld	t5,176(sp)
    ld t4, 184(sp)
ffffffe00020023c:	0b813e83          	ld	t4,184(sp)
    ld t3, 192(sp)
ffffffe000200240:	0c013e03          	ld	t3,192(sp)
    ld t2, 200(sp)
ffffffe000200244:	0c813383          	ld	t2,200(sp)
    ld t1, 208(sp)
ffffffe000200248:	0d013303          	ld	t1,208(sp)
    ld t0, 216(sp)
ffffffe00020024c:	0d813283          	ld	t0,216(sp)
    ld tp, 224(sp)
ffffffe000200250:	0e013203          	ld	tp,224(sp)
    ld gp, 232(sp)
ffffffe000200254:	0e813183          	ld	gp,232(sp)
    ld ra, 240(sp)
ffffffe000200258:	0f013083          	ld	ra,240(sp)
    ld sp, 248(sp)
ffffffe00020025c:	0f813103          	ld	sp,248(sp)
    # -----------
    # 4. return from trap
    sret
ffffffe000200260:	10200073          	sret

ffffffe000200264 <get_cycles>:
#include"sbi.h"


unsigned long TIMECLOCK = 10000000;

unsigned long get_cycles() {
ffffffe000200264:	fe010113          	addi	sp,sp,-32
ffffffe000200268:	00813c23          	sd	s0,24(sp)
ffffffe00020026c:	02010413          	addi	s0,sp,32
    unsigned long timer;
    __asm__ volatile(
ffffffe000200270:	c01027f3          	rdtime	a5
ffffffe000200274:	fef43423          	sd	a5,-24(s0)
        "rdtime %[timer]\n"
        :[timer]"=r"(timer)
        :
        :"memory"
    );
    return timer;
ffffffe000200278:	fe843783          	ld	a5,-24(s0)
}
ffffffe00020027c:	00078513          	mv	a0,a5
ffffffe000200280:	01813403          	ld	s0,24(sp)
ffffffe000200284:	02010113          	addi	sp,sp,32
ffffffe000200288:	00008067          	ret

ffffffe00020028c <clock_set_next_event>:

void clock_set_next_event() {
ffffffe00020028c:	fe010113          	addi	sp,sp,-32
ffffffe000200290:	00113c23          	sd	ra,24(sp)
ffffffe000200294:	00813823          	sd	s0,16(sp)
ffffffe000200298:	02010413          	addi	s0,sp,32
    // sbi_set_timer(TIMECLOCK);
    
    // 下一次 时钟中断 的时间点
    unsigned long next = get_cycles() + TIMECLOCK;
ffffffe00020029c:	fc9ff0ef          	jal	ra,ffffffe000200264 <get_cycles>
ffffffe0002002a0:	00050713          	mv	a4,a0
ffffffe0002002a4:	00003797          	auipc	a5,0x3
ffffffe0002002a8:	d5c78793          	addi	a5,a5,-676 # ffffffe000203000 <TIMECLOCK>
ffffffe0002002ac:	0007b783          	ld	a5,0(a5)
ffffffe0002002b0:	00f707b3          	add	a5,a4,a5
ffffffe0002002b4:	fef43423          	sd	a5,-24(s0)
    // 使用 sbi_ecall 来完成对下一次时钟中断的设置
    sbi_ecall(0x00, 0, next, 0, 0, 0, 0, 0);
ffffffe0002002b8:	00000893          	li	a7,0
ffffffe0002002bc:	00000813          	li	a6,0
ffffffe0002002c0:	00000793          	li	a5,0
ffffffe0002002c4:	00000713          	li	a4,0
ffffffe0002002c8:	00000693          	li	a3,0
ffffffe0002002cc:	fe843603          	ld	a2,-24(s0)
ffffffe0002002d0:	00000593          	li	a1,0
ffffffe0002002d4:	00000513          	li	a0,0
ffffffe0002002d8:	75c000ef          	jal	ra,ffffffe000200a34 <sbi_ecall>
} 
ffffffe0002002dc:	00000013          	nop
ffffffe0002002e0:	01813083          	ld	ra,24(sp)
ffffffe0002002e4:	01013403          	ld	s0,16(sp)
ffffffe0002002e8:	02010113          	addi	sp,sp,32
ffffffe0002002ec:	00008067          	ret

ffffffe0002002f0 <kalloc>:

struct {
    struct run *freelist;
} kmem;

uint64 kalloc() {
ffffffe0002002f0:	fe010113          	addi	sp,sp,-32
ffffffe0002002f4:	00813c23          	sd	s0,24(sp)
ffffffe0002002f8:	02010413          	addi	s0,sp,32
    struct run *r;

    r = kmem.freelist;
ffffffe0002002fc:	00004797          	auipc	a5,0x4
ffffffe000200300:	d0478793          	addi	a5,a5,-764 # ffffffe000204000 <kmem>
ffffffe000200304:	0007b783          	ld	a5,0(a5)
ffffffe000200308:	fef43423          	sd	a5,-24(s0)
    kmem.freelist = r->next;
ffffffe00020030c:	fe843783          	ld	a5,-24(s0)
ffffffe000200310:	0007b703          	ld	a4,0(a5)
ffffffe000200314:	00004797          	auipc	a5,0x4
ffffffe000200318:	cec78793          	addi	a5,a5,-788 # ffffffe000204000 <kmem>
ffffffe00020031c:	00e7b023          	sd	a4,0(a5)
    
    // memset((void *)r, 0x0, PGSIZE);
    return (uint64) r;
ffffffe000200320:	fe843783          	ld	a5,-24(s0)
}
ffffffe000200324:	00078513          	mv	a0,a5
ffffffe000200328:	01813403          	ld	s0,24(sp)
ffffffe00020032c:	02010113          	addi	sp,sp,32
ffffffe000200330:	00008067          	ret

ffffffe000200334 <kfree>:

void kfree(uint64 addr) {
ffffffe000200334:	fd010113          	addi	sp,sp,-48
ffffffe000200338:	02813423          	sd	s0,40(sp)
ffffffe00020033c:	03010413          	addi	s0,sp,48
ffffffe000200340:	fca43c23          	sd	a0,-40(s0)
    struct run *r;

    // PGSIZE align 
    addr = addr & ~(PGSIZE - 1);
ffffffe000200344:	fd843703          	ld	a4,-40(s0)
ffffffe000200348:	fffff7b7          	lui	a5,0xfffff
ffffffe00020034c:	00f777b3          	and	a5,a4,a5
ffffffe000200350:	fcf43c23          	sd	a5,-40(s0)

    // memset((void *)addr, 0x0, (uint64)PGSIZE);

    r = (struct run *)addr;
ffffffe000200354:	fd843783          	ld	a5,-40(s0)
ffffffe000200358:	fef43423          	sd	a5,-24(s0)
    r->next = kmem.freelist;
ffffffe00020035c:	00004797          	auipc	a5,0x4
ffffffe000200360:	ca478793          	addi	a5,a5,-860 # ffffffe000204000 <kmem>
ffffffe000200364:	0007b703          	ld	a4,0(a5)
ffffffe000200368:	fe843783          	ld	a5,-24(s0)
ffffffe00020036c:	00e7b023          	sd	a4,0(a5)
    kmem.freelist = r;
ffffffe000200370:	00004797          	auipc	a5,0x4
ffffffe000200374:	c9078793          	addi	a5,a5,-880 # ffffffe000204000 <kmem>
ffffffe000200378:	fe843703          	ld	a4,-24(s0)
ffffffe00020037c:	00e7b023          	sd	a4,0(a5)

    return ;
ffffffe000200380:	00000013          	nop
}
ffffffe000200384:	02813403          	ld	s0,40(sp)
ffffffe000200388:	03010113          	addi	sp,sp,48
ffffffe00020038c:	00008067          	ret

ffffffe000200390 <kfreerange>:

void kfreerange(char *start, char *end) {
ffffffe000200390:	fd010113          	addi	sp,sp,-48
ffffffe000200394:	02113423          	sd	ra,40(sp)
ffffffe000200398:	02813023          	sd	s0,32(sp)
ffffffe00020039c:	03010413          	addi	s0,sp,48
ffffffe0002003a0:	fca43c23          	sd	a0,-40(s0)
ffffffe0002003a4:	fcb43823          	sd	a1,-48(s0)
    char *addr = (char *)PGROUNDUP((uint64)start);
ffffffe0002003a8:	fd843703          	ld	a4,-40(s0)
ffffffe0002003ac:	000017b7          	lui	a5,0x1
ffffffe0002003b0:	fff78793          	addi	a5,a5,-1 # fff <_skernel-0xffffffe0001ff001>
ffffffe0002003b4:	00f70733          	add	a4,a4,a5
ffffffe0002003b8:	fffff7b7          	lui	a5,0xfffff
ffffffe0002003bc:	00f777b3          	and	a5,a4,a5
ffffffe0002003c0:	fef43423          	sd	a5,-24(s0)
    for (; (uint64)(addr) + PGSIZE <= (uint64)end; addr += PGSIZE) {
ffffffe0002003c4:	0200006f          	j	ffffffe0002003e4 <kfreerange+0x54>
        kfree((uint64)addr);
ffffffe0002003c8:	fe843783          	ld	a5,-24(s0)
ffffffe0002003cc:	00078513          	mv	a0,a5
ffffffe0002003d0:	f65ff0ef          	jal	ra,ffffffe000200334 <kfree>
    for (; (uint64)(addr) + PGSIZE <= (uint64)end; addr += PGSIZE) {
ffffffe0002003d4:	fe843703          	ld	a4,-24(s0)
ffffffe0002003d8:	000017b7          	lui	a5,0x1
ffffffe0002003dc:	00f707b3          	add	a5,a4,a5
ffffffe0002003e0:	fef43423          	sd	a5,-24(s0)
ffffffe0002003e4:	fe843703          	ld	a4,-24(s0)
ffffffe0002003e8:	000017b7          	lui	a5,0x1
ffffffe0002003ec:	00f70733          	add	a4,a4,a5
ffffffe0002003f0:	fd043783          	ld	a5,-48(s0)
ffffffe0002003f4:	fce7fae3          	bgeu	a5,a4,ffffffe0002003c8 <kfreerange+0x38>
    }
}
ffffffe0002003f8:	00000013          	nop
ffffffe0002003fc:	00000013          	nop
ffffffe000200400:	02813083          	ld	ra,40(sp)
ffffffe000200404:	02013403          	ld	s0,32(sp)
ffffffe000200408:	03010113          	addi	sp,sp,48
ffffffe00020040c:	00008067          	ret

ffffffe000200410 <mm_init>:

void mm_init(void) {
ffffffe000200410:	ff010113          	addi	sp,sp,-16
ffffffe000200414:	00113423          	sd	ra,8(sp)
ffffffe000200418:	00813023          	sd	s0,0(sp)
ffffffe00020041c:	01010413          	addi	s0,sp,16
    // kfreerange(_end, 0x0000000080210000);
    kfreerange(_end, (char *)(PHY_END+PA2VA_OFFSET));
ffffffe000200420:	ffe007b7          	lui	a5,0xffe00
ffffffe000200424:	02178793          	addi	a5,a5,33 # ffffffffffe00021 <_ekernel+0x1fffbf7021>
ffffffe000200428:	01079593          	slli	a1,a5,0x10
ffffffe00020042c:	00005517          	auipc	a0,0x5
ffffffe000200430:	bf450513          	addi	a0,a0,-1036 # ffffffe000205020 <task>
ffffffe000200434:	f5dff0ef          	jal	ra,ffffffe000200390 <kfreerange>
    printk("...mm_init\n");
ffffffe000200438:	00002517          	auipc	a0,0x2
ffffffe00020043c:	bc850513          	addi	a0,a0,-1080 # ffffffe000202000 <_srodata>
ffffffe000200440:	438010ef          	jal	ra,ffffffe000201878 <printk>
}
ffffffe000200444:	00000013          	nop
ffffffe000200448:	00813083          	ld	ra,8(sp)
ffffffe00020044c:	00013403          	ld	s0,0(sp)
ffffffe000200450:	01010113          	addi	sp,sp,16
ffffffe000200454:	00008067          	ret

ffffffe000200458 <task_init>:

struct task_struct* idle;           // idle process
struct task_struct* current;        // 指向当前运行线程的 `task_struct`
struct task_struct* task[NR_TASKS]; // 线程数组，所有的线程都保存在此

void task_init() {
ffffffe000200458:	fe010113          	addi	sp,sp,-32
ffffffe00020045c:	00113c23          	sd	ra,24(sp)
ffffffe000200460:	00813823          	sd	s0,16(sp)
ffffffe000200464:	02010413          	addi	s0,sp,32
    // 1. 调用 kalloc() 为 idle 分配一个物理页
    // 2. 设置 state 为 TASK_RUNNING;
    // 3. 由于 idle 不参与调度 可以将其 counter / priority 设置为 0
    // 4. 设置 idle 的 pid 为 0
    // 5. 将 current 和 task[0] 指向 idle
    idle = (struct task_struct*) kalloc();
ffffffe000200468:	e89ff0ef          	jal	ra,ffffffe0002002f0 <kalloc>
ffffffe00020046c:	00050793          	mv	a5,a0
ffffffe000200470:	00078713          	mv	a4,a5
ffffffe000200474:	00004797          	auipc	a5,0x4
ffffffe000200478:	b9478793          	addi	a5,a5,-1132 # ffffffe000204008 <idle>
ffffffe00020047c:	00e7b023          	sd	a4,0(a5)
    idle->state = TASK_RUNNING;
ffffffe000200480:	00004797          	auipc	a5,0x4
ffffffe000200484:	b8878793          	addi	a5,a5,-1144 # ffffffe000204008 <idle>
ffffffe000200488:	0007b783          	ld	a5,0(a5)
ffffffe00020048c:	0007b423          	sd	zero,8(a5)
    idle->counter = 0;
ffffffe000200490:	00004797          	auipc	a5,0x4
ffffffe000200494:	b7878793          	addi	a5,a5,-1160 # ffffffe000204008 <idle>
ffffffe000200498:	0007b783          	ld	a5,0(a5)
ffffffe00020049c:	0007b823          	sd	zero,16(a5)
    idle->priority = 0;
ffffffe0002004a0:	00004797          	auipc	a5,0x4
ffffffe0002004a4:	b6878793          	addi	a5,a5,-1176 # ffffffe000204008 <idle>
ffffffe0002004a8:	0007b783          	ld	a5,0(a5)
ffffffe0002004ac:	0007bc23          	sd	zero,24(a5)
    idle->pid = 0;
ffffffe0002004b0:	00004797          	auipc	a5,0x4
ffffffe0002004b4:	b5878793          	addi	a5,a5,-1192 # ffffffe000204008 <idle>
ffffffe0002004b8:	0007b783          	ld	a5,0(a5)
ffffffe0002004bc:	0207b023          	sd	zero,32(a5)

    current = idle;
ffffffe0002004c0:	00004797          	auipc	a5,0x4
ffffffe0002004c4:	b4878793          	addi	a5,a5,-1208 # ffffffe000204008 <idle>
ffffffe0002004c8:	0007b703          	ld	a4,0(a5)
ffffffe0002004cc:	00004797          	auipc	a5,0x4
ffffffe0002004d0:	b4478793          	addi	a5,a5,-1212 # ffffffe000204010 <current>
ffffffe0002004d4:	00e7b023          	sd	a4,0(a5)
    task[0] = idle;
ffffffe0002004d8:	00004797          	auipc	a5,0x4
ffffffe0002004dc:	b3078793          	addi	a5,a5,-1232 # ffffffe000204008 <idle>
ffffffe0002004e0:	0007b703          	ld	a4,0(a5)
ffffffe0002004e4:	00005797          	auipc	a5,0x5
ffffffe0002004e8:	b3c78793          	addi	a5,a5,-1220 # ffffffe000205020 <task>
ffffffe0002004ec:	00e7b023          	sd	a4,0(a5)
    // 1. 参考 idle 的设置, 为 task[1] ~ task[NR_TASKS - 1] 进行初始化
    // 2. 其中每个线程的 state 为 TASK_RUNNING, counter 为 0, priority 使用 rand() 来设置, pid 为该线程在线程数组中的下标。
    // 3. 为 task[1] ~ task[NR_TASKS - 1] 设置 `thread_struct` 中的 `ra` 和 `sp`, 
    // 4. 其中 `ra` 设置为 __dummy （见 4.3.2）的地址， `sp` 设置为 该线程申请的物理页的高地址
    
    for(int i = 1;i < NR_TASKS; i++){
ffffffe0002004f0:	00100793          	li	a5,1
ffffffe0002004f4:	fef42623          	sw	a5,-20(s0)
ffffffe0002004f8:	0a40006f          	j	ffffffe00020059c <task_init+0x144>
        struct task_struct * temp = (struct task_struct *)kalloc();
ffffffe0002004fc:	df5ff0ef          	jal	ra,ffffffe0002002f0 <kalloc>
ffffffe000200500:	00050793          	mv	a5,a0
ffffffe000200504:	fef43023          	sd	a5,-32(s0)
        temp->state = TASK_RUNNING;
ffffffe000200508:	fe043783          	ld	a5,-32(s0)
ffffffe00020050c:	0007b423          	sd	zero,8(a5)
        temp->counter = 0;
ffffffe000200510:	fe043783          	ld	a5,-32(s0)
ffffffe000200514:	0007b823          	sd	zero,16(a5)
        temp->priority = (uint64)int_mod(i+4,(PRIORITY_MAX-PRIORITY_MIN+1))+PRIORITY_MIN;
ffffffe000200518:	fec42783          	lw	a5,-20(s0)
ffffffe00020051c:	0047879b          	addiw	a5,a5,4
ffffffe000200520:	0007879b          	sext.w	a5,a5
ffffffe000200524:	0007879b          	sext.w	a5,a5
ffffffe000200528:	00500593          	li	a1,5
ffffffe00020052c:	00078513          	mv	a0,a5
ffffffe000200530:	3d5000ef          	jal	ra,ffffffe000201104 <int_mod>
ffffffe000200534:	00050793          	mv	a5,a0
ffffffe000200538:	00178713          	addi	a4,a5,1
ffffffe00020053c:	fe043783          	ld	a5,-32(s0)
ffffffe000200540:	00e7bc23          	sd	a4,24(a5)
        // temp->priority = (uint64)(i + 2) % (PRIORITY_MAX - PRIORITY_MIN + 1) + PRIORITY_MIN;
        temp->pid = i;
ffffffe000200544:	fec42703          	lw	a4,-20(s0)
ffffffe000200548:	fe043783          	ld	a5,-32(s0)
ffffffe00020054c:	02e7b023          	sd	a4,32(a5)
        (temp->thread).ra = (uint64)__dummy;
ffffffe000200550:	00000717          	auipc	a4,0x0
ffffffe000200554:	bd070713          	addi	a4,a4,-1072 # ffffffe000200120 <__dummy>
ffffffe000200558:	fe043783          	ld	a5,-32(s0)
ffffffe00020055c:	02e7b423          	sd	a4,40(a5)
        (temp->thread).sp = (uint64)temp + PGSIZE;
ffffffe000200560:	fe043703          	ld	a4,-32(s0)
ffffffe000200564:	000017b7          	lui	a5,0x1
ffffffe000200568:	00f70733          	add	a4,a4,a5
ffffffe00020056c:	fe043783          	ld	a5,-32(s0)
ffffffe000200570:	02e7b823          	sd	a4,48(a5) # 1030 <_skernel-0xffffffe0001fefd0>
        task[i] = temp;
ffffffe000200574:	00005717          	auipc	a4,0x5
ffffffe000200578:	aac70713          	addi	a4,a4,-1364 # ffffffe000205020 <task>
ffffffe00020057c:	fec42783          	lw	a5,-20(s0)
ffffffe000200580:	00379793          	slli	a5,a5,0x3
ffffffe000200584:	00f707b3          	add	a5,a4,a5
ffffffe000200588:	fe043703          	ld	a4,-32(s0)
ffffffe00020058c:	00e7b023          	sd	a4,0(a5)
    for(int i = 1;i < NR_TASKS; i++){
ffffffe000200590:	fec42783          	lw	a5,-20(s0)
ffffffe000200594:	0017879b          	addiw	a5,a5,1
ffffffe000200598:	fef42623          	sw	a5,-20(s0)
ffffffe00020059c:	fec42783          	lw	a5,-20(s0)
ffffffe0002005a0:	0007871b          	sext.w	a4,a5
ffffffe0002005a4:	00300793          	li	a5,3
ffffffe0002005a8:	f4e7dae3          	bge	a5,a4,ffffffe0002004fc <task_init+0xa4>
    }
    printk("...proc_init\n");
ffffffe0002005ac:	00002517          	auipc	a0,0x2
ffffffe0002005b0:	a6450513          	addi	a0,a0,-1436 # ffffffe000202010 <_srodata+0x10>
ffffffe0002005b4:	2c4010ef          	jal	ra,ffffffe000201878 <printk>
}
ffffffe0002005b8:	00000013          	nop
ffffffe0002005bc:	01813083          	ld	ra,24(sp)
ffffffe0002005c0:	01013403          	ld	s0,16(sp)
ffffffe0002005c4:	02010113          	addi	sp,sp,32
ffffffe0002005c8:	00008067          	ret

ffffffe0002005cc <dummy>:

void dummy(){
ffffffe0002005cc:	fd010113          	addi	sp,sp,-48
ffffffe0002005d0:	02113423          	sd	ra,40(sp)
ffffffe0002005d4:	02813023          	sd	s0,32(sp)
ffffffe0002005d8:	03010413          	addi	s0,sp,48
    uint64 MOD = 1000000007;
ffffffe0002005dc:	3b9ad7b7          	lui	a5,0x3b9ad
ffffffe0002005e0:	a0778793          	addi	a5,a5,-1529 # 3b9aca07 <_skernel-0xffffffdfc48535f9>
ffffffe0002005e4:	fcf43c23          	sd	a5,-40(s0)
    uint64 auto_inc_local_var = 0;
ffffffe0002005e8:	fe043423          	sd	zero,-24(s0)
    int last_counter = -1; // 记录上一个counter
ffffffe0002005ec:	fff00793          	li	a5,-1
ffffffe0002005f0:	fef42223          	sw	a5,-28(s0)
    int last_last_counter = -1; // 记录上上个counter
ffffffe0002005f4:	fff00793          	li	a5,-1
ffffffe0002005f8:	fef42023          	sw	a5,-32(s0)
    while(1) {
        if (last_counter == -1 || current->counter != last_counter) {
ffffffe0002005fc:	fe442783          	lw	a5,-28(s0)
ffffffe000200600:	0007871b          	sext.w	a4,a5
ffffffe000200604:	fff00793          	li	a5,-1
ffffffe000200608:	00f70e63          	beq	a4,a5,ffffffe000200624 <dummy+0x58>
ffffffe00020060c:	00004797          	auipc	a5,0x4
ffffffe000200610:	a0478793          	addi	a5,a5,-1532 # ffffffe000204010 <current>
ffffffe000200614:	0007b783          	ld	a5,0(a5)
ffffffe000200618:	0107b703          	ld	a4,16(a5)
ffffffe00020061c:	fe442783          	lw	a5,-28(s0)
ffffffe000200620:	08f70863          	beq	a4,a5,ffffffe0002006b0 <dummy+0xe4>
            last_last_counter = last_counter;
ffffffe000200624:	fe442783          	lw	a5,-28(s0)
ffffffe000200628:	fef42023          	sw	a5,-32(s0)
            last_counter = current->counter;
ffffffe00020062c:	00004797          	auipc	a5,0x4
ffffffe000200630:	9e478793          	addi	a5,a5,-1564 # ffffffe000204010 <current>
ffffffe000200634:	0007b783          	ld	a5,0(a5)
ffffffe000200638:	0107b783          	ld	a5,16(a5)
ffffffe00020063c:	fef42223          	sw	a5,-28(s0)
            auto_inc_local_var = int_mod((auto_inc_local_var + 1) , MOD);
ffffffe000200640:	fe843783          	ld	a5,-24(s0)
ffffffe000200644:	0007879b          	sext.w	a5,a5
ffffffe000200648:	0017879b          	addiw	a5,a5,1
ffffffe00020064c:	0007879b          	sext.w	a5,a5
ffffffe000200650:	fd843703          	ld	a4,-40(s0)
ffffffe000200654:	0007071b          	sext.w	a4,a4
ffffffe000200658:	00070593          	mv	a1,a4
ffffffe00020065c:	00078513          	mv	a0,a5
ffffffe000200660:	2a5000ef          	jal	ra,ffffffe000201104 <int_mod>
ffffffe000200664:	00050793          	mv	a5,a0
ffffffe000200668:	fef43423          	sd	a5,-24(s0)
            // auto_inc_local_var = (auto_inc_local_var + 1) % MOD;
            printk("[PID = %d] is running. auto_inc_local_var = %d.", current->pid, auto_inc_local_var); 
ffffffe00020066c:	00004797          	auipc	a5,0x4
ffffffe000200670:	9a478793          	addi	a5,a5,-1628 # ffffffe000204010 <current>
ffffffe000200674:	0007b783          	ld	a5,0(a5)
ffffffe000200678:	0207b783          	ld	a5,32(a5)
ffffffe00020067c:	fe843603          	ld	a2,-24(s0)
ffffffe000200680:	00078593          	mv	a1,a5
ffffffe000200684:	00002517          	auipc	a0,0x2
ffffffe000200688:	99c50513          	addi	a0,a0,-1636 # ffffffe000202020 <_srodata+0x20>
ffffffe00020068c:	1ec010ef          	jal	ra,ffffffe000201878 <printk>
            printk("Thread space begin at %lx\n", current);
ffffffe000200690:	00004797          	auipc	a5,0x4
ffffffe000200694:	98078793          	addi	a5,a5,-1664 # ffffffe000204010 <current>
ffffffe000200698:	0007b783          	ld	a5,0(a5)
ffffffe00020069c:	00078593          	mv	a1,a5
ffffffe0002006a0:	00002517          	auipc	a0,0x2
ffffffe0002006a4:	9b050513          	addi	a0,a0,-1616 # ffffffe000202050 <_srodata+0x50>
ffffffe0002006a8:	1d0010ef          	jal	ra,ffffffe000201878 <printk>
        if (last_counter == -1 || current->counter != last_counter) {
ffffffe0002006ac:	0440006f          	j	ffffffe0002006f0 <dummy+0x124>
        } else if((last_last_counter == 0 || last_last_counter == -1) && last_counter == 1) { // counter恒为1的情况
ffffffe0002006b0:	fe042783          	lw	a5,-32(s0)
ffffffe0002006b4:	0007879b          	sext.w	a5,a5
ffffffe0002006b8:	00078a63          	beqz	a5,ffffffe0002006cc <dummy+0x100>
ffffffe0002006bc:	fe042783          	lw	a5,-32(s0)
ffffffe0002006c0:	0007871b          	sext.w	a4,a5
ffffffe0002006c4:	fff00793          	li	a5,-1
ffffffe0002006c8:	f2f71ae3          	bne	a4,a5,ffffffe0002005fc <dummy+0x30>
ffffffe0002006cc:	fe442783          	lw	a5,-28(s0)
ffffffe0002006d0:	0007871b          	sext.w	a4,a5
ffffffe0002006d4:	00100793          	li	a5,1
ffffffe0002006d8:	f2f712e3          	bne	a4,a5,ffffffe0002005fc <dummy+0x30>
            // 这里比较 tricky，不要求理解。
            last_counter = 0; 
ffffffe0002006dc:	fe042223          	sw	zero,-28(s0)
            current->counter = 0;
ffffffe0002006e0:	00004797          	auipc	a5,0x4
ffffffe0002006e4:	93078793          	addi	a5,a5,-1744 # ffffffe000204010 <current>
ffffffe0002006e8:	0007b783          	ld	a5,0(a5)
ffffffe0002006ec:	0007b823          	sd	zero,16(a5)
        if (last_counter == -1 || current->counter != last_counter) {
ffffffe0002006f0:	f0dff06f          	j	ffffffe0002005fc <dummy+0x30>

ffffffe0002006f4 <switch_to>:
        }
    }
}

void switch_to(struct task_struct* next) {
ffffffe0002006f4:	fd010113          	addi	sp,sp,-48
ffffffe0002006f8:	02113423          	sd	ra,40(sp)
ffffffe0002006fc:	02813023          	sd	s0,32(sp)
ffffffe000200700:	03010413          	addi	s0,sp,48
ffffffe000200704:	fca43c23          	sd	a0,-40(s0)
    if (next->pid != current->pid) 
ffffffe000200708:	fd843783          	ld	a5,-40(s0)
ffffffe00020070c:	0207b703          	ld	a4,32(a5)
ffffffe000200710:	00004797          	auipc	a5,0x4
ffffffe000200714:	90078793          	addi	a5,a5,-1792 # ffffffe000204010 <current>
ffffffe000200718:	0007b783          	ld	a5,0(a5)
ffffffe00020071c:	0207b783          	ld	a5,32(a5)
ffffffe000200720:	04f70e63          	beq	a4,a5,ffffffe00020077c <switch_to+0x88>
    {
        printk("\nswitch to [PID = %d PRIORITY = %d COUNTER = %d]\n", next->pid, next->priority, next->counter);
ffffffe000200724:	fd843783          	ld	a5,-40(s0)
ffffffe000200728:	0207b703          	ld	a4,32(a5)
ffffffe00020072c:	fd843783          	ld	a5,-40(s0)
ffffffe000200730:	0187b603          	ld	a2,24(a5)
ffffffe000200734:	fd843783          	ld	a5,-40(s0)
ffffffe000200738:	0107b783          	ld	a5,16(a5)
ffffffe00020073c:	00078693          	mv	a3,a5
ffffffe000200740:	00070593          	mv	a1,a4
ffffffe000200744:	00002517          	auipc	a0,0x2
ffffffe000200748:	92c50513          	addi	a0,a0,-1748 # ffffffe000202070 <_srodata+0x70>
ffffffe00020074c:	12c010ef          	jal	ra,ffffffe000201878 <printk>
        struct task_struct* prev = current;
ffffffe000200750:	00004797          	auipc	a5,0x4
ffffffe000200754:	8c078793          	addi	a5,a5,-1856 # ffffffe000204010 <current>
ffffffe000200758:	0007b783          	ld	a5,0(a5)
ffffffe00020075c:	fef43423          	sd	a5,-24(s0)
        current = next; // 切换
ffffffe000200760:	00004797          	auipc	a5,0x4
ffffffe000200764:	8b078793          	addi	a5,a5,-1872 # ffffffe000204010 <current>
ffffffe000200768:	fd843703          	ld	a4,-40(s0)
ffffffe00020076c:	00e7b023          	sd	a4,0(a5)
        __switch_to(prev, next);
ffffffe000200770:	fd843583          	ld	a1,-40(s0)
ffffffe000200774:	fe843503          	ld	a0,-24(s0)
ffffffe000200778:	935ff0ef          	jal	ra,ffffffe0002000ac <__switch_to>
    }
}
ffffffe00020077c:	00000013          	nop
ffffffe000200780:	02813083          	ld	ra,40(sp)
ffffffe000200784:	02013403          	ld	s0,32(sp)
ffffffe000200788:	03010113          	addi	sp,sp,48
ffffffe00020078c:	00008067          	ret

ffffffe000200790 <do_timer>:

void do_timer(){
ffffffe000200790:	ff010113          	addi	sp,sp,-16
ffffffe000200794:	00113423          	sd	ra,8(sp)
ffffffe000200798:	00813023          	sd	s0,0(sp)
ffffffe00020079c:	01010413          	addi	s0,sp,16
    if(current == idle || current -> counter == 0) 
ffffffe0002007a0:	00004797          	auipc	a5,0x4
ffffffe0002007a4:	87078793          	addi	a5,a5,-1936 # ffffffe000204010 <current>
ffffffe0002007a8:	0007b703          	ld	a4,0(a5)
ffffffe0002007ac:	00004797          	auipc	a5,0x4
ffffffe0002007b0:	85c78793          	addi	a5,a5,-1956 # ffffffe000204008 <idle>
ffffffe0002007b4:	0007b783          	ld	a5,0(a5)
ffffffe0002007b8:	00f70c63          	beq	a4,a5,ffffffe0002007d0 <do_timer+0x40>
ffffffe0002007bc:	00004797          	auipc	a5,0x4
ffffffe0002007c0:	85478793          	addi	a5,a5,-1964 # ffffffe000204010 <current>
ffffffe0002007c4:	0007b783          	ld	a5,0(a5)
ffffffe0002007c8:	0107b783          	ld	a5,16(a5)
ffffffe0002007cc:	00079663          	bnez	a5,ffffffe0002007d8 <do_timer+0x48>
        schedule();
ffffffe0002007d0:	050000ef          	jal	ra,ffffffe000200820 <schedule>
ffffffe0002007d4:	03c0006f          	j	ffffffe000200810 <do_timer+0x80>
    else{
        current->counter--;
ffffffe0002007d8:	00004797          	auipc	a5,0x4
ffffffe0002007dc:	83878793          	addi	a5,a5,-1992 # ffffffe000204010 <current>
ffffffe0002007e0:	0007b783          	ld	a5,0(a5)
ffffffe0002007e4:	0107b703          	ld	a4,16(a5)
ffffffe0002007e8:	fff70713          	addi	a4,a4,-1
ffffffe0002007ec:	00e7b823          	sd	a4,16(a5)
        if (current->counter > 0)
ffffffe0002007f0:	00004797          	auipc	a5,0x4
ffffffe0002007f4:	82078793          	addi	a5,a5,-2016 # ffffffe000204010 <current>
ffffffe0002007f8:	0007b783          	ld	a5,0(a5)
ffffffe0002007fc:	0107b783          	ld	a5,16(a5)
ffffffe000200800:	00079663          	bnez	a5,ffffffe00020080c <do_timer+0x7c>
            return;
        else
            schedule();
ffffffe000200804:	01c000ef          	jal	ra,ffffffe000200820 <schedule>
ffffffe000200808:	0080006f          	j	ffffffe000200810 <do_timer+0x80>
            return;
ffffffe00020080c:	00000013          	nop
    }
}
ffffffe000200810:	00813083          	ld	ra,8(sp)
ffffffe000200814:	00013403          	ld	s0,0(sp)
ffffffe000200818:	01010113          	addi	sp,sp,16
ffffffe00020081c:	00008067          	ret

ffffffe000200820 <schedule>:

void schedule(void)
{
ffffffe000200820:	fd010113          	addi	sp,sp,-48
ffffffe000200824:	02113423          	sd	ra,40(sp)
ffffffe000200828:	02813023          	sd	s0,32(sp)
ffffffe00020082c:	03010413          	addi	s0,sp,48
    struct task_struct *next = idle;
ffffffe000200830:	00003797          	auipc	a5,0x3
ffffffe000200834:	7d878793          	addi	a5,a5,2008 # ffffffe000204008 <idle>
ffffffe000200838:	0007b783          	ld	a5,0(a5)
ffffffe00020083c:	fef43423          	sd	a5,-24(s0)
    uint64 min_counter = 0xFFFFFFFF;
ffffffe000200840:	fff00793          	li	a5,-1
ffffffe000200844:	0207d793          	srli	a5,a5,0x20
ffffffe000200848:	fef43023          	sd	a5,-32(s0)
    while (1)
    {
        for (int i = 1; i < NR_TASKS; i++)
ffffffe00020084c:	00100793          	li	a5,1
ffffffe000200850:	fcf42e23          	sw	a5,-36(s0)
ffffffe000200854:	0d40006f          	j	ffffffe000200928 <schedule+0x108>
        {
            if (task[i]->state == TASK_RUNNING && task[i]->counter > 0 && task[i]->counter < min_counter)
ffffffe000200858:	00004717          	auipc	a4,0x4
ffffffe00020085c:	7c870713          	addi	a4,a4,1992 # ffffffe000205020 <task>
ffffffe000200860:	fdc42783          	lw	a5,-36(s0)
ffffffe000200864:	00379793          	slli	a5,a5,0x3
ffffffe000200868:	00f707b3          	add	a5,a4,a5
ffffffe00020086c:	0007b783          	ld	a5,0(a5)
ffffffe000200870:	0087b783          	ld	a5,8(a5)
ffffffe000200874:	0a079463          	bnez	a5,ffffffe00020091c <schedule+0xfc>
ffffffe000200878:	00004717          	auipc	a4,0x4
ffffffe00020087c:	7a870713          	addi	a4,a4,1960 # ffffffe000205020 <task>
ffffffe000200880:	fdc42783          	lw	a5,-36(s0)
ffffffe000200884:	00379793          	slli	a5,a5,0x3
ffffffe000200888:	00f707b3          	add	a5,a4,a5
ffffffe00020088c:	0007b783          	ld	a5,0(a5)
ffffffe000200890:	0107b783          	ld	a5,16(a5)
ffffffe000200894:	08078463          	beqz	a5,ffffffe00020091c <schedule+0xfc>
ffffffe000200898:	00004717          	auipc	a4,0x4
ffffffe00020089c:	78870713          	addi	a4,a4,1928 # ffffffe000205020 <task>
ffffffe0002008a0:	fdc42783          	lw	a5,-36(s0)
ffffffe0002008a4:	00379793          	slli	a5,a5,0x3
ffffffe0002008a8:	00f707b3          	add	a5,a4,a5
ffffffe0002008ac:	0007b783          	ld	a5,0(a5)
ffffffe0002008b0:	0107b783          	ld	a5,16(a5)
ffffffe0002008b4:	fe043703          	ld	a4,-32(s0)
ffffffe0002008b8:	06e7f263          	bgeu	a5,a4,ffffffe00020091c <schedule+0xfc>
            {
                if (min_counter > task[i]->counter)
ffffffe0002008bc:	00004717          	auipc	a4,0x4
ffffffe0002008c0:	76470713          	addi	a4,a4,1892 # ffffffe000205020 <task>
ffffffe0002008c4:	fdc42783          	lw	a5,-36(s0)
ffffffe0002008c8:	00379793          	slli	a5,a5,0x3
ffffffe0002008cc:	00f707b3          	add	a5,a4,a5
ffffffe0002008d0:	0007b783          	ld	a5,0(a5)
ffffffe0002008d4:	0107b783          	ld	a5,16(a5)
ffffffe0002008d8:	fe043703          	ld	a4,-32(s0)
ffffffe0002008dc:	04e7f063          	bgeu	a5,a4,ffffffe00020091c <schedule+0xfc>
                {
                    min_counter = task[i]->counter;
ffffffe0002008e0:	00004717          	auipc	a4,0x4
ffffffe0002008e4:	74070713          	addi	a4,a4,1856 # ffffffe000205020 <task>
ffffffe0002008e8:	fdc42783          	lw	a5,-36(s0)
ffffffe0002008ec:	00379793          	slli	a5,a5,0x3
ffffffe0002008f0:	00f707b3          	add	a5,a4,a5
ffffffe0002008f4:	0007b783          	ld	a5,0(a5)
ffffffe0002008f8:	0107b783          	ld	a5,16(a5)
ffffffe0002008fc:	fef43023          	sd	a5,-32(s0)
                    next = task[i];
ffffffe000200900:	00004717          	auipc	a4,0x4
ffffffe000200904:	72070713          	addi	a4,a4,1824 # ffffffe000205020 <task>
ffffffe000200908:	fdc42783          	lw	a5,-36(s0)
ffffffe00020090c:	00379793          	slli	a5,a5,0x3
ffffffe000200910:	00f707b3          	add	a5,a4,a5
ffffffe000200914:	0007b783          	ld	a5,0(a5)
ffffffe000200918:	fef43423          	sd	a5,-24(s0)
        for (int i = 1; i < NR_TASKS; i++)
ffffffe00020091c:	fdc42783          	lw	a5,-36(s0)
ffffffe000200920:	0017879b          	addiw	a5,a5,1
ffffffe000200924:	fcf42e23          	sw	a5,-36(s0)
ffffffe000200928:	fdc42783          	lw	a5,-36(s0)
ffffffe00020092c:	0007871b          	sext.w	a4,a5
ffffffe000200930:	00300793          	li	a5,3
ffffffe000200934:	f2e7d2e3          	bge	a5,a4,ffffffe000200858 <schedule+0x38>
                }
            }
        }
        if (next == idle)
ffffffe000200938:	00003797          	auipc	a5,0x3
ffffffe00020093c:	6d078793          	addi	a5,a5,1744 # ffffffe000204008 <idle>
ffffffe000200940:	0007b783          	ld	a5,0(a5)
ffffffe000200944:	fe843703          	ld	a4,-24(s0)
ffffffe000200948:	0cf71663          	bne	a4,a5,ffffffe000200a14 <schedule+0x1f4>
        {
            for (int i = 1; i < NR_TASKS; i++)
ffffffe00020094c:	00100793          	li	a5,1
ffffffe000200950:	fcf42c23          	sw	a5,-40(s0)
ffffffe000200954:	0ac0006f          	j	ffffffe000200a00 <schedule+0x1e0>
            {
                task[i]->counter = task[i]->priority;
ffffffe000200958:	00004717          	auipc	a4,0x4
ffffffe00020095c:	6c870713          	addi	a4,a4,1736 # ffffffe000205020 <task>
ffffffe000200960:	fd842783          	lw	a5,-40(s0)
ffffffe000200964:	00379793          	slli	a5,a5,0x3
ffffffe000200968:	00f707b3          	add	a5,a4,a5
ffffffe00020096c:	0007b703          	ld	a4,0(a5)
ffffffe000200970:	00004697          	auipc	a3,0x4
ffffffe000200974:	6b068693          	addi	a3,a3,1712 # ffffffe000205020 <task>
ffffffe000200978:	fd842783          	lw	a5,-40(s0)
ffffffe00020097c:	00379793          	slli	a5,a5,0x3
ffffffe000200980:	00f687b3          	add	a5,a3,a5
ffffffe000200984:	0007b783          	ld	a5,0(a5)
ffffffe000200988:	01873703          	ld	a4,24(a4)
ffffffe00020098c:	00e7b823          	sd	a4,16(a5)
                printk("SET [PID = %d PRIORITY = %d COUNTER = %d]\n", task[i]->pid, task[i]->priority, task[i]->counter);
ffffffe000200990:	00004717          	auipc	a4,0x4
ffffffe000200994:	69070713          	addi	a4,a4,1680 # ffffffe000205020 <task>
ffffffe000200998:	fd842783          	lw	a5,-40(s0)
ffffffe00020099c:	00379793          	slli	a5,a5,0x3
ffffffe0002009a0:	00f707b3          	add	a5,a4,a5
ffffffe0002009a4:	0007b783          	ld	a5,0(a5)
ffffffe0002009a8:	0207b583          	ld	a1,32(a5)
ffffffe0002009ac:	00004717          	auipc	a4,0x4
ffffffe0002009b0:	67470713          	addi	a4,a4,1652 # ffffffe000205020 <task>
ffffffe0002009b4:	fd842783          	lw	a5,-40(s0)
ffffffe0002009b8:	00379793          	slli	a5,a5,0x3
ffffffe0002009bc:	00f707b3          	add	a5,a4,a5
ffffffe0002009c0:	0007b783          	ld	a5,0(a5)
ffffffe0002009c4:	0187b603          	ld	a2,24(a5)
ffffffe0002009c8:	00004717          	auipc	a4,0x4
ffffffe0002009cc:	65870713          	addi	a4,a4,1624 # ffffffe000205020 <task>
ffffffe0002009d0:	fd842783          	lw	a5,-40(s0)
ffffffe0002009d4:	00379793          	slli	a5,a5,0x3
ffffffe0002009d8:	00f707b3          	add	a5,a4,a5
ffffffe0002009dc:	0007b783          	ld	a5,0(a5)
ffffffe0002009e0:	0107b783          	ld	a5,16(a5)
ffffffe0002009e4:	00078693          	mv	a3,a5
ffffffe0002009e8:	00001517          	auipc	a0,0x1
ffffffe0002009ec:	6c050513          	addi	a0,a0,1728 # ffffffe0002020a8 <_srodata+0xa8>
ffffffe0002009f0:	689000ef          	jal	ra,ffffffe000201878 <printk>
            for (int i = 1; i < NR_TASKS; i++)
ffffffe0002009f4:	fd842783          	lw	a5,-40(s0)
ffffffe0002009f8:	0017879b          	addiw	a5,a5,1
ffffffe0002009fc:	fcf42c23          	sw	a5,-40(s0)
ffffffe000200a00:	fd842783          	lw	a5,-40(s0)
ffffffe000200a04:	0007871b          	sext.w	a4,a5
ffffffe000200a08:	00300793          	li	a5,3
ffffffe000200a0c:	f4e7d6e3          	bge	a5,a4,ffffffe000200958 <schedule+0x138>
        for (int i = 1; i < NR_TASKS; i++)
ffffffe000200a10:	e3dff06f          	j	ffffffe00020084c <schedule+0x2c>
            }
        }
        else
            break;
ffffffe000200a14:	00000013          	nop
    }
    switch_to(next);
ffffffe000200a18:	fe843503          	ld	a0,-24(s0)
ffffffe000200a1c:	cd9ff0ef          	jal	ra,ffffffe0002006f4 <switch_to>
}
ffffffe000200a20:	00000013          	nop
ffffffe000200a24:	02813083          	ld	ra,40(sp)
ffffffe000200a28:	02013403          	ld	s0,32(sp)
ffffffe000200a2c:	03010113          	addi	sp,sp,48
ffffffe000200a30:	00008067          	ret

ffffffe000200a34 <sbi_ecall>:

struct sbiret sbi_ecall(int ext, int fid, uint64 arg0,
                        uint64 arg1, uint64 arg2,
                        uint64 arg3, uint64 arg4,
                        uint64 arg5)
{
ffffffe000200a34:	f9010113          	addi	sp,sp,-112
ffffffe000200a38:	06813423          	sd	s0,104(sp)
ffffffe000200a3c:	07010413          	addi	s0,sp,112
ffffffe000200a40:	fcc43023          	sd	a2,-64(s0)
ffffffe000200a44:	fad43c23          	sd	a3,-72(s0)
ffffffe000200a48:	fae43823          	sd	a4,-80(s0)
ffffffe000200a4c:	faf43423          	sd	a5,-88(s0)
ffffffe000200a50:	fb043023          	sd	a6,-96(s0)
ffffffe000200a54:	f9143c23          	sd	a7,-104(s0)
ffffffe000200a58:	00050793          	mv	a5,a0
ffffffe000200a5c:	fcf42623          	sw	a5,-52(s0)
ffffffe000200a60:	00058793          	mv	a5,a1
ffffffe000200a64:	fcf42423          	sw	a5,-56(s0)
  // );
  // ret_str.error = err;
  // ret_str.value = value;
  // return ret_str;
  struct sbiret ret;
  register uint64 a0 asm("a0") = (uint64)(arg0);
ffffffe000200a68:	fc043503          	ld	a0,-64(s0)
  register uint64 a1 asm("a1") = (uint64)(arg1);
ffffffe000200a6c:	fb843583          	ld	a1,-72(s0)
  register uint64 a2 asm("a2") = (uint64)(arg2);
ffffffe000200a70:	fb043603          	ld	a2,-80(s0)
  register uint64 a3 asm("a3") = (uint64)(arg3);
ffffffe000200a74:	fa843683          	ld	a3,-88(s0)
  register uint64 a4 asm("a4") = (uint64)(arg4);
ffffffe000200a78:	fa043703          	ld	a4,-96(s0)
  register uint64 a5 asm("a5") = (uint64)(arg5);
ffffffe000200a7c:	f9843783          	ld	a5,-104(s0)
  register uint64 a6 asm("a6") = (uint64)(fid);
ffffffe000200a80:	fc842803          	lw	a6,-56(s0)
  register uint64 a7 asm("a7") = (uint64)(ext);
ffffffe000200a84:	fcc42883          	lw	a7,-52(s0)
  asm volatile (
ffffffe000200a88:	00000073          	ecall
      "ecall"
      : "+r" (a0), "+r" (a1)
      : "r" (a2), "r" (a3), "r" (a4), "r" (a5), "r" (a6), "r" (a7)
      : "memory"
  );
  ret.error = a0;
ffffffe000200a8c:	00050793          	mv	a5,a0
ffffffe000200a90:	fcf43823          	sd	a5,-48(s0)
  ret.value = a1;
ffffffe000200a94:	00058793          	mv	a5,a1
ffffffe000200a98:	fcf43c23          	sd	a5,-40(s0)
  return ret;
ffffffe000200a9c:	fd043783          	ld	a5,-48(s0)
ffffffe000200aa0:	fef43023          	sd	a5,-32(s0)
ffffffe000200aa4:	fd843783          	ld	a5,-40(s0)
ffffffe000200aa8:	fef43423          	sd	a5,-24(s0)
ffffffe000200aac:	fe043703          	ld	a4,-32(s0)
ffffffe000200ab0:	fe843783          	ld	a5,-24(s0)
ffffffe000200ab4:	00070313          	mv	t1,a4
ffffffe000200ab8:	00078393          	mv	t2,a5
ffffffe000200abc:	00030713          	mv	a4,t1
ffffffe000200ac0:	00038793          	mv	a5,t2
}
ffffffe000200ac4:	00070513          	mv	a0,a4
ffffffe000200ac8:	00078593          	mv	a1,a5
ffffffe000200acc:	06813403          	ld	s0,104(sp)
ffffffe000200ad0:	07010113          	addi	sp,sp,112
ffffffe000200ad4:	00008067          	ret

ffffffe000200ad8 <sbi_set_timer>:
void sbi_set_timer(uint64 time){
ffffffe000200ad8:	fe010113          	addi	sp,sp,-32
ffffffe000200adc:	00113c23          	sd	ra,24(sp)
ffffffe000200ae0:	00813823          	sd	s0,16(sp)
ffffffe000200ae4:	02010413          	addi	s0,sp,32
ffffffe000200ae8:	fea43423          	sd	a0,-24(s0)
  sbi_ecall(0,0,time,0,0,0,0,0);
ffffffe000200aec:	00000893          	li	a7,0
ffffffe000200af0:	00000813          	li	a6,0
ffffffe000200af4:	00000793          	li	a5,0
ffffffe000200af8:	00000713          	li	a4,0
ffffffe000200afc:	00000693          	li	a3,0
ffffffe000200b00:	fe843603          	ld	a2,-24(s0)
ffffffe000200b04:	00000593          	li	a1,0
ffffffe000200b08:	00000513          	li	a0,0
ffffffe000200b0c:	f29ff0ef          	jal	ra,ffffffe000200a34 <sbi_ecall>
ffffffe000200b10:	00000013          	nop
ffffffe000200b14:	01813083          	ld	ra,24(sp)
ffffffe000200b18:	01013403          	ld	s0,16(sp)
ffffffe000200b1c:	02010113          	addi	sp,sp,32
ffffffe000200b20:	00008067          	ret

ffffffe000200b24 <trap_handler>:
#include<printk.h>
#include"clock.h"
// trap.c 

void trap_handler(unsigned long scause, unsigned long sepc)
{
ffffffe000200b24:	fe010113          	addi	sp,sp,-32
ffffffe000200b28:	00113c23          	sd	ra,24(sp)
ffffffe000200b2c:	00813823          	sd	s0,16(sp)
ffffffe000200b30:	02010413          	addi	s0,sp,32
ffffffe000200b34:	fea43423          	sd	a0,-24(s0)
ffffffe000200b38:	feb43023          	sd	a1,-32(s0)
    if ((scause >> 63 == 1) && ((scause & 0x7fffffffffffffff) == 5))
ffffffe000200b3c:	fe843783          	ld	a5,-24(s0)
ffffffe000200b40:	03f7d713          	srli	a4,a5,0x3f
ffffffe000200b44:	00100793          	li	a5,1
ffffffe000200b48:	02f71463          	bne	a4,a5,ffffffe000200b70 <trap_handler+0x4c>
ffffffe000200b4c:	fe843703          	ld	a4,-24(s0)
ffffffe000200b50:	fff00793          	li	a5,-1
ffffffe000200b54:	0017d793          	srli	a5,a5,0x1
ffffffe000200b58:	00f77733          	and	a4,a4,a5
ffffffe000200b5c:	00500793          	li	a5,5
ffffffe000200b60:	00f71863          	bne	a4,a5,ffffffe000200b70 <trap_handler+0x4c>
    {
        // printk("[S] Supervisor Mode Timer Interrupt\n");
        clock_set_next_event();
ffffffe000200b64:	f28ff0ef          	jal	ra,ffffffe00020028c <clock_set_next_event>
        // sbi_ecall(0x00, 0, TIMECLOCK, 0, 0, 0, 0, 0);
        do_timer();
ffffffe000200b68:	c29ff0ef          	jal	ra,ffffffe000200790 <do_timer>
    {
ffffffe000200b6c:	0180006f          	j	ffffffe000200b84 <trap_handler+0x60>
    }
    else {
        printk("trap handler: scause = %lx, sepc = %lx\n", scause, sepc);
ffffffe000200b70:	fe043603          	ld	a2,-32(s0)
ffffffe000200b74:	fe843583          	ld	a1,-24(s0)
ffffffe000200b78:	00001517          	auipc	a0,0x1
ffffffe000200b7c:	56050513          	addi	a0,a0,1376 # ffffffe0002020d8 <_srodata+0xd8>
ffffffe000200b80:	4f9000ef          	jal	ra,ffffffe000201878 <printk>
    }
    return;
ffffffe000200b84:	00000013          	nop
ffffffe000200b88:	01813083          	ld	ra,24(sp)
ffffffe000200b8c:	01013403          	ld	s0,16(sp)
ffffffe000200b90:	02010113          	addi	sp,sp,32
ffffffe000200b94:	00008067          	ret

ffffffe000200b98 <setup_vm>:
unsigned long early_pgtbl[512] __attribute__((__aligned__(0x1000)));
/* swapper_pg_dir: kernel pagetable 根目录， 在 setup_vm_final 进行映射。 */
unsigned long  swapper_pg_dir[512] __attribute__((__aligned__(0x1000)));

void setup_vm(void)
{
ffffffe000200b98:	fe010113          	addi	sp,sp,-32
ffffffe000200b9c:	00113c23          	sd	ra,24(sp)
ffffffe000200ba0:	00813823          	sd	s0,16(sp)
ffffffe000200ba4:	02010413          	addi	s0,sp,32
        high bit 可以忽略
        中间9 bit 作为 early_pgtbl 的 index
        低 30 bit 作为 页内偏移 这里注意到 30 = 9 + 9 + 12， 即我们只使用根页表， 根页表的每个 entry 都对应 1GB 的区域。
    3. Page Table Entry 的权限 V | R | W | X 位设置为 1
    */
    memset(early_pgtbl, 0, PGSIZE);
ffffffe000200ba8:	00001637          	lui	a2,0x1
ffffffe000200bac:	00000593          	li	a1,0
ffffffe000200bb0:	00005517          	auipc	a0,0x5
ffffffe000200bb4:	45050513          	addi	a0,a0,1104 # ffffffe000206000 <early_pgtbl>
ffffffe000200bb8:	040010ef          	jal	ra,ffffffe000201bf8 <memset>
    uint64 index, entry;
    // entry[53:28] = PPN[2], entry[3:0] = XWRV
    // PA == VA
    index = ((uint64)PHY_START >> 30) & 0x01FF;
ffffffe000200bbc:	00200793          	li	a5,2
ffffffe000200bc0:	fef43423          	sd	a5,-24(s0)
    entry = ((PHY_START & 0x00FFFFFFC0000000) >> 2) | 0xCF;
ffffffe000200bc4:	200007b7          	lui	a5,0x20000
ffffffe000200bc8:	0cf78793          	addi	a5,a5,207 # 200000cf <_skernel-0xffffffdfe01fff31>
ffffffe000200bcc:	fef43023          	sd	a5,-32(s0)
    early_pgtbl[index] = entry;
ffffffe000200bd0:	00005717          	auipc	a4,0x5
ffffffe000200bd4:	43070713          	addi	a4,a4,1072 # ffffffe000206000 <early_pgtbl>
ffffffe000200bd8:	fe843783          	ld	a5,-24(s0)
ffffffe000200bdc:	00379793          	slli	a5,a5,0x3
ffffffe000200be0:	00f707b3          	add	a5,a4,a5
ffffffe000200be4:	fe043703          	ld	a4,-32(s0)
ffffffe000200be8:	00e7b023          	sd	a4,0(a5)
    // PA + PV2VA_OFFSET == VA
    index = ((uint64)VM_START >> 30) & 0x01FF;
ffffffe000200bec:	18000793          	li	a5,384
ffffffe000200bf0:	fef43423          	sd	a5,-24(s0)
    entry = ((PHY_START & 0x00FFFFFFC0000000) >> 2) | 0xCF;
ffffffe000200bf4:	200007b7          	lui	a5,0x20000
ffffffe000200bf8:	0cf78793          	addi	a5,a5,207 # 200000cf <_skernel-0xffffffdfe01fff31>
ffffffe000200bfc:	fef43023          	sd	a5,-32(s0)
    early_pgtbl[index] = entry;
ffffffe000200c00:	00005717          	auipc	a4,0x5
ffffffe000200c04:	40070713          	addi	a4,a4,1024 # ffffffe000206000 <early_pgtbl>
ffffffe000200c08:	fe843783          	ld	a5,-24(s0)
ffffffe000200c0c:	00379793          	slli	a5,a5,0x3
ffffffe000200c10:	00f707b3          	add	a5,a4,a5
ffffffe000200c14:	fe043703          	ld	a4,-32(s0)
ffffffe000200c18:	00e7b023          	sd	a4,0(a5)
    printk("...setup_vm\n");
ffffffe000200c1c:	00001517          	auipc	a0,0x1
ffffffe000200c20:	4e450513          	addi	a0,a0,1252 # ffffffe000202100 <_srodata+0x100>
ffffffe000200c24:	455000ef          	jal	ra,ffffffe000201878 <printk>
}
ffffffe000200c28:	00000013          	nop
ffffffe000200c2c:	01813083          	ld	ra,24(sp)
ffffffe000200c30:	01013403          	ld	s0,16(sp)
ffffffe000200c34:	02010113          	addi	sp,sp,32
ffffffe000200c38:	00008067          	ret

ffffffe000200c3c <setup_vm_final>:
extern char _stext[];
extern char _srodata[];
extern char _sdata[];
extern char _sbss[];

void setup_vm_final(void) {
ffffffe000200c3c:	fd010113          	addi	sp,sp,-48
ffffffe000200c40:	02113423          	sd	ra,40(sp)
ffffffe000200c44:	02813023          	sd	s0,32(sp)
ffffffe000200c48:	03010413          	addi	s0,sp,48
    memset(swapper_pg_dir, 0x0, PGSIZE);
ffffffe000200c4c:	00001637          	lui	a2,0x1
ffffffe000200c50:	00000593          	li	a1,0
ffffffe000200c54:	00006517          	auipc	a0,0x6
ffffffe000200c58:	3ac50513          	addi	a0,a0,940 # ffffffe000207000 <swapper_pg_dir>
ffffffe000200c5c:	79d000ef          	jal	ra,ffffffe000201bf8 <memset>

    // No OpenSBI mapping required
    
    // mapping kernel text X|-|R|V
    uint64 va = (uint64)&_stext;
ffffffe000200c60:	fffff797          	auipc	a5,0xfffff
ffffffe000200c64:	3a078793          	addi	a5,a5,928 # ffffffe000200000 <_skernel>
ffffffe000200c68:	fef43423          	sd	a5,-24(s0)
    uint64 pa = (uint64)(&_stext) - PA2VA_OFFSET;
ffffffe000200c6c:	fffff717          	auipc	a4,0xfffff
ffffffe000200c70:	39470713          	addi	a4,a4,916 # ffffffe000200000 <_skernel>
ffffffe000200c74:	04100793          	li	a5,65
ffffffe000200c78:	01f79793          	slli	a5,a5,0x1f
ffffffe000200c7c:	00f707b3          	add	a5,a4,a5
ffffffe000200c80:	fef43023          	sd	a5,-32(s0)
    uint64 sz = (uint64)&_srodata - (uint64)(&_stext);
ffffffe000200c84:	00001717          	auipc	a4,0x1
ffffffe000200c88:	37c70713          	addi	a4,a4,892 # ffffffe000202000 <_srodata>
ffffffe000200c8c:	fffff797          	auipc	a5,0xfffff
ffffffe000200c90:	37478793          	addi	a5,a5,884 # ffffffe000200000 <_skernel>
ffffffe000200c94:	40f707b3          	sub	a5,a4,a5
ffffffe000200c98:	fcf43c23          	sd	a5,-40(s0)
    create_mapping(swapper_pg_dir, va, pa, sz, 0xB | 0x40 | 0x80);
ffffffe000200c9c:	0cb00713          	li	a4,203
ffffffe000200ca0:	fd843683          	ld	a3,-40(s0)
ffffffe000200ca4:	fe043603          	ld	a2,-32(s0)
ffffffe000200ca8:	fe843583          	ld	a1,-24(s0)
ffffffe000200cac:	00006517          	auipc	a0,0x6
ffffffe000200cb0:	35450513          	addi	a0,a0,852 # ffffffe000207000 <swapper_pg_dir>
ffffffe000200cb4:	114000ef          	jal	ra,ffffffe000200dc8 <create_mapping>

    // mapping kernel rodata -|-|R|V
    va = (uint64)(&_srodata);
ffffffe000200cb8:	00001797          	auipc	a5,0x1
ffffffe000200cbc:	34878793          	addi	a5,a5,840 # ffffffe000202000 <_srodata>
ffffffe000200cc0:	fef43423          	sd	a5,-24(s0)
    pa = (uint64)(&_srodata) - PA2VA_OFFSET;
ffffffe000200cc4:	00001717          	auipc	a4,0x1
ffffffe000200cc8:	33c70713          	addi	a4,a4,828 # ffffffe000202000 <_srodata>
ffffffe000200ccc:	04100793          	li	a5,65
ffffffe000200cd0:	01f79793          	slli	a5,a5,0x1f
ffffffe000200cd4:	00f707b3          	add	a5,a4,a5
ffffffe000200cd8:	fef43023          	sd	a5,-32(s0)
    sz = (uint64)(&_sdata) - (uint64)(&_srodata);
ffffffe000200cdc:	00002717          	auipc	a4,0x2
ffffffe000200ce0:	32470713          	addi	a4,a4,804 # ffffffe000203000 <TIMECLOCK>
ffffffe000200ce4:	00001797          	auipc	a5,0x1
ffffffe000200ce8:	31c78793          	addi	a5,a5,796 # ffffffe000202000 <_srodata>
ffffffe000200cec:	40f707b3          	sub	a5,a4,a5
ffffffe000200cf0:	fcf43c23          	sd	a5,-40(s0)
    create_mapping(swapper_pg_dir, va, pa, sz, 0x3 | 0x40 | 0x80);
ffffffe000200cf4:	0c300713          	li	a4,195
ffffffe000200cf8:	fd843683          	ld	a3,-40(s0)
ffffffe000200cfc:	fe043603          	ld	a2,-32(s0)
ffffffe000200d00:	fe843583          	ld	a1,-24(s0)
ffffffe000200d04:	00006517          	auipc	a0,0x6
ffffffe000200d08:	2fc50513          	addi	a0,a0,764 # ffffffe000207000 <swapper_pg_dir>
ffffffe000200d0c:	0bc000ef          	jal	ra,ffffffe000200dc8 <create_mapping>
  
    // mapping other memory -|W|R|V
    va = (uint64)(&_sdata);
ffffffe000200d10:	00002797          	auipc	a5,0x2
ffffffe000200d14:	2f078793          	addi	a5,a5,752 # ffffffe000203000 <TIMECLOCK>
ffffffe000200d18:	fef43423          	sd	a5,-24(s0)
    pa = (uint64)(&_sdata) - PA2VA_OFFSET;
ffffffe000200d1c:	00002717          	auipc	a4,0x2
ffffffe000200d20:	2e470713          	addi	a4,a4,740 # ffffffe000203000 <TIMECLOCK>
ffffffe000200d24:	04100793          	li	a5,65
ffffffe000200d28:	01f79793          	slli	a5,a5,0x1f
ffffffe000200d2c:	00f707b3          	add	a5,a4,a5
ffffffe000200d30:	fef43023          	sd	a5,-32(s0)
    sz = PHY_SIZE - ((uint64)(&_sdata) - (uint64)&_stext);
ffffffe000200d34:	fffff717          	auipc	a4,0xfffff
ffffffe000200d38:	2cc70713          	addi	a4,a4,716 # ffffffe000200000 <_skernel>
ffffffe000200d3c:	002107b7          	lui	a5,0x210
ffffffe000200d40:	00f70733          	add	a4,a4,a5
ffffffe000200d44:	00002797          	auipc	a5,0x2
ffffffe000200d48:	2bc78793          	addi	a5,a5,700 # ffffffe000203000 <TIMECLOCK>
ffffffe000200d4c:	40f707b3          	sub	a5,a4,a5
ffffffe000200d50:	fcf43c23          	sd	a5,-40(s0)
    create_mapping(swapper_pg_dir, va, pa, sz, 0x7 | 0x80 | 0x40);
ffffffe000200d54:	0c700713          	li	a4,199
ffffffe000200d58:	fd843683          	ld	a3,-40(s0)
ffffffe000200d5c:	fe043603          	ld	a2,-32(s0)
ffffffe000200d60:	fe843583          	ld	a1,-24(s0)
ffffffe000200d64:	00006517          	auipc	a0,0x6
ffffffe000200d68:	29c50513          	addi	a0,a0,668 # ffffffe000207000 <swapper_pg_dir>
ffffffe000200d6c:	05c000ef          	jal	ra,ffffffe000200dc8 <create_mapping>
  
    // set satp with swapper_pg_dir

    printk("...create_mapping\n");
ffffffe000200d70:	00001517          	auipc	a0,0x1
ffffffe000200d74:	3a050513          	addi	a0,a0,928 # ffffffe000202110 <_srodata+0x110>
ffffffe000200d78:	301000ef          	jal	ra,ffffffe000201878 <printk>
    uint64 satp = (((uint64)(swapper_pg_dir) - PA2VA_OFFSET) >> 12) | (1L << 63);
ffffffe000200d7c:	00006717          	auipc	a4,0x6
ffffffe000200d80:	28470713          	addi	a4,a4,644 # ffffffe000207000 <swapper_pg_dir>
ffffffe000200d84:	04100793          	li	a5,65
ffffffe000200d88:	01f79793          	slli	a5,a5,0x1f
ffffffe000200d8c:	00f707b3          	add	a5,a4,a5
ffffffe000200d90:	00c7d713          	srli	a4,a5,0xc
ffffffe000200d94:	fff00793          	li	a5,-1
ffffffe000200d98:	03f79793          	slli	a5,a5,0x3f
ffffffe000200d9c:	00f767b3          	or	a5,a4,a5
ffffffe000200da0:	fcf43823          	sd	a5,-48(s0)
    // 一定要写成 1L，写 1 是过不了的
    __asm__ volatile("csrw satp, %[_satp]" ::[_satp] "r" (satp) :);
ffffffe000200da4:	fd043783          	ld	a5,-48(s0)
ffffffe000200da8:	18079073          	csrw	satp,a5

    // flush TLB
    asm volatile("sfence.vma zero, zero");
ffffffe000200dac:	12000073          	sfence.vma

    // flush icache
    asm volatile("fence.i");
ffffffe000200db0:	0000100f          	fence.i

    return;
ffffffe000200db4:	00000013          	nop
}
ffffffe000200db8:	02813083          	ld	ra,40(sp)
ffffffe000200dbc:	02013403          	ld	s0,32(sp)
ffffffe000200dc0:	03010113          	addi	sp,sp,48
ffffffe000200dc4:	00008067          	ret

ffffffe000200dc8 <create_mapping>:


/* 创建多级页表映射关系 */
void create_mapping(uint64 *pgtbl, uint64 va, uint64 pa, uint64 sz, uint64 perm) {
ffffffe000200dc8:	f8010113          	addi	sp,sp,-128
ffffffe000200dcc:	06113c23          	sd	ra,120(sp)
ffffffe000200dd0:	06813823          	sd	s0,112(sp)
ffffffe000200dd4:	08010413          	addi	s0,sp,128
ffffffe000200dd8:	faa43423          	sd	a0,-88(s0)
ffffffe000200ddc:	fab43023          	sd	a1,-96(s0)
ffffffe000200de0:	f8c43c23          	sd	a2,-104(s0)
ffffffe000200de4:	f8d43823          	sd	a3,-112(s0)
ffffffe000200de8:	f8e43423          	sd	a4,-120(s0)
    将给定的一段虚拟内存映射到物理内存上
    物理内存需要分页
    创建多级页表的时候可以使用 kalloc() 来获取一页作为页表目录
    可以使用 V bit 来判断页表项是否存在
    */
   uint64 end = va + sz;
ffffffe000200dec:	fa043703          	ld	a4,-96(s0)
ffffffe000200df0:	f9043783          	ld	a5,-112(s0)
ffffffe000200df4:	00f707b3          	add	a5,a4,a5
ffffffe000200df8:	fcf43c23          	sd	a5,-40(s0)
   uint64 vpn2, vpn1, vpn0;
   while (va < end)
ffffffe000200dfc:	1980006f          	j	ffffffe000200f94 <create_mapping+0x1cc>
   {
        vpn2 = (va & 0x7FC0000000) >> 30;
ffffffe000200e00:	fa043783          	ld	a5,-96(s0)
ffffffe000200e04:	01e7d793          	srli	a5,a5,0x1e
ffffffe000200e08:	1ff7f793          	andi	a5,a5,511
ffffffe000200e0c:	fcf43823          	sd	a5,-48(s0)
        vpn1 = (va & 0x3FE00000) >> 21;
ffffffe000200e10:	fa043783          	ld	a5,-96(s0)
ffffffe000200e14:	0157d793          	srli	a5,a5,0x15
ffffffe000200e18:	1ff7f793          	andi	a5,a5,511
ffffffe000200e1c:	fcf43423          	sd	a5,-56(s0)
        vpn0 = (va & 0x1FF000) >> 12;
ffffffe000200e20:	fa043783          	ld	a5,-96(s0)
ffffffe000200e24:	00c7d793          	srli	a5,a5,0xc
ffffffe000200e28:	1ff7f793          	andi	a5,a5,511
ffffffe000200e2c:	fcf43023          	sd	a5,-64(s0)

        uint64 *pgtbl_first = pgtbl;
ffffffe000200e30:	fa843783          	ld	a5,-88(s0)
ffffffe000200e34:	faf43c23          	sd	a5,-72(s0)
        uint64 *pgtbl_second;
        if(pgtbl_first[vpn2] & 0x1){
ffffffe000200e38:	fd043783          	ld	a5,-48(s0)
ffffffe000200e3c:	00379793          	slli	a5,a5,0x3
ffffffe000200e40:	fb843703          	ld	a4,-72(s0)
ffffffe000200e44:	00f707b3          	add	a5,a4,a5
ffffffe000200e48:	0007b783          	ld	a5,0(a5)
ffffffe000200e4c:	0017f793          	andi	a5,a5,1
ffffffe000200e50:	02078463          	beqz	a5,ffffffe000200e78 <create_mapping+0xb0>
            pgtbl_second = (uint64)((pgtbl[vpn2] >> 10) << 12);
ffffffe000200e54:	fd043783          	ld	a5,-48(s0)
ffffffe000200e58:	00379793          	slli	a5,a5,0x3
ffffffe000200e5c:	fa843703          	ld	a4,-88(s0)
ffffffe000200e60:	00f707b3          	add	a5,a4,a5
ffffffe000200e64:	0007b783          	ld	a5,0(a5)
ffffffe000200e68:	00a7d793          	srli	a5,a5,0xa
ffffffe000200e6c:	00c79793          	slli	a5,a5,0xc
ffffffe000200e70:	fef43423          	sd	a5,-24(s0)
ffffffe000200e74:	0400006f          	j	ffffffe000200eb4 <create_mapping+0xec>
        }else {
            pgtbl_second = (uint64)(kalloc() - PA2VA_OFFSET);
ffffffe000200e78:	c78ff0ef          	jal	ra,ffffffe0002002f0 <kalloc>
ffffffe000200e7c:	00050793          	mv	a5,a0
ffffffe000200e80:	00078713          	mv	a4,a5
ffffffe000200e84:	04100793          	li	a5,65
ffffffe000200e88:	01f79793          	slli	a5,a5,0x1f
ffffffe000200e8c:	00f707b3          	add	a5,a4,a5
ffffffe000200e90:	fef43423          	sd	a5,-24(s0)
            pgtbl_first[vpn2] = (((uint64)pgtbl_second >> 2) | 1);
ffffffe000200e94:	fe843783          	ld	a5,-24(s0)
ffffffe000200e98:	0027d713          	srli	a4,a5,0x2
ffffffe000200e9c:	fd043783          	ld	a5,-48(s0)
ffffffe000200ea0:	00379793          	slli	a5,a5,0x3
ffffffe000200ea4:	fb843683          	ld	a3,-72(s0)
ffffffe000200ea8:	00f687b3          	add	a5,a3,a5
ffffffe000200eac:	00176713          	ori	a4,a4,1
ffffffe000200eb0:	00e7b023          	sd	a4,0(a5)
        }

        uint64 *pgtbl_third;
        if(pgtbl_second[vpn1] & 0x1){
ffffffe000200eb4:	fc843783          	ld	a5,-56(s0)
ffffffe000200eb8:	00379793          	slli	a5,a5,0x3
ffffffe000200ebc:	fe843703          	ld	a4,-24(s0)
ffffffe000200ec0:	00f707b3          	add	a5,a4,a5
ffffffe000200ec4:	0007b783          	ld	a5,0(a5)
ffffffe000200ec8:	0017f793          	andi	a5,a5,1
ffffffe000200ecc:	02078463          	beqz	a5,ffffffe000200ef4 <create_mapping+0x12c>
            pgtbl_third = (uint64)((pgtbl_second[vpn1] >> 10) << 12);
ffffffe000200ed0:	fc843783          	ld	a5,-56(s0)
ffffffe000200ed4:	00379793          	slli	a5,a5,0x3
ffffffe000200ed8:	fe843703          	ld	a4,-24(s0)
ffffffe000200edc:	00f707b3          	add	a5,a4,a5
ffffffe000200ee0:	0007b783          	ld	a5,0(a5)
ffffffe000200ee4:	00a7d793          	srli	a5,a5,0xa
ffffffe000200ee8:	00c79793          	slli	a5,a5,0xc
ffffffe000200eec:	fef43023          	sd	a5,-32(s0)
ffffffe000200ef0:	0400006f          	j	ffffffe000200f30 <create_mapping+0x168>
        }else {
            pgtbl_third = (uint64)(kalloc() - PA2VA_OFFSET);
ffffffe000200ef4:	bfcff0ef          	jal	ra,ffffffe0002002f0 <kalloc>
ffffffe000200ef8:	00050793          	mv	a5,a0
ffffffe000200efc:	00078713          	mv	a4,a5
ffffffe000200f00:	04100793          	li	a5,65
ffffffe000200f04:	01f79793          	slli	a5,a5,0x1f
ffffffe000200f08:	00f707b3          	add	a5,a4,a5
ffffffe000200f0c:	fef43023          	sd	a5,-32(s0)
            pgtbl_second[vpn1] = (((uint64)pgtbl_third >> 2) | 1);
ffffffe000200f10:	fe043783          	ld	a5,-32(s0)
ffffffe000200f14:	0027d713          	srli	a4,a5,0x2
ffffffe000200f18:	fc843783          	ld	a5,-56(s0)
ffffffe000200f1c:	00379793          	slli	a5,a5,0x3
ffffffe000200f20:	fe843683          	ld	a3,-24(s0)
ffffffe000200f24:	00f687b3          	add	a5,a3,a5
ffffffe000200f28:	00176713          	ori	a4,a4,1
ffffffe000200f2c:	00e7b023          	sd	a4,0(a5)
        }

        if(!(pgtbl_third[vpn0] & 0x1)){
ffffffe000200f30:	fc043783          	ld	a5,-64(s0)
ffffffe000200f34:	00379793          	slli	a5,a5,0x3
ffffffe000200f38:	fe043703          	ld	a4,-32(s0)
ffffffe000200f3c:	00f707b3          	add	a5,a4,a5
ffffffe000200f40:	0007b783          	ld	a5,0(a5)
ffffffe000200f44:	0017f793          	andi	a5,a5,1
ffffffe000200f48:	02079663          	bnez	a5,ffffffe000200f74 <create_mapping+0x1ac>
            pgtbl_third[vpn0] = (((pa >> 12) << 10) | perm);
ffffffe000200f4c:	f9843783          	ld	a5,-104(s0)
ffffffe000200f50:	00c7d793          	srli	a5,a5,0xc
ffffffe000200f54:	00a79693          	slli	a3,a5,0xa
ffffffe000200f58:	fc043783          	ld	a5,-64(s0)
ffffffe000200f5c:	00379793          	slli	a5,a5,0x3
ffffffe000200f60:	fe043703          	ld	a4,-32(s0)
ffffffe000200f64:	00f707b3          	add	a5,a4,a5
ffffffe000200f68:	f8843703          	ld	a4,-120(s0)
ffffffe000200f6c:	00e6e733          	or	a4,a3,a4
ffffffe000200f70:	00e7b023          	sd	a4,0(a5)
        }

        va += PGSIZE;
ffffffe000200f74:	fa043703          	ld	a4,-96(s0)
ffffffe000200f78:	000017b7          	lui	a5,0x1
ffffffe000200f7c:	00f707b3          	add	a5,a4,a5
ffffffe000200f80:	faf43023          	sd	a5,-96(s0)
        pa += PGSIZE;
ffffffe000200f84:	f9843703          	ld	a4,-104(s0)
ffffffe000200f88:	000017b7          	lui	a5,0x1
ffffffe000200f8c:	00f707b3          	add	a5,a4,a5
ffffffe000200f90:	f8f43c23          	sd	a5,-104(s0)
   while (va < end)
ffffffe000200f94:	fa043703          	ld	a4,-96(s0)
ffffffe000200f98:	fd843783          	ld	a5,-40(s0)
ffffffe000200f9c:	e6f762e3          	bltu	a4,a5,ffffffe000200e00 <create_mapping+0x38>
   }
   
}
ffffffe000200fa0:	00000013          	nop
ffffffe000200fa4:	00000013          	nop
ffffffe000200fa8:	07813083          	ld	ra,120(sp)
ffffffe000200fac:	07013403          	ld	s0,112(sp)
ffffffe000200fb0:	08010113          	addi	sp,sp,128
ffffffe000200fb4:	00008067          	ret

ffffffe000200fb8 <start_kernel>:
extern char _srodata[];
extern char _sdata[];
extern char _sbss[];

int start_kernel() 
{
ffffffe000200fb8:	ff010113          	addi	sp,sp,-16
ffffffe000200fbc:	00113423          	sd	ra,8(sp)
ffffffe000200fc0:	00813023          	sd	s0,0(sp)
ffffffe000200fc4:	01010413          	addi	s0,sp,16
    // printk("%d", 2024);
    printk("2024 ZJU Computer System III\n");
ffffffe000200fc8:	00001517          	auipc	a0,0x1
ffffffe000200fcc:	16050513          	addi	a0,a0,352 # ffffffe000202128 <_srodata+0x128>
ffffffe000200fd0:	0a9000ef          	jal	ra,ffffffe000201878 <printk>
    // *_srodata = 0;

    // printk("_stext = %ld\n", *_stext);
    // printk("_srodata = %ld\n", *_srodata);

    test(); // DO NOT DELETE !!!
ffffffe000200fd4:	01c000ef          	jal	ra,ffffffe000200ff0 <test>

	return 0;
ffffffe000200fd8:	00000793          	li	a5,0
}
ffffffe000200fdc:	00078513          	mv	a0,a5
ffffffe000200fe0:	00813083          	ld	ra,8(sp)
ffffffe000200fe4:	00013403          	ld	s0,0(sp)
ffffffe000200fe8:	01010113          	addi	sp,sp,16
ffffffe000200fec:	00008067          	ret

ffffffe000200ff0 <test>:
#include "defs.h"
#include "math.h"

// Please do not modify

void test() {
ffffffe000200ff0:	fe010113          	addi	sp,sp,-32
ffffffe000200ff4:	00813c23          	sd	s0,24(sp)
ffffffe000200ff8:	02010413          	addi	s0,sp,32
   unsigned long record_time = 0; 
ffffffe000200ffc:	fe043423          	sd	zero,-24(s0)
    while (1) {
ffffffe000201000:	0000006f          	j	ffffffe000201000 <test+0x10>

ffffffe000201004 <__udivsi3>:
# define __divdi3 __divsi3
# define __moddi3 __modsi3
#else
FUNC_BEGIN (__udivsi3)
  /* Compute __udivdi3(a0 << 32, a1 << 32); cast result to uint32_t.  */
  sll    a0, a0, 32
ffffffe000201004:	02051513          	slli	a0,a0,0x20
  sll    a1, a1, 32
ffffffe000201008:	02059593          	slli	a1,a1,0x20
  move   t0, ra
ffffffe00020100c:	00008293          	mv	t0,ra
  jal    HIDDEN_JUMPTARGET(__udivdi3)
ffffffe000201010:	03c000ef          	jal	ra,ffffffe00020104c <__hidden___udivdi3>
  sext.w a0, a0
ffffffe000201014:	0005051b          	sext.w	a0,a0
  jr     t0
ffffffe000201018:	00028067          	jr	t0

ffffffe00020101c <__umodsi3>:
FUNC_END (__udivsi3)

FUNC_BEGIN (__umodsi3)
  /* Compute __udivdi3((uint32_t)a0, (uint32_t)a1); cast a1 to uint32_t.  */
  sll    a0, a0, 32
ffffffe00020101c:	02051513          	slli	a0,a0,0x20
  sll    a1, a1, 32
ffffffe000201020:	02059593          	slli	a1,a1,0x20
  srl    a0, a0, 32
ffffffe000201024:	02055513          	srli	a0,a0,0x20
  srl    a1, a1, 32
ffffffe000201028:	0205d593          	srli	a1,a1,0x20
  move   t0, ra
ffffffe00020102c:	00008293          	mv	t0,ra
  jal    HIDDEN_JUMPTARGET(__udivdi3)
ffffffe000201030:	01c000ef          	jal	ra,ffffffe00020104c <__hidden___udivdi3>
  sext.w a0, a1
ffffffe000201034:	0005851b          	sext.w	a0,a1
  jr     t0
ffffffe000201038:	00028067          	jr	t0

ffffffe00020103c <__divsi3>:

FUNC_ALIAS (__modsi3, __moddi3)

FUNC_BEGIN( __divsi3)
  /* Check for special case of INT_MIN/-1. Otherwise, fall into __divdi3.  */
  li    t0, -1
ffffffe00020103c:	fff00293          	li	t0,-1
  beq   a1, t0, .L20
ffffffe000201040:	0a558c63          	beq	a1,t0,ffffffe0002010f8 <__moddi3+0x30>

ffffffe000201044 <__divdi3>:
#endif

FUNC_BEGIN (__divdi3)
  bltz  a0, .L10
ffffffe000201044:	06054063          	bltz	a0,ffffffe0002010a4 <__umoddi3+0x10>
  bltz  a1, .L11
ffffffe000201048:	0605c663          	bltz	a1,ffffffe0002010b4 <__umoddi3+0x20>

ffffffe00020104c <__hidden___udivdi3>:
  /* Since the quotient is positive, fall into __udivdi3.  */

FUNC_BEGIN (__udivdi3)
  mv    a2, a1
ffffffe00020104c:	00058613          	mv	a2,a1
  mv    a1, a0
ffffffe000201050:	00050593          	mv	a1,a0
  li    a0, -1
ffffffe000201054:	fff00513          	li	a0,-1
  beqz  a2, .L5
ffffffe000201058:	02060c63          	beqz	a2,ffffffe000201090 <__hidden___udivdi3+0x44>
  li    a3, 1
ffffffe00020105c:	00100693          	li	a3,1
  bgeu  a2, a1, .L2
ffffffe000201060:	00b67a63          	bgeu	a2,a1,ffffffe000201074 <__hidden___udivdi3+0x28>
.L1:
  blez  a2, .L2
ffffffe000201064:	00c05863          	blez	a2,ffffffe000201074 <__hidden___udivdi3+0x28>
  slli  a2, a2, 1
ffffffe000201068:	00161613          	slli	a2,a2,0x1
  slli  a3, a3, 1
ffffffe00020106c:	00169693          	slli	a3,a3,0x1
  bgtu  a1, a2, .L1
ffffffe000201070:	feb66ae3          	bltu	a2,a1,ffffffe000201064 <__hidden___udivdi3+0x18>
.L2:
  li    a0, 0
ffffffe000201074:	00000513          	li	a0,0
.L3:
  bltu  a1, a2, .L4
ffffffe000201078:	00c5e663          	bltu	a1,a2,ffffffe000201084 <__hidden___udivdi3+0x38>
  sub   a1, a1, a2
ffffffe00020107c:	40c585b3          	sub	a1,a1,a2
  or    a0, a0, a3
ffffffe000201080:	00d56533          	or	a0,a0,a3
.L4:
  srli  a3, a3, 1
ffffffe000201084:	0016d693          	srli	a3,a3,0x1
  srli  a2, a2, 1
ffffffe000201088:	00165613          	srli	a2,a2,0x1
  bnez  a3, .L3
ffffffe00020108c:	fe0696e3          	bnez	a3,ffffffe000201078 <__hidden___udivdi3+0x2c>
.L5:
  ret
ffffffe000201090:	00008067          	ret

ffffffe000201094 <__umoddi3>:
FUNC_END (__udivdi3)
HIDDEN_DEF (__udivdi3)

FUNC_BEGIN (__umoddi3)
  /* Call __udivdi3(a0, a1), then return the remainder, which is in a1.  */
  move  t0, ra
ffffffe000201094:	00008293          	mv	t0,ra
  jal   HIDDEN_JUMPTARGET(__udivdi3)
ffffffe000201098:	fb5ff0ef          	jal	ra,ffffffe00020104c <__hidden___udivdi3>
  move  a0, a1
ffffffe00020109c:	00058513          	mv	a0,a1
  jr    t0
ffffffe0002010a0:	00028067          	jr	t0
FUNC_END (__umoddi3)

  /* Handle negative arguments to __divdi3.  */
.L10:
  neg   a0, a0
ffffffe0002010a4:	40a00533          	neg	a0,a0
  /* Zero is handled as a negative so that the result will not be inverted.  */
  bgtz  a1, .L12     /* Compute __udivdi3(-a0, a1), then negate the result.  */
ffffffe0002010a8:	00b04863          	bgtz	a1,ffffffe0002010b8 <__umoddi3+0x24>

  neg   a1, a1
ffffffe0002010ac:	40b005b3          	neg	a1,a1
  j     HIDDEN_JUMPTARGET(__udivdi3)     /* Compute __udivdi3(-a0, -a1).  */
ffffffe0002010b0:	f9dff06f          	j	ffffffe00020104c <__hidden___udivdi3>
.L11:                /* Compute __udivdi3(a0, -a1), then negate the result.  */
  neg   a1, a1
ffffffe0002010b4:	40b005b3          	neg	a1,a1
.L12:
  move  t0, ra
ffffffe0002010b8:	00008293          	mv	t0,ra
  jal   HIDDEN_JUMPTARGET(__udivdi3)
ffffffe0002010bc:	f91ff0ef          	jal	ra,ffffffe00020104c <__hidden___udivdi3>
  neg   a0, a0
ffffffe0002010c0:	40a00533          	neg	a0,a0
  jr    t0
ffffffe0002010c4:	00028067          	jr	t0

ffffffe0002010c8 <__moddi3>:
FUNC_END (__divdi3)

FUNC_BEGIN (__moddi3)
  move   t0, ra
ffffffe0002010c8:	00008293          	mv	t0,ra
  bltz   a1, .L31
ffffffe0002010cc:	0005ca63          	bltz	a1,ffffffe0002010e0 <__moddi3+0x18>
  bltz   a0, .L32
ffffffe0002010d0:	00054c63          	bltz	a0,ffffffe0002010e8 <__moddi3+0x20>
.L30:
  jal    HIDDEN_JUMPTARGET(__udivdi3)    /* The dividend is not negative.  */
ffffffe0002010d4:	f79ff0ef          	jal	ra,ffffffe00020104c <__hidden___udivdi3>
  move   a0, a1
ffffffe0002010d8:	00058513          	mv	a0,a1
  jr     t0
ffffffe0002010dc:	00028067          	jr	t0
.L31:
  neg    a1, a1
ffffffe0002010e0:	40b005b3          	neg	a1,a1
  bgez   a0, .L30
ffffffe0002010e4:	fe0558e3          	bgez	a0,ffffffe0002010d4 <__moddi3+0xc>
.L32:
  neg    a0, a0
ffffffe0002010e8:	40a00533          	neg	a0,a0
  jal    HIDDEN_JUMPTARGET(__udivdi3)    /* The dividend is hella negative.  */
ffffffe0002010ec:	f61ff0ef          	jal	ra,ffffffe00020104c <__hidden___udivdi3>
  neg    a0, a1
ffffffe0002010f0:	40b00533          	neg	a0,a1
  jr     t0
ffffffe0002010f4:	00028067          	jr	t0
FUNC_END (__moddi3)

#if __riscv_xlen == 64
  /* continuation of __divsi3 */
.L20:
  sll   t0, t0, 31
ffffffe0002010f8:	01f29293          	slli	t0,t0,0x1f
  bne   a0, t0, __divdi3
ffffffe0002010fc:	f45514e3          	bne	a0,t0,ffffffe000201044 <__divdi3>
  ret
ffffffe000201100:	00008067          	ret

ffffffe000201104 <int_mod>:
#include"math.h"
int int_mod(unsigned int v1,unsigned int v2){
ffffffe000201104:	fd010113          	addi	sp,sp,-48
ffffffe000201108:	02813423          	sd	s0,40(sp)
ffffffe00020110c:	03010413          	addi	s0,sp,48
ffffffe000201110:	00050793          	mv	a5,a0
ffffffe000201114:	00058713          	mv	a4,a1
ffffffe000201118:	fcf42e23          	sw	a5,-36(s0)
ffffffe00020111c:	00070793          	mv	a5,a4
ffffffe000201120:	fcf42c23          	sw	a5,-40(s0)
    unsigned long long m1=v1;
ffffffe000201124:	fdc46783          	lwu	a5,-36(s0)
ffffffe000201128:	fef43423          	sd	a5,-24(s0)
    unsigned long long m2=v2;
ffffffe00020112c:	fd846783          	lwu	a5,-40(s0)
ffffffe000201130:	fef43023          	sd	a5,-32(s0)
    m2<<=31;
ffffffe000201134:	fe043783          	ld	a5,-32(s0)
ffffffe000201138:	01f79793          	slli	a5,a5,0x1f
ffffffe00020113c:	fef43023          	sd	a5,-32(s0)
    while(m1>=v2){
ffffffe000201140:	02c0006f          	j	ffffffe00020116c <int_mod+0x68>
        if(m2<m1){
ffffffe000201144:	fe043703          	ld	a4,-32(s0)
ffffffe000201148:	fe843783          	ld	a5,-24(s0)
ffffffe00020114c:	00f77a63          	bgeu	a4,a5,ffffffe000201160 <int_mod+0x5c>
            m1-=m2;
ffffffe000201150:	fe843703          	ld	a4,-24(s0)
ffffffe000201154:	fe043783          	ld	a5,-32(s0)
ffffffe000201158:	40f707b3          	sub	a5,a4,a5
ffffffe00020115c:	fef43423          	sd	a5,-24(s0)
        }
        m2>>=1;
ffffffe000201160:	fe043783          	ld	a5,-32(s0)
ffffffe000201164:	0017d793          	srli	a5,a5,0x1
ffffffe000201168:	fef43023          	sd	a5,-32(s0)
    while(m1>=v2){
ffffffe00020116c:	fd846783          	lwu	a5,-40(s0)
ffffffe000201170:	fe843703          	ld	a4,-24(s0)
ffffffe000201174:	fcf778e3          	bgeu	a4,a5,ffffffe000201144 <int_mod+0x40>
    }
    return m1;
ffffffe000201178:	fe843783          	ld	a5,-24(s0)
ffffffe00020117c:	0007879b          	sext.w	a5,a5
}
ffffffe000201180:	00078513          	mv	a0,a5
ffffffe000201184:	02813403          	ld	s0,40(sp)
ffffffe000201188:	03010113          	addi	sp,sp,48
ffffffe00020118c:	00008067          	ret

ffffffe000201190 <int_mul>:

int int_mul(unsigned int v1,unsigned int v2){
ffffffe000201190:	fd010113          	addi	sp,sp,-48
ffffffe000201194:	02813423          	sd	s0,40(sp)
ffffffe000201198:	03010413          	addi	s0,sp,48
ffffffe00020119c:	00050793          	mv	a5,a0
ffffffe0002011a0:	00058713          	mv	a4,a1
ffffffe0002011a4:	fcf42e23          	sw	a5,-36(s0)
ffffffe0002011a8:	00070793          	mv	a5,a4
ffffffe0002011ac:	fcf42c23          	sw	a5,-40(s0)
    unsigned long long res=0;
ffffffe0002011b0:	fe043423          	sd	zero,-24(s0)
    while(v2&&v1){
ffffffe0002011b4:	03c0006f          	j	ffffffe0002011f0 <int_mul+0x60>
        if(v2&1){
ffffffe0002011b8:	fd842783          	lw	a5,-40(s0)
ffffffe0002011bc:	0017f793          	andi	a5,a5,1
ffffffe0002011c0:	0007879b          	sext.w	a5,a5
ffffffe0002011c4:	00078a63          	beqz	a5,ffffffe0002011d8 <int_mul+0x48>
            res+=v1;
ffffffe0002011c8:	fdc46783          	lwu	a5,-36(s0)
ffffffe0002011cc:	fe843703          	ld	a4,-24(s0)
ffffffe0002011d0:	00f707b3          	add	a5,a4,a5
ffffffe0002011d4:	fef43423          	sd	a5,-24(s0)
        }
        v2>>=1;
ffffffe0002011d8:	fd842783          	lw	a5,-40(s0)
ffffffe0002011dc:	0017d79b          	srliw	a5,a5,0x1
ffffffe0002011e0:	fcf42c23          	sw	a5,-40(s0)
        v1<<=1;
ffffffe0002011e4:	fdc42783          	lw	a5,-36(s0)
ffffffe0002011e8:	0017979b          	slliw	a5,a5,0x1
ffffffe0002011ec:	fcf42e23          	sw	a5,-36(s0)
    while(v2&&v1){
ffffffe0002011f0:	fd842783          	lw	a5,-40(s0)
ffffffe0002011f4:	0007879b          	sext.w	a5,a5
ffffffe0002011f8:	00078863          	beqz	a5,ffffffe000201208 <int_mul+0x78>
ffffffe0002011fc:	fdc42783          	lw	a5,-36(s0)
ffffffe000201200:	0007879b          	sext.w	a5,a5
ffffffe000201204:	fa079ae3          	bnez	a5,ffffffe0002011b8 <int_mul+0x28>
    }
    return res;
ffffffe000201208:	fe843783          	ld	a5,-24(s0)
ffffffe00020120c:	0007879b          	sext.w	a5,a5
}
ffffffe000201210:	00078513          	mv	a0,a5
ffffffe000201214:	02813403          	ld	s0,40(sp)
ffffffe000201218:	03010113          	addi	sp,sp,48
ffffffe00020121c:	00008067          	ret

ffffffe000201220 <int_div>:

int int_div(unsigned int v1,unsigned int v2){
ffffffe000201220:	fc010113          	addi	sp,sp,-64
ffffffe000201224:	02813c23          	sd	s0,56(sp)
ffffffe000201228:	04010413          	addi	s0,sp,64
ffffffe00020122c:	00050793          	mv	a5,a0
ffffffe000201230:	00058713          	mv	a4,a1
ffffffe000201234:	fcf42623          	sw	a5,-52(s0)
ffffffe000201238:	00070793          	mv	a5,a4
ffffffe00020123c:	fcf42423          	sw	a5,-56(s0)
    unsigned long long m1=v1;
ffffffe000201240:	fcc46783          	lwu	a5,-52(s0)
ffffffe000201244:	fef43423          	sd	a5,-24(s0)
    unsigned long long m2=v2;
ffffffe000201248:	fc846783          	lwu	a5,-56(s0)
ffffffe00020124c:	fef43023          	sd	a5,-32(s0)
    unsigned long long mask=(unsigned int)1<<31;
ffffffe000201250:	00100793          	li	a5,1
ffffffe000201254:	01f79793          	slli	a5,a5,0x1f
ffffffe000201258:	fcf43c23          	sd	a5,-40(s0)
    m2<<=31;
ffffffe00020125c:	fe043783          	ld	a5,-32(s0)
ffffffe000201260:	01f79793          	slli	a5,a5,0x1f
ffffffe000201264:	fef43023          	sd	a5,-32(s0)
    unsigned long long res=0;
ffffffe000201268:	fc043823          	sd	zero,-48(s0)
    while(m1>=v2){
ffffffe00020126c:	0480006f          	j	ffffffe0002012b4 <int_div+0x94>
        if(m2<m1){
ffffffe000201270:	fe043703          	ld	a4,-32(s0)
ffffffe000201274:	fe843783          	ld	a5,-24(s0)
ffffffe000201278:	02f77263          	bgeu	a4,a5,ffffffe00020129c <int_div+0x7c>
            m1-=m2;
ffffffe00020127c:	fe843703          	ld	a4,-24(s0)
ffffffe000201280:	fe043783          	ld	a5,-32(s0)
ffffffe000201284:	40f707b3          	sub	a5,a4,a5
ffffffe000201288:	fef43423          	sd	a5,-24(s0)
            res|=mask;
ffffffe00020128c:	fd043703          	ld	a4,-48(s0)
ffffffe000201290:	fd843783          	ld	a5,-40(s0)
ffffffe000201294:	00f767b3          	or	a5,a4,a5
ffffffe000201298:	fcf43823          	sd	a5,-48(s0)
        }
        m2>>=1;
ffffffe00020129c:	fe043783          	ld	a5,-32(s0)
ffffffe0002012a0:	0017d793          	srli	a5,a5,0x1
ffffffe0002012a4:	fef43023          	sd	a5,-32(s0)
        mask>>=1;
ffffffe0002012a8:	fd843783          	ld	a5,-40(s0)
ffffffe0002012ac:	0017d793          	srli	a5,a5,0x1
ffffffe0002012b0:	fcf43c23          	sd	a5,-40(s0)
    while(m1>=v2){
ffffffe0002012b4:	fc846783          	lwu	a5,-56(s0)
ffffffe0002012b8:	fe843703          	ld	a4,-24(s0)
ffffffe0002012bc:	faf77ae3          	bgeu	a4,a5,ffffffe000201270 <int_div+0x50>
    }
    return res;
ffffffe0002012c0:	fd043783          	ld	a5,-48(s0)
ffffffe0002012c4:	0007879b          	sext.w	a5,a5
ffffffe0002012c8:	00078513          	mv	a0,a5
ffffffe0002012cc:	03813403          	ld	s0,56(sp)
ffffffe0002012d0:	04010113          	addi	sp,sp,64
ffffffe0002012d4:	00008067          	ret

ffffffe0002012d8 <__muldi3>:
/* Our RV64 64-bit routine is equivalent to our RV32 32-bit routine.  */
# define __muldi3 __mulsi3
#endif

FUNC_BEGIN (__muldi3)
  mv     a2, a0
ffffffe0002012d8:	00050613          	mv	a2,a0
  li     a0, 0
ffffffe0002012dc:	00000513          	li	a0,0
.L1:
  andi   a3, a1, 1
ffffffe0002012e0:	0015f693          	andi	a3,a1,1
  beqz   a3, .L2
ffffffe0002012e4:	00068463          	beqz	a3,ffffffe0002012ec <__muldi3+0x14>
  add    a0, a0, a2
ffffffe0002012e8:	00c50533          	add	a0,a0,a2
.L2:
  srli   a1, a1, 1
ffffffe0002012ec:	0015d593          	srli	a1,a1,0x1
  slli   a2, a2, 1
ffffffe0002012f0:	00161613          	slli	a2,a2,0x1
  bnez   a1, .L1
ffffffe0002012f4:	fe0596e3          	bnez	a1,ffffffe0002012e0 <__muldi3+0x8>
  ret
ffffffe0002012f8:	00008067          	ret

ffffffe0002012fc <putc>:
#include "printk.h"
#include "sbi.h"
#include "math.h"

void putc(char c) {
ffffffe0002012fc:	fe010113          	addi	sp,sp,-32
ffffffe000201300:	00113c23          	sd	ra,24(sp)
ffffffe000201304:	00813823          	sd	s0,16(sp)
ffffffe000201308:	02010413          	addi	s0,sp,32
ffffffe00020130c:	00050793          	mv	a5,a0
ffffffe000201310:	fef407a3          	sb	a5,-17(s0)
  sbi_ecall(SBI_PUTCHAR, 0, c, 0, 0, 0, 0, 0);
ffffffe000201314:	fef44603          	lbu	a2,-17(s0)
ffffffe000201318:	00000893          	li	a7,0
ffffffe00020131c:	00000813          	li	a6,0
ffffffe000201320:	00000793          	li	a5,0
ffffffe000201324:	00000713          	li	a4,0
ffffffe000201328:	00000693          	li	a3,0
ffffffe00020132c:	00000593          	li	a1,0
ffffffe000201330:	00100513          	li	a0,1
ffffffe000201334:	f00ff0ef          	jal	ra,ffffffe000200a34 <sbi_ecall>
}
ffffffe000201338:	00000013          	nop
ffffffe00020133c:	01813083          	ld	ra,24(sp)
ffffffe000201340:	01013403          	ld	s0,16(sp)
ffffffe000201344:	02010113          	addi	sp,sp,32
ffffffe000201348:	00008067          	ret

ffffffe00020134c <vprintfmt>:

static int vprintfmt(void(*putch)(char), const char *fmt, va_list vl) {
ffffffe00020134c:	f2010113          	addi	sp,sp,-224
ffffffe000201350:	0c113c23          	sd	ra,216(sp)
ffffffe000201354:	0c813823          	sd	s0,208(sp)
ffffffe000201358:	0e010413          	addi	s0,sp,224
ffffffe00020135c:	f2a43c23          	sd	a0,-200(s0)
ffffffe000201360:	f2b43823          	sd	a1,-208(s0)
ffffffe000201364:	f2c43423          	sd	a2,-216(s0)
    int in_format = 0, longarg = 0;
ffffffe000201368:	fe042623          	sw	zero,-20(s0)
ffffffe00020136c:	fe042423          	sw	zero,-24(s0)
    size_t pos = 0;
ffffffe000201370:	fe043023          	sd	zero,-32(s0)
    for( ; *fmt; fmt++) {
ffffffe000201374:	4dc0006f          	j	ffffffe000201850 <vprintfmt+0x504>
        if (in_format) {
ffffffe000201378:	fec42783          	lw	a5,-20(s0)
ffffffe00020137c:	0007879b          	sext.w	a5,a5
ffffffe000201380:	46078e63          	beqz	a5,ffffffe0002017fc <vprintfmt+0x4b0>
            switch(*fmt) {
ffffffe000201384:	f3043783          	ld	a5,-208(s0)
ffffffe000201388:	0007c783          	lbu	a5,0(a5) # 1000 <_skernel-0xffffffe0001ff000>
ffffffe00020138c:	0007879b          	sext.w	a5,a5
ffffffe000201390:	f9d7869b          	addiw	a3,a5,-99
ffffffe000201394:	0006871b          	sext.w	a4,a3
ffffffe000201398:	01500793          	li	a5,21
ffffffe00020139c:	4ae7e263          	bltu	a5,a4,ffffffe000201840 <vprintfmt+0x4f4>
ffffffe0002013a0:	02069793          	slli	a5,a3,0x20
ffffffe0002013a4:	0207d793          	srli	a5,a5,0x20
ffffffe0002013a8:	00279713          	slli	a4,a5,0x2
ffffffe0002013ac:	00001797          	auipc	a5,0x1
ffffffe0002013b0:	d9c78793          	addi	a5,a5,-612 # ffffffe000202148 <_srodata+0x148>
ffffffe0002013b4:	00f707b3          	add	a5,a4,a5
ffffffe0002013b8:	0007a783          	lw	a5,0(a5)
ffffffe0002013bc:	0007871b          	sext.w	a4,a5
ffffffe0002013c0:	00001797          	auipc	a5,0x1
ffffffe0002013c4:	d8878793          	addi	a5,a5,-632 # ffffffe000202148 <_srodata+0x148>
ffffffe0002013c8:	00f707b3          	add	a5,a4,a5
ffffffe0002013cc:	00078067          	jr	a5
                case 'l': { 
                    longarg = 1; 
ffffffe0002013d0:	00100793          	li	a5,1
ffffffe0002013d4:	fef42423          	sw	a5,-24(s0)
                    break; 
ffffffe0002013d8:	46c0006f          	j	ffffffe000201844 <vprintfmt+0x4f8>
                }
                
                case 'x': {
                    long num = longarg ? va_arg(vl, long) : va_arg(vl, int);
ffffffe0002013dc:	fe842783          	lw	a5,-24(s0)
ffffffe0002013e0:	0007879b          	sext.w	a5,a5
ffffffe0002013e4:	00078c63          	beqz	a5,ffffffe0002013fc <vprintfmt+0xb0>
ffffffe0002013e8:	f2843783          	ld	a5,-216(s0)
ffffffe0002013ec:	00878713          	addi	a4,a5,8
ffffffe0002013f0:	f2e43423          	sd	a4,-216(s0)
ffffffe0002013f4:	0007b783          	ld	a5,0(a5)
ffffffe0002013f8:	0140006f          	j	ffffffe00020140c <vprintfmt+0xc0>
ffffffe0002013fc:	f2843783          	ld	a5,-216(s0)
ffffffe000201400:	00878713          	addi	a4,a5,8
ffffffe000201404:	f2e43423          	sd	a4,-216(s0)
ffffffe000201408:	0007a783          	lw	a5,0(a5)
ffffffe00020140c:	f8f43c23          	sd	a5,-104(s0)

                    int hexdigits = int_mul(2, (longarg ? sizeof(long) : sizeof(int))) - 1;
ffffffe000201410:	fe842783          	lw	a5,-24(s0)
ffffffe000201414:	0007879b          	sext.w	a5,a5
ffffffe000201418:	00078663          	beqz	a5,ffffffe000201424 <vprintfmt+0xd8>
ffffffe00020141c:	00800793          	li	a5,8
ffffffe000201420:	0080006f          	j	ffffffe000201428 <vprintfmt+0xdc>
ffffffe000201424:	00400793          	li	a5,4
ffffffe000201428:	00078593          	mv	a1,a5
ffffffe00020142c:	00200513          	li	a0,2
ffffffe000201430:	d61ff0ef          	jal	ra,ffffffe000201190 <int_mul>
ffffffe000201434:	00050793          	mv	a5,a0
ffffffe000201438:	fff7879b          	addiw	a5,a5,-1
ffffffe00020143c:	f8f42a23          	sw	a5,-108(s0)
                    for(int halfbyte = hexdigits; halfbyte >= 0; halfbyte--) {
ffffffe000201440:	f9442783          	lw	a5,-108(s0)
ffffffe000201444:	fcf42e23          	sw	a5,-36(s0)
ffffffe000201448:	0900006f          	j	ffffffe0002014d8 <vprintfmt+0x18c>
                        int hex = (num >> int_mul(4, halfbyte)) & 0xF;
ffffffe00020144c:	fdc42783          	lw	a5,-36(s0)
ffffffe000201450:	00078593          	mv	a1,a5
ffffffe000201454:	00400513          	li	a0,4
ffffffe000201458:	d39ff0ef          	jal	ra,ffffffe000201190 <int_mul>
ffffffe00020145c:	00050793          	mv	a5,a0
ffffffe000201460:	00078713          	mv	a4,a5
ffffffe000201464:	f9843783          	ld	a5,-104(s0)
ffffffe000201468:	40e7d7b3          	sra	a5,a5,a4
ffffffe00020146c:	0007879b          	sext.w	a5,a5
ffffffe000201470:	00f7f793          	andi	a5,a5,15
ffffffe000201474:	f8f42823          	sw	a5,-112(s0)
                        char hexchar = (hex < 10 ? '0' + hex : 'a' + hex - 10);
ffffffe000201478:	f9042783          	lw	a5,-112(s0)
ffffffe00020147c:	0007871b          	sext.w	a4,a5
ffffffe000201480:	00900793          	li	a5,9
ffffffe000201484:	00e7cc63          	blt	a5,a4,ffffffe00020149c <vprintfmt+0x150>
ffffffe000201488:	f9042783          	lw	a5,-112(s0)
ffffffe00020148c:	0ff7f793          	zext.b	a5,a5
ffffffe000201490:	0307879b          	addiw	a5,a5,48
ffffffe000201494:	0ff7f793          	zext.b	a5,a5
ffffffe000201498:	0140006f          	j	ffffffe0002014ac <vprintfmt+0x160>
ffffffe00020149c:	f9042783          	lw	a5,-112(s0)
ffffffe0002014a0:	0ff7f793          	zext.b	a5,a5
ffffffe0002014a4:	0577879b          	addiw	a5,a5,87
ffffffe0002014a8:	0ff7f793          	zext.b	a5,a5
ffffffe0002014ac:	f8f407a3          	sb	a5,-113(s0)
                        putch(hexchar);
ffffffe0002014b0:	f8f44703          	lbu	a4,-113(s0)
ffffffe0002014b4:	f3843783          	ld	a5,-200(s0)
ffffffe0002014b8:	00070513          	mv	a0,a4
ffffffe0002014bc:	000780e7          	jalr	a5
                        pos++;
ffffffe0002014c0:	fe043783          	ld	a5,-32(s0)
ffffffe0002014c4:	00178793          	addi	a5,a5,1
ffffffe0002014c8:	fef43023          	sd	a5,-32(s0)
                    for(int halfbyte = hexdigits; halfbyte >= 0; halfbyte--) {
ffffffe0002014cc:	fdc42783          	lw	a5,-36(s0)
ffffffe0002014d0:	fff7879b          	addiw	a5,a5,-1
ffffffe0002014d4:	fcf42e23          	sw	a5,-36(s0)
ffffffe0002014d8:	fdc42783          	lw	a5,-36(s0)
ffffffe0002014dc:	0007879b          	sext.w	a5,a5
ffffffe0002014e0:	f607d6e3          	bgez	a5,ffffffe00020144c <vprintfmt+0x100>
                    }
                    longarg = 0; in_format = 0; 
ffffffe0002014e4:	fe042423          	sw	zero,-24(s0)
ffffffe0002014e8:	fe042623          	sw	zero,-20(s0)
                    break;
ffffffe0002014ec:	3580006f          	j	ffffffe000201844 <vprintfmt+0x4f8>
                }
            
                case 'd': {
                    long num = longarg ? va_arg(vl, long) : va_arg(vl, int);
ffffffe0002014f0:	fe842783          	lw	a5,-24(s0)
ffffffe0002014f4:	0007879b          	sext.w	a5,a5
ffffffe0002014f8:	00078c63          	beqz	a5,ffffffe000201510 <vprintfmt+0x1c4>
ffffffe0002014fc:	f2843783          	ld	a5,-216(s0)
ffffffe000201500:	00878713          	addi	a4,a5,8
ffffffe000201504:	f2e43423          	sd	a4,-216(s0)
ffffffe000201508:	0007b783          	ld	a5,0(a5)
ffffffe00020150c:	0140006f          	j	ffffffe000201520 <vprintfmt+0x1d4>
ffffffe000201510:	f2843783          	ld	a5,-216(s0)
ffffffe000201514:	00878713          	addi	a4,a5,8
ffffffe000201518:	f2e43423          	sd	a4,-216(s0)
ffffffe00020151c:	0007a783          	lw	a5,0(a5)
ffffffe000201520:	fcf43823          	sd	a5,-48(s0)
                    if (num < 0) {
ffffffe000201524:	fd043783          	ld	a5,-48(s0)
ffffffe000201528:	0207d463          	bgez	a5,ffffffe000201550 <vprintfmt+0x204>
                        num = -num; putch('-');
ffffffe00020152c:	fd043783          	ld	a5,-48(s0)
ffffffe000201530:	40f007b3          	neg	a5,a5
ffffffe000201534:	fcf43823          	sd	a5,-48(s0)
ffffffe000201538:	f3843783          	ld	a5,-200(s0)
ffffffe00020153c:	02d00513          	li	a0,45
ffffffe000201540:	000780e7          	jalr	a5
                        pos++;
ffffffe000201544:	fe043783          	ld	a5,-32(s0)
ffffffe000201548:	00178793          	addi	a5,a5,1
ffffffe00020154c:	fef43023          	sd	a5,-32(s0)
                    }
                    int bits = 0;
ffffffe000201550:	fc042623          	sw	zero,-52(s0)
                    char decchar[25] = {'0', 0};
ffffffe000201554:	03000793          	li	a5,48
ffffffe000201558:	f6f43023          	sd	a5,-160(s0)
ffffffe00020155c:	f6043423          	sd	zero,-152(s0)
ffffffe000201560:	f6043823          	sd	zero,-144(s0)
ffffffe000201564:	f6040c23          	sb	zero,-136(s0)
                    for (long tmp = num; tmp; bits++) {
ffffffe000201568:	fd043783          	ld	a5,-48(s0)
ffffffe00020156c:	fcf43023          	sd	a5,-64(s0)
ffffffe000201570:	0600006f          	j	ffffffe0002015d0 <vprintfmt+0x284>
                        decchar[bits] = int_mod(tmp, 10) + '0';
ffffffe000201574:	fc043783          	ld	a5,-64(s0)
ffffffe000201578:	0007879b          	sext.w	a5,a5
ffffffe00020157c:	00a00593          	li	a1,10
ffffffe000201580:	00078513          	mv	a0,a5
ffffffe000201584:	b81ff0ef          	jal	ra,ffffffe000201104 <int_mod>
ffffffe000201588:	00050793          	mv	a5,a0
ffffffe00020158c:	0ff7f793          	zext.b	a5,a5
ffffffe000201590:	0307879b          	addiw	a5,a5,48
ffffffe000201594:	0ff7f713          	zext.b	a4,a5
ffffffe000201598:	fcc42783          	lw	a5,-52(s0)
ffffffe00020159c:	ff078793          	addi	a5,a5,-16
ffffffe0002015a0:	008787b3          	add	a5,a5,s0
ffffffe0002015a4:	f6e78823          	sb	a4,-144(a5)
                        tmp = int_div(tmp, 10);
ffffffe0002015a8:	fc043783          	ld	a5,-64(s0)
ffffffe0002015ac:	0007879b          	sext.w	a5,a5
ffffffe0002015b0:	00a00593          	li	a1,10
ffffffe0002015b4:	00078513          	mv	a0,a5
ffffffe0002015b8:	c69ff0ef          	jal	ra,ffffffe000201220 <int_div>
ffffffe0002015bc:	00050793          	mv	a5,a0
ffffffe0002015c0:	fcf43023          	sd	a5,-64(s0)
                    for (long tmp = num; tmp; bits++) {
ffffffe0002015c4:	fcc42783          	lw	a5,-52(s0)
ffffffe0002015c8:	0017879b          	addiw	a5,a5,1
ffffffe0002015cc:	fcf42623          	sw	a5,-52(s0)
ffffffe0002015d0:	fc043783          	ld	a5,-64(s0)
ffffffe0002015d4:	fa0790e3          	bnez	a5,ffffffe000201574 <vprintfmt+0x228>
                    }

                    for (int i = bits; i >= 0; i--) {
ffffffe0002015d8:	fcc42783          	lw	a5,-52(s0)
ffffffe0002015dc:	faf42e23          	sw	a5,-68(s0)
ffffffe0002015e0:	02c0006f          	j	ffffffe00020160c <vprintfmt+0x2c0>
                        putch(decchar[i]);
ffffffe0002015e4:	fbc42783          	lw	a5,-68(s0)
ffffffe0002015e8:	ff078793          	addi	a5,a5,-16
ffffffe0002015ec:	008787b3          	add	a5,a5,s0
ffffffe0002015f0:	f707c703          	lbu	a4,-144(a5)
ffffffe0002015f4:	f3843783          	ld	a5,-200(s0)
ffffffe0002015f8:	00070513          	mv	a0,a4
ffffffe0002015fc:	000780e7          	jalr	a5
                    for (int i = bits; i >= 0; i--) {
ffffffe000201600:	fbc42783          	lw	a5,-68(s0)
ffffffe000201604:	fff7879b          	addiw	a5,a5,-1
ffffffe000201608:	faf42e23          	sw	a5,-68(s0)
ffffffe00020160c:	fbc42783          	lw	a5,-68(s0)
ffffffe000201610:	0007879b          	sext.w	a5,a5
ffffffe000201614:	fc07d8e3          	bgez	a5,ffffffe0002015e4 <vprintfmt+0x298>
                    }
                    pos += bits + 1;
ffffffe000201618:	fcc42783          	lw	a5,-52(s0)
ffffffe00020161c:	0017879b          	addiw	a5,a5,1
ffffffe000201620:	0007879b          	sext.w	a5,a5
ffffffe000201624:	00078713          	mv	a4,a5
ffffffe000201628:	fe043783          	ld	a5,-32(s0)
ffffffe00020162c:	00e787b3          	add	a5,a5,a4
ffffffe000201630:	fef43023          	sd	a5,-32(s0)
                    longarg = 0; in_format = 0; 
ffffffe000201634:	fe042423          	sw	zero,-24(s0)
ffffffe000201638:	fe042623          	sw	zero,-20(s0)
                    break;
ffffffe00020163c:	2080006f          	j	ffffffe000201844 <vprintfmt+0x4f8>
                }

                case 'u': {
                    unsigned long num = longarg ? va_arg(vl, long) : va_arg(vl, int);
ffffffe000201640:	fe842783          	lw	a5,-24(s0)
ffffffe000201644:	0007879b          	sext.w	a5,a5
ffffffe000201648:	00078c63          	beqz	a5,ffffffe000201660 <vprintfmt+0x314>
ffffffe00020164c:	f2843783          	ld	a5,-216(s0)
ffffffe000201650:	00878713          	addi	a4,a5,8
ffffffe000201654:	f2e43423          	sd	a4,-216(s0)
ffffffe000201658:	0007b783          	ld	a5,0(a5)
ffffffe00020165c:	0140006f          	j	ffffffe000201670 <vprintfmt+0x324>
ffffffe000201660:	f2843783          	ld	a5,-216(s0)
ffffffe000201664:	00878713          	addi	a4,a5,8
ffffffe000201668:	f2e43423          	sd	a4,-216(s0)
ffffffe00020166c:	0007a783          	lw	a5,0(a5)
ffffffe000201670:	f8f43023          	sd	a5,-128(s0)
                    int bits = 0;
ffffffe000201674:	fa042c23          	sw	zero,-72(s0)
                    char decchar[25] = {'0', 0};
ffffffe000201678:	03000793          	li	a5,48
ffffffe00020167c:	f4f43023          	sd	a5,-192(s0)
ffffffe000201680:	f4043423          	sd	zero,-184(s0)
ffffffe000201684:	f4043823          	sd	zero,-176(s0)
ffffffe000201688:	f4040c23          	sb	zero,-168(s0)
                    for (long tmp = num; tmp; bits++) {
ffffffe00020168c:	f8043783          	ld	a5,-128(s0)
ffffffe000201690:	faf43823          	sd	a5,-80(s0)
ffffffe000201694:	0600006f          	j	ffffffe0002016f4 <vprintfmt+0x3a8>
                        decchar[bits] = int_mod(tmp, 10) + '0';
ffffffe000201698:	fb043783          	ld	a5,-80(s0)
ffffffe00020169c:	0007879b          	sext.w	a5,a5
ffffffe0002016a0:	00a00593          	li	a1,10
ffffffe0002016a4:	00078513          	mv	a0,a5
ffffffe0002016a8:	a5dff0ef          	jal	ra,ffffffe000201104 <int_mod>
ffffffe0002016ac:	00050793          	mv	a5,a0
ffffffe0002016b0:	0ff7f793          	zext.b	a5,a5
ffffffe0002016b4:	0307879b          	addiw	a5,a5,48
ffffffe0002016b8:	0ff7f713          	zext.b	a4,a5
ffffffe0002016bc:	fb842783          	lw	a5,-72(s0)
ffffffe0002016c0:	ff078793          	addi	a5,a5,-16
ffffffe0002016c4:	008787b3          	add	a5,a5,s0
ffffffe0002016c8:	f4e78823          	sb	a4,-176(a5)
                        tmp = int_div(tmp, 10);
ffffffe0002016cc:	fb043783          	ld	a5,-80(s0)
ffffffe0002016d0:	0007879b          	sext.w	a5,a5
ffffffe0002016d4:	00a00593          	li	a1,10
ffffffe0002016d8:	00078513          	mv	a0,a5
ffffffe0002016dc:	b45ff0ef          	jal	ra,ffffffe000201220 <int_div>
ffffffe0002016e0:	00050793          	mv	a5,a0
ffffffe0002016e4:	faf43823          	sd	a5,-80(s0)
                    for (long tmp = num; tmp; bits++) {
ffffffe0002016e8:	fb842783          	lw	a5,-72(s0)
ffffffe0002016ec:	0017879b          	addiw	a5,a5,1
ffffffe0002016f0:	faf42c23          	sw	a5,-72(s0)
ffffffe0002016f4:	fb043783          	ld	a5,-80(s0)
ffffffe0002016f8:	fa0790e3          	bnez	a5,ffffffe000201698 <vprintfmt+0x34c>
                    }

                    for (int i = bits; i >= 0; i--) {
ffffffe0002016fc:	fb842783          	lw	a5,-72(s0)
ffffffe000201700:	faf42623          	sw	a5,-84(s0)
ffffffe000201704:	02c0006f          	j	ffffffe000201730 <vprintfmt+0x3e4>
                        putch(decchar[i]);
ffffffe000201708:	fac42783          	lw	a5,-84(s0)
ffffffe00020170c:	ff078793          	addi	a5,a5,-16
ffffffe000201710:	008787b3          	add	a5,a5,s0
ffffffe000201714:	f507c703          	lbu	a4,-176(a5)
ffffffe000201718:	f3843783          	ld	a5,-200(s0)
ffffffe00020171c:	00070513          	mv	a0,a4
ffffffe000201720:	000780e7          	jalr	a5
                    for (int i = bits; i >= 0; i--) {
ffffffe000201724:	fac42783          	lw	a5,-84(s0)
ffffffe000201728:	fff7879b          	addiw	a5,a5,-1
ffffffe00020172c:	faf42623          	sw	a5,-84(s0)
ffffffe000201730:	fac42783          	lw	a5,-84(s0)
ffffffe000201734:	0007879b          	sext.w	a5,a5
ffffffe000201738:	fc07d8e3          	bgez	a5,ffffffe000201708 <vprintfmt+0x3bc>
                    }
                    pos += bits + 1;
ffffffe00020173c:	fb842783          	lw	a5,-72(s0)
ffffffe000201740:	0017879b          	addiw	a5,a5,1
ffffffe000201744:	0007879b          	sext.w	a5,a5
ffffffe000201748:	00078713          	mv	a4,a5
ffffffe00020174c:	fe043783          	ld	a5,-32(s0)
ffffffe000201750:	00e787b3          	add	a5,a5,a4
ffffffe000201754:	fef43023          	sd	a5,-32(s0)
                    longarg = 0; in_format = 0; 
ffffffe000201758:	fe042423          	sw	zero,-24(s0)
ffffffe00020175c:	fe042623          	sw	zero,-20(s0)
                    break;
ffffffe000201760:	0e40006f          	j	ffffffe000201844 <vprintfmt+0x4f8>
                }

                case 's': {
                    const char* str = va_arg(vl, const char*);
ffffffe000201764:	f2843783          	ld	a5,-216(s0)
ffffffe000201768:	00878713          	addi	a4,a5,8
ffffffe00020176c:	f2e43423          	sd	a4,-216(s0)
ffffffe000201770:	0007b783          	ld	a5,0(a5)
ffffffe000201774:	faf43023          	sd	a5,-96(s0)
                    while (*str) {
ffffffe000201778:	0300006f          	j	ffffffe0002017a8 <vprintfmt+0x45c>
                        putch(*str);
ffffffe00020177c:	fa043783          	ld	a5,-96(s0)
ffffffe000201780:	0007c703          	lbu	a4,0(a5)
ffffffe000201784:	f3843783          	ld	a5,-200(s0)
ffffffe000201788:	00070513          	mv	a0,a4
ffffffe00020178c:	000780e7          	jalr	a5
                        pos++; 
ffffffe000201790:	fe043783          	ld	a5,-32(s0)
ffffffe000201794:	00178793          	addi	a5,a5,1
ffffffe000201798:	fef43023          	sd	a5,-32(s0)
                        str++;
ffffffe00020179c:	fa043783          	ld	a5,-96(s0)
ffffffe0002017a0:	00178793          	addi	a5,a5,1
ffffffe0002017a4:	faf43023          	sd	a5,-96(s0)
                    while (*str) {
ffffffe0002017a8:	fa043783          	ld	a5,-96(s0)
ffffffe0002017ac:	0007c783          	lbu	a5,0(a5)
ffffffe0002017b0:	fc0796e3          	bnez	a5,ffffffe00020177c <vprintfmt+0x430>
                    }
                    longarg = 0; in_format = 0; 
ffffffe0002017b4:	fe042423          	sw	zero,-24(s0)
ffffffe0002017b8:	fe042623          	sw	zero,-20(s0)
                    break;
ffffffe0002017bc:	0880006f          	j	ffffffe000201844 <vprintfmt+0x4f8>
                }

                case 'c': {
                    char ch = (char)va_arg(vl,int);
ffffffe0002017c0:	f2843783          	ld	a5,-216(s0)
ffffffe0002017c4:	00878713          	addi	a4,a5,8
ffffffe0002017c8:	f2e43423          	sd	a4,-216(s0)
ffffffe0002017cc:	0007a783          	lw	a5,0(a5)
ffffffe0002017d0:	f6f40fa3          	sb	a5,-129(s0)
                    putch(ch);
ffffffe0002017d4:	f7f44703          	lbu	a4,-129(s0)
ffffffe0002017d8:	f3843783          	ld	a5,-200(s0)
ffffffe0002017dc:	00070513          	mv	a0,a4
ffffffe0002017e0:	000780e7          	jalr	a5
                    pos++;
ffffffe0002017e4:	fe043783          	ld	a5,-32(s0)
ffffffe0002017e8:	00178793          	addi	a5,a5,1
ffffffe0002017ec:	fef43023          	sd	a5,-32(s0)
                    longarg = 0; in_format = 0; 
ffffffe0002017f0:	fe042423          	sw	zero,-24(s0)
ffffffe0002017f4:	fe042623          	sw	zero,-20(s0)
                    break;
ffffffe0002017f8:	04c0006f          	j	ffffffe000201844 <vprintfmt+0x4f8>
                }
                default:
                    break;
            }
        }
        else if(*fmt == '%') {
ffffffe0002017fc:	f3043783          	ld	a5,-208(s0)
ffffffe000201800:	0007c783          	lbu	a5,0(a5)
ffffffe000201804:	00078713          	mv	a4,a5
ffffffe000201808:	02500793          	li	a5,37
ffffffe00020180c:	00f71863          	bne	a4,a5,ffffffe00020181c <vprintfmt+0x4d0>
          in_format = 1;
ffffffe000201810:	00100793          	li	a5,1
ffffffe000201814:	fef42623          	sw	a5,-20(s0)
ffffffe000201818:	02c0006f          	j	ffffffe000201844 <vprintfmt+0x4f8>
        }
        else {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
            putch(*fmt);
ffffffe00020181c:	f3043783          	ld	a5,-208(s0)
ffffffe000201820:	0007c703          	lbu	a4,0(a5)
ffffffe000201824:	f3843783          	ld	a5,-200(s0)
ffffffe000201828:	00070513          	mv	a0,a4
ffffffe00020182c:	000780e7          	jalr	a5
            pos++;
ffffffe000201830:	fe043783          	ld	a5,-32(s0)
ffffffe000201834:	00178793          	addi	a5,a5,1
ffffffe000201838:	fef43023          	sd	a5,-32(s0)
ffffffe00020183c:	0080006f          	j	ffffffe000201844 <vprintfmt+0x4f8>
                    break;
ffffffe000201840:	00000013          	nop
    for( ; *fmt; fmt++) {
ffffffe000201844:	f3043783          	ld	a5,-208(s0)
ffffffe000201848:	00178793          	addi	a5,a5,1
ffffffe00020184c:	f2f43823          	sd	a5,-208(s0)
ffffffe000201850:	f3043783          	ld	a5,-208(s0)
ffffffe000201854:	0007c783          	lbu	a5,0(a5)
ffffffe000201858:	b20790e3          	bnez	a5,ffffffe000201378 <vprintfmt+0x2c>
        }
    }
    return pos;
ffffffe00020185c:	fe043783          	ld	a5,-32(s0)
ffffffe000201860:	0007879b          	sext.w	a5,a5
}
ffffffe000201864:	00078513          	mv	a0,a5
ffffffe000201868:	0d813083          	ld	ra,216(sp)
ffffffe00020186c:	0d013403          	ld	s0,208(sp)
ffffffe000201870:	0e010113          	addi	sp,sp,224
ffffffe000201874:	00008067          	ret

ffffffe000201878 <printk>:



int printk(const char* s, ...) {
ffffffe000201878:	f9010113          	addi	sp,sp,-112
ffffffe00020187c:	02113423          	sd	ra,40(sp)
ffffffe000201880:	02813023          	sd	s0,32(sp)
ffffffe000201884:	03010413          	addi	s0,sp,48
ffffffe000201888:	fca43c23          	sd	a0,-40(s0)
ffffffe00020188c:	00b43423          	sd	a1,8(s0)
ffffffe000201890:	00c43823          	sd	a2,16(s0)
ffffffe000201894:	00d43c23          	sd	a3,24(s0)
ffffffe000201898:	02e43023          	sd	a4,32(s0)
ffffffe00020189c:	02f43423          	sd	a5,40(s0)
ffffffe0002018a0:	03043823          	sd	a6,48(s0)
ffffffe0002018a4:	03143c23          	sd	a7,56(s0)
    int res = 0;
ffffffe0002018a8:	fe042623          	sw	zero,-20(s0)
    va_list vl;
    va_start(vl, s);
ffffffe0002018ac:	04040793          	addi	a5,s0,64
ffffffe0002018b0:	fcf43823          	sd	a5,-48(s0)
ffffffe0002018b4:	fd043783          	ld	a5,-48(s0)
ffffffe0002018b8:	fc878793          	addi	a5,a5,-56
ffffffe0002018bc:	fef43023          	sd	a5,-32(s0)
    res = vprintfmt(putc, s, vl);
ffffffe0002018c0:	fe043783          	ld	a5,-32(s0)
ffffffe0002018c4:	00078613          	mv	a2,a5
ffffffe0002018c8:	fd843583          	ld	a1,-40(s0)
ffffffe0002018cc:	00000517          	auipc	a0,0x0
ffffffe0002018d0:	a3050513          	addi	a0,a0,-1488 # ffffffe0002012fc <putc>
ffffffe0002018d4:	a79ff0ef          	jal	ra,ffffffe00020134c <vprintfmt>
ffffffe0002018d8:	00050793          	mv	a5,a0
ffffffe0002018dc:	fef42623          	sw	a5,-20(s0)
    va_end(vl);
    return res;
ffffffe0002018e0:	fec42783          	lw	a5,-20(s0)
}
ffffffe0002018e4:	00078513          	mv	a0,a5
ffffffe0002018e8:	02813083          	ld	ra,40(sp)
ffffffe0002018ec:	02013403          	ld	s0,32(sp)
ffffffe0002018f0:	07010113          	addi	sp,sp,112
ffffffe0002018f4:	00008067          	ret

ffffffe0002018f8 <rand>:

int initialize = 0;
int r[1000];
int t = 0;

uint64 rand() {
ffffffe0002018f8:	fe010113          	addi	sp,sp,-32
ffffffe0002018fc:	00813c23          	sd	s0,24(sp)
ffffffe000201900:	02010413          	addi	s0,sp,32
    int i;

    if (initialize == 0) {
ffffffe000201904:	00002797          	auipc	a5,0x2
ffffffe000201908:	71478793          	addi	a5,a5,1812 # ffffffe000204018 <initialize>
ffffffe00020190c:	0007a783          	lw	a5,0(a5)
ffffffe000201910:	1e079463          	bnez	a5,ffffffe000201af8 <rand+0x200>
        r[0] = SEED;
ffffffe000201914:	00006797          	auipc	a5,0x6
ffffffe000201918:	6ec78793          	addi	a5,a5,1772 # ffffffe000208000 <r>
ffffffe00020191c:	00d00713          	li	a4,13
ffffffe000201920:	00e7a023          	sw	a4,0(a5)
        for (i = 1; i < 31; i++) {
ffffffe000201924:	00100793          	li	a5,1
ffffffe000201928:	fef42623          	sw	a5,-20(s0)
ffffffe00020192c:	0c40006f          	j	ffffffe0002019f0 <rand+0xf8>
            r[i] = (16807LL * r[i - 1]) % 2147483647;
ffffffe000201930:	fec42783          	lw	a5,-20(s0)
ffffffe000201934:	fff7879b          	addiw	a5,a5,-1
ffffffe000201938:	0007879b          	sext.w	a5,a5
ffffffe00020193c:	00006717          	auipc	a4,0x6
ffffffe000201940:	6c470713          	addi	a4,a4,1732 # ffffffe000208000 <r>
ffffffe000201944:	00279793          	slli	a5,a5,0x2
ffffffe000201948:	00f707b3          	add	a5,a4,a5
ffffffe00020194c:	0007a783          	lw	a5,0(a5)
ffffffe000201950:	00078713          	mv	a4,a5
ffffffe000201954:	000047b7          	lui	a5,0x4
ffffffe000201958:	1a778793          	addi	a5,a5,423 # 41a7 <_skernel-0xffffffe0001fbe59>
ffffffe00020195c:	02f70733          	mul	a4,a4,a5
ffffffe000201960:	800007b7          	lui	a5,0x80000
ffffffe000201964:	fff7c793          	not	a5,a5
ffffffe000201968:	02f767b3          	rem	a5,a4,a5
ffffffe00020196c:	0007871b          	sext.w	a4,a5
ffffffe000201970:	00006697          	auipc	a3,0x6
ffffffe000201974:	69068693          	addi	a3,a3,1680 # ffffffe000208000 <r>
ffffffe000201978:	fec42783          	lw	a5,-20(s0)
ffffffe00020197c:	00279793          	slli	a5,a5,0x2
ffffffe000201980:	00f687b3          	add	a5,a3,a5
ffffffe000201984:	00e7a023          	sw	a4,0(a5) # ffffffff80000000 <_ekernel+0x1f7fdf7000>
            if (r[i] < 0) {
ffffffe000201988:	00006717          	auipc	a4,0x6
ffffffe00020198c:	67870713          	addi	a4,a4,1656 # ffffffe000208000 <r>
ffffffe000201990:	fec42783          	lw	a5,-20(s0)
ffffffe000201994:	00279793          	slli	a5,a5,0x2
ffffffe000201998:	00f707b3          	add	a5,a4,a5
ffffffe00020199c:	0007a783          	lw	a5,0(a5)
ffffffe0002019a0:	0407d263          	bgez	a5,ffffffe0002019e4 <rand+0xec>
                r[i] += 2147483647;
ffffffe0002019a4:	00006717          	auipc	a4,0x6
ffffffe0002019a8:	65c70713          	addi	a4,a4,1628 # ffffffe000208000 <r>
ffffffe0002019ac:	fec42783          	lw	a5,-20(s0)
ffffffe0002019b0:	00279793          	slli	a5,a5,0x2
ffffffe0002019b4:	00f707b3          	add	a5,a4,a5
ffffffe0002019b8:	0007a703          	lw	a4,0(a5)
ffffffe0002019bc:	800007b7          	lui	a5,0x80000
ffffffe0002019c0:	fff7c793          	not	a5,a5
ffffffe0002019c4:	00f707bb          	addw	a5,a4,a5
ffffffe0002019c8:	0007871b          	sext.w	a4,a5
ffffffe0002019cc:	00006697          	auipc	a3,0x6
ffffffe0002019d0:	63468693          	addi	a3,a3,1588 # ffffffe000208000 <r>
ffffffe0002019d4:	fec42783          	lw	a5,-20(s0)
ffffffe0002019d8:	00279793          	slli	a5,a5,0x2
ffffffe0002019dc:	00f687b3          	add	a5,a3,a5
ffffffe0002019e0:	00e7a023          	sw	a4,0(a5) # ffffffff80000000 <_ekernel+0x1f7fdf7000>
        for (i = 1; i < 31; i++) {
ffffffe0002019e4:	fec42783          	lw	a5,-20(s0)
ffffffe0002019e8:	0017879b          	addiw	a5,a5,1
ffffffe0002019ec:	fef42623          	sw	a5,-20(s0)
ffffffe0002019f0:	fec42783          	lw	a5,-20(s0)
ffffffe0002019f4:	0007871b          	sext.w	a4,a5
ffffffe0002019f8:	01e00793          	li	a5,30
ffffffe0002019fc:	f2e7dae3          	bge	a5,a4,ffffffe000201930 <rand+0x38>
            }
        }
        for (i = 31; i < 34; i++) {
ffffffe000201a00:	01f00793          	li	a5,31
ffffffe000201a04:	fef42623          	sw	a5,-20(s0)
ffffffe000201a08:	0480006f          	j	ffffffe000201a50 <rand+0x158>
            r[i] = r[i - 31];
ffffffe000201a0c:	fec42783          	lw	a5,-20(s0)
ffffffe000201a10:	fe17879b          	addiw	a5,a5,-31
ffffffe000201a14:	0007879b          	sext.w	a5,a5
ffffffe000201a18:	00006717          	auipc	a4,0x6
ffffffe000201a1c:	5e870713          	addi	a4,a4,1512 # ffffffe000208000 <r>
ffffffe000201a20:	00279793          	slli	a5,a5,0x2
ffffffe000201a24:	00f707b3          	add	a5,a4,a5
ffffffe000201a28:	0007a703          	lw	a4,0(a5)
ffffffe000201a2c:	00006697          	auipc	a3,0x6
ffffffe000201a30:	5d468693          	addi	a3,a3,1492 # ffffffe000208000 <r>
ffffffe000201a34:	fec42783          	lw	a5,-20(s0)
ffffffe000201a38:	00279793          	slli	a5,a5,0x2
ffffffe000201a3c:	00f687b3          	add	a5,a3,a5
ffffffe000201a40:	00e7a023          	sw	a4,0(a5)
        for (i = 31; i < 34; i++) {
ffffffe000201a44:	fec42783          	lw	a5,-20(s0)
ffffffe000201a48:	0017879b          	addiw	a5,a5,1
ffffffe000201a4c:	fef42623          	sw	a5,-20(s0)
ffffffe000201a50:	fec42783          	lw	a5,-20(s0)
ffffffe000201a54:	0007871b          	sext.w	a4,a5
ffffffe000201a58:	02100793          	li	a5,33
ffffffe000201a5c:	fae7d8e3          	bge	a5,a4,ffffffe000201a0c <rand+0x114>
        }
        for (i = 34; i < 344; i++) {
ffffffe000201a60:	02200793          	li	a5,34
ffffffe000201a64:	fef42623          	sw	a5,-20(s0)
ffffffe000201a68:	0700006f          	j	ffffffe000201ad8 <rand+0x1e0>
            r[i] = r[i - 31] + r[i - 3];
ffffffe000201a6c:	fec42783          	lw	a5,-20(s0)
ffffffe000201a70:	fe17879b          	addiw	a5,a5,-31
ffffffe000201a74:	0007879b          	sext.w	a5,a5
ffffffe000201a78:	00006717          	auipc	a4,0x6
ffffffe000201a7c:	58870713          	addi	a4,a4,1416 # ffffffe000208000 <r>
ffffffe000201a80:	00279793          	slli	a5,a5,0x2
ffffffe000201a84:	00f707b3          	add	a5,a4,a5
ffffffe000201a88:	0007a703          	lw	a4,0(a5)
ffffffe000201a8c:	fec42783          	lw	a5,-20(s0)
ffffffe000201a90:	ffd7879b          	addiw	a5,a5,-3
ffffffe000201a94:	0007879b          	sext.w	a5,a5
ffffffe000201a98:	00006697          	auipc	a3,0x6
ffffffe000201a9c:	56868693          	addi	a3,a3,1384 # ffffffe000208000 <r>
ffffffe000201aa0:	00279793          	slli	a5,a5,0x2
ffffffe000201aa4:	00f687b3          	add	a5,a3,a5
ffffffe000201aa8:	0007a783          	lw	a5,0(a5)
ffffffe000201aac:	00f707bb          	addw	a5,a4,a5
ffffffe000201ab0:	0007871b          	sext.w	a4,a5
ffffffe000201ab4:	00006697          	auipc	a3,0x6
ffffffe000201ab8:	54c68693          	addi	a3,a3,1356 # ffffffe000208000 <r>
ffffffe000201abc:	fec42783          	lw	a5,-20(s0)
ffffffe000201ac0:	00279793          	slli	a5,a5,0x2
ffffffe000201ac4:	00f687b3          	add	a5,a3,a5
ffffffe000201ac8:	00e7a023          	sw	a4,0(a5)
        for (i = 34; i < 344; i++) {
ffffffe000201acc:	fec42783          	lw	a5,-20(s0)
ffffffe000201ad0:	0017879b          	addiw	a5,a5,1
ffffffe000201ad4:	fef42623          	sw	a5,-20(s0)
ffffffe000201ad8:	fec42783          	lw	a5,-20(s0)
ffffffe000201adc:	0007871b          	sext.w	a4,a5
ffffffe000201ae0:	15700793          	li	a5,343
ffffffe000201ae4:	f8e7d4e3          	bge	a5,a4,ffffffe000201a6c <rand+0x174>
        }

		initialize = 1;
ffffffe000201ae8:	00002797          	auipc	a5,0x2
ffffffe000201aec:	53078793          	addi	a5,a5,1328 # ffffffe000204018 <initialize>
ffffffe000201af0:	00100713          	li	a4,1
ffffffe000201af4:	00e7a023          	sw	a4,0(a5)
    }

	t = t % 656;
ffffffe000201af8:	00002797          	auipc	a5,0x2
ffffffe000201afc:	52478793          	addi	a5,a5,1316 # ffffffe00020401c <t>
ffffffe000201b00:	0007a783          	lw	a5,0(a5)
ffffffe000201b04:	00078713          	mv	a4,a5
ffffffe000201b08:	29000793          	li	a5,656
ffffffe000201b0c:	02f767bb          	remw	a5,a4,a5
ffffffe000201b10:	0007871b          	sext.w	a4,a5
ffffffe000201b14:	00002797          	auipc	a5,0x2
ffffffe000201b18:	50878793          	addi	a5,a5,1288 # ffffffe00020401c <t>
ffffffe000201b1c:	00e7a023          	sw	a4,0(a5)

    r[t + 344] = r[t + 344 - 31] + r[t + 344 - 3];
ffffffe000201b20:	00002797          	auipc	a5,0x2
ffffffe000201b24:	4fc78793          	addi	a5,a5,1276 # ffffffe00020401c <t>
ffffffe000201b28:	0007a783          	lw	a5,0(a5)
ffffffe000201b2c:	1397879b          	addiw	a5,a5,313
ffffffe000201b30:	0007879b          	sext.w	a5,a5
ffffffe000201b34:	00006717          	auipc	a4,0x6
ffffffe000201b38:	4cc70713          	addi	a4,a4,1228 # ffffffe000208000 <r>
ffffffe000201b3c:	00279793          	slli	a5,a5,0x2
ffffffe000201b40:	00f707b3          	add	a5,a4,a5
ffffffe000201b44:	0007a683          	lw	a3,0(a5)
ffffffe000201b48:	00002797          	auipc	a5,0x2
ffffffe000201b4c:	4d478793          	addi	a5,a5,1236 # ffffffe00020401c <t>
ffffffe000201b50:	0007a783          	lw	a5,0(a5)
ffffffe000201b54:	1557879b          	addiw	a5,a5,341
ffffffe000201b58:	0007879b          	sext.w	a5,a5
ffffffe000201b5c:	00006717          	auipc	a4,0x6
ffffffe000201b60:	4a470713          	addi	a4,a4,1188 # ffffffe000208000 <r>
ffffffe000201b64:	00279793          	slli	a5,a5,0x2
ffffffe000201b68:	00f707b3          	add	a5,a4,a5
ffffffe000201b6c:	0007a703          	lw	a4,0(a5)
ffffffe000201b70:	00002797          	auipc	a5,0x2
ffffffe000201b74:	4ac78793          	addi	a5,a5,1196 # ffffffe00020401c <t>
ffffffe000201b78:	0007a783          	lw	a5,0(a5)
ffffffe000201b7c:	1587879b          	addiw	a5,a5,344
ffffffe000201b80:	0007879b          	sext.w	a5,a5
ffffffe000201b84:	00e6873b          	addw	a4,a3,a4
ffffffe000201b88:	0007071b          	sext.w	a4,a4
ffffffe000201b8c:	00006697          	auipc	a3,0x6
ffffffe000201b90:	47468693          	addi	a3,a3,1140 # ffffffe000208000 <r>
ffffffe000201b94:	00279793          	slli	a5,a5,0x2
ffffffe000201b98:	00f687b3          	add	a5,a3,a5
ffffffe000201b9c:	00e7a023          	sw	a4,0(a5)
    
	t++;
ffffffe000201ba0:	00002797          	auipc	a5,0x2
ffffffe000201ba4:	47c78793          	addi	a5,a5,1148 # ffffffe00020401c <t>
ffffffe000201ba8:	0007a783          	lw	a5,0(a5)
ffffffe000201bac:	0017879b          	addiw	a5,a5,1
ffffffe000201bb0:	0007871b          	sext.w	a4,a5
ffffffe000201bb4:	00002797          	auipc	a5,0x2
ffffffe000201bb8:	46878793          	addi	a5,a5,1128 # ffffffe00020401c <t>
ffffffe000201bbc:	00e7a023          	sw	a4,0(a5)

    return (uint64)r[t - 1 + 344];
ffffffe000201bc0:	00002797          	auipc	a5,0x2
ffffffe000201bc4:	45c78793          	addi	a5,a5,1116 # ffffffe00020401c <t>
ffffffe000201bc8:	0007a783          	lw	a5,0(a5)
ffffffe000201bcc:	1577879b          	addiw	a5,a5,343
ffffffe000201bd0:	0007879b          	sext.w	a5,a5
ffffffe000201bd4:	00006717          	auipc	a4,0x6
ffffffe000201bd8:	42c70713          	addi	a4,a4,1068 # ffffffe000208000 <r>
ffffffe000201bdc:	00279793          	slli	a5,a5,0x2
ffffffe000201be0:	00f707b3          	add	a5,a4,a5
ffffffe000201be4:	0007a783          	lw	a5,0(a5)
}
ffffffe000201be8:	00078513          	mv	a0,a5
ffffffe000201bec:	01813403          	ld	s0,24(sp)
ffffffe000201bf0:	02010113          	addi	sp,sp,32
ffffffe000201bf4:	00008067          	ret

ffffffe000201bf8 <memset>:
#include "string.h"

void *memset(void *dst, int c, uint64 n) {
ffffffe000201bf8:	fc010113          	addi	sp,sp,-64
ffffffe000201bfc:	02813c23          	sd	s0,56(sp)
ffffffe000201c00:	04010413          	addi	s0,sp,64
ffffffe000201c04:	fca43c23          	sd	a0,-40(s0)
ffffffe000201c08:	00058793          	mv	a5,a1
ffffffe000201c0c:	fcc43423          	sd	a2,-56(s0)
ffffffe000201c10:	fcf42a23          	sw	a5,-44(s0)
    char *cdst = (char *)dst;
ffffffe000201c14:	fd843783          	ld	a5,-40(s0)
ffffffe000201c18:	fef43023          	sd	a5,-32(s0)
    for (uint64 i = 0; i < n; ++i)
ffffffe000201c1c:	fe043423          	sd	zero,-24(s0)
ffffffe000201c20:	0280006f          	j	ffffffe000201c48 <memset+0x50>
        cdst[i] = c;
ffffffe000201c24:	fe043703          	ld	a4,-32(s0)
ffffffe000201c28:	fe843783          	ld	a5,-24(s0)
ffffffe000201c2c:	00f707b3          	add	a5,a4,a5
ffffffe000201c30:	fd442703          	lw	a4,-44(s0)
ffffffe000201c34:	0ff77713          	zext.b	a4,a4
ffffffe000201c38:	00e78023          	sb	a4,0(a5)
    for (uint64 i = 0; i < n; ++i)
ffffffe000201c3c:	fe843783          	ld	a5,-24(s0)
ffffffe000201c40:	00178793          	addi	a5,a5,1
ffffffe000201c44:	fef43423          	sd	a5,-24(s0)
ffffffe000201c48:	fe843703          	ld	a4,-24(s0)
ffffffe000201c4c:	fc843783          	ld	a5,-56(s0)
ffffffe000201c50:	fcf76ae3          	bltu	a4,a5,ffffffe000201c24 <memset+0x2c>

    return dst;
ffffffe000201c54:	fd843783          	ld	a5,-40(s0)
}
ffffffe000201c58:	00078513          	mv	a0,a5
ffffffe000201c5c:	03813403          	ld	s0,56(sp)
ffffffe000201c60:	04010113          	addi	sp,sp,64
ffffffe000201c64:	00008067          	ret

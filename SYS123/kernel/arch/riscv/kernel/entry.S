    .extern trap_handler
    .extern dummy
    .section .text.entry
    .align 2
    .globl _traps 
    .global __dummy
    .globl __switch_to

__switch_to:
    # save state to prev process
    # YOUR CODE HERE
    sd ra, 40(a0)
    sd sp, 48(a0)
    sd s0, 56(a0)
    sd s1, 64(a0)
    sd s2, 72(a0)
    sd s3, 80(a0)
    sd s4, 88(a0)
    sd s5, 96(a0)
    sd s6, 104(a0)
    sd s7, 112(a0)
    sd s8, 120(a0)
    sd s9, 128(a0)
    sd s10, 136(a0)
    sd s11, 144(a0)
    # restore state from next process
    # YOUR CODE HERE
    ld ra, 40(a1)
    ld sp, 48(a1)
    ld s0, 56(a1)
    ld s1, 64(a1)
    ld s2, 72(a1)
    ld s3, 80(a1)
    ld s4, 88(a1)
    ld s5, 96(a1)
    ld s6, 104(a1)
    ld s7, 112(a1)
    ld s8, 120(a1)
    ld s9, 128(a1)
    ld s10, 136(a1)
    ld s11, 144(a1)
    ret

__dummy:
    # YOUR CODE HERE
    la t0, dummy
    csrw sepc, t0
    sret

_traps:

    # 1. save 32 registers and sepc to stack
    sd sp, -8(sp)

    sd ra, -16(sp)
    sd gp, -24(sp)
    sd tp, -32(sp)
    sd t0, -40(sp)
    sd t1, -48(sp)
    sd t2, -56(sp)
    sd t3, -64(sp)
    sd t4, -72(sp)
    sd t5, -80(sp)
    sd t6, -88(sp)
    sd fp, -96(sp)
    sd s1, -104(sp)
    sd a0, -112(sp)
    sd a1, -120(sp)
    sd a2, -128(sp)
    sd a3, -136(sp)
    sd a4, -144(sp)
    sd a5, -152(sp)
    sd a6, -160(sp)
    sd a7, -168(sp)
    sd s2, -176(sp)
    sd s3, -184(sp)
    sd s4, -192(sp)
    sd s5, -200(sp)
    sd s6, -208(sp)
    sd s7, -216(sp)
    sd s8, -224(sp)
    sd s9, -232(sp)
    sd s10, -240(sp)
    sd s11, -248(sp)

    csrr a0, sepc
    sd a0, -256(sp)
    addi sp, sp, -256
    # -----------
    # 2. call trap_handler
    csrr a0, scause
    csrr a1, sepc
    call trap_handler
    # -----------
    # 3. restore sepc and 32 registers (x2(sp) should be restore last) from stack
    ld a0, 0(sp)    #===
    
    li t1, 0x8000000000000005
    csrr t0, scause
    beq t0, t1, _csrwrite
    addi a0, a0, 4
_csrwrite:
    csrw sepc, a0   #===

    ld s11, 8(sp)
    ld s10, 16(sp)
    ld s9, 24(sp)
    ld s8, 32(sp)
    ld s7, 40(sp)
    ld s6, 48(sp)
    ld s5, 56(sp)
    ld s4, 64(sp)
    ld s3, 72(sp)
    ld s2, 80(sp)
    ld a7, 88(sp)
    ld a6, 96(sp)
    ld a5, 104(sp)
    ld a4, 112(sp)
    ld a3, 120(sp)
    ld a2, 128(sp)
    ld a1, 136(sp)
    ld a0, 144(sp)
    ld s1, 152(sp)
    ld fp, 160(sp)
    ld t6, 168(sp)
    ld t5, 176(sp)
    ld t4, 184(sp)
    ld t3, 192(sp)
    ld t2, 200(sp)
    ld t1, 208(sp)
    ld t0, 216(sp)
    ld tp, 224(sp)
    ld gp, 232(sp)
    ld ra, 240(sp)
    ld sp, 248(sp)
    # -----------
    # 4. return from trap
    sret
    # -----------
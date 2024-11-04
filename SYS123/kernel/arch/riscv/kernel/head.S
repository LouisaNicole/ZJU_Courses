.extern start_kernel

.section .text.init
.globl _start
.globl _end
_start:
  la sp, boot_stack_top

  call setup_vm
  call relocate

  la t0, _traps
  csrw stvec, t0
  csrr t0, sie
  ori t0, t0, 0x20
  csrw sie, t0
  
  rdtime a0
  li t0, 10000000
  add a0, a0, t0

  xor a7, a7, a7
  xor a6, a6, a6
  xor a5, a5, a5
  xor a4, a4, a4
  xor a3, a3, a3
  xor a2, a2, a2
  xor a1, a1, a1
  ecall

  csrr t0, sstatus
  ori t0, t0, 1<<1
  csrw sstatus, t0

  call mm_init
  call setup_vm_final
  call task_init

  # li a0, 2022
  # j _srodata
  j start_kernel

relocate:
    # set ra = ra + PA2VA_OFFSET
    # set sp = sp + PA2VA_OFFSET (If you have set the sp before)
    li t0, 0xffffffdf80000000
    add ra, ra, t0
    add sp, sp, t0

    # la t0, _trap_vm
    # csrw stvec, t0

    # set satp with early_pgtbl
    li t1, 1
    slli t1, t1, 63
    la t2, early_pgtbl
    srli t2, t2, 12
    or t1, t1, t2
    csrw satp, t1

    # flush tlb
    sfence.vma zero, zero

    # flush icache
    fence.i

    ret

# _trap_vm:
#   csrr t1, sepc
#   li t0, 0xffffffdf80000000
#   addi t0, t0, 4
#   add t0, t0, t1
#   csrw sepc, t0
#   sret


.section .bss
  .space 0x1000

boot_stack_top:
.align 4
_end:

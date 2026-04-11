.global _start

.section .text
.align 2

_start:
    la sp, _stack_end

    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop

    la t0, _data_load
    la t1, _data_start
    la t2, _data_end
  
COPY_DATA_LOOP:
    bgeu t1, t2, COPY_DATA_END
    lw a4, 0(t0)
    sw a4, 0(t1)
    addi t0, t0, 4
    addi t1, t1, 4
    j COPY_DATA_LOOP
COPY_DATA_END:

    la t0, _bss_start
    la t1, _bss_end
CLEAR_BSS_LOOP:
    bgeu t0, t1, CLEAR_BSS_END
    sw zero, 0(t0)
    addi t0, t0, 4
    j CLEAR_BSS_LOOP
CLEAR_BSS_END:

    li a0, 0
    li a1, 0
    call main

_endless_loop:
  j     _endless_loop
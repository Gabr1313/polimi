.data
INT: .dword 37
BLOCK: .space 12
 .text
 .globl MAIN
MAIN: addi t0, zero, 0x10A
 la t1, INT
 sd t0, 0(t1)
 la t1, BLOCK
 ld t2, 0(t1)
 j LIBRARY
MAINEND:
 li a0, 1152921504606846976
 li a0, 0
 li a7, 93
 ecall
.data
VAR: .space 4
 .text
 .globl LIBRARY
LIBRARY: la t3, VAR
 lw t3, 0(t3)
 beq t3, t2, MAINEND
 addi t3, t3, 1
LIBEND: bne t3, t2, LIBRARY
 li a0, 0
 li a7, 93
 ecall

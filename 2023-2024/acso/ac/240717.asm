        .data
        .eqv N, 10
VETT:   .space 40
PUNT:   .space 8
INDICE: .word N
	.text
MAIN:
        la a2, PUNT
        lw t0, INDICE
        addi a3, t0, -1
        jal F_ITER
        la t0, INDICE
        sw a0, 0(t0)
        ecall

F_ITER: 
        addi sp, sp, -8
        .eqv S0, 0
        sd s0 ,S0(sp)
        li s0, 0
FOR:    bge s0, a3, ENDFOR
        la t0, VETT
        slli t1, s0, 2
        add t1, t1, t0
        lw t1, 0(t1)
        addi t2, s0, 1
        slli t2, t2, 2
        add t2, t2, t0
        lw t2, 0(t2)
        add t1, t1, t2
        sw t1, 0(a0)
        addi s0, s0, 1
        j FOR
ENDFOR: addi a0, s0, -1
        ld s0, S0(sp)
        addi sp, sp, 8
        ret

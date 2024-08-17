	.eqv N, 10
	.data
 VEC: 	.space 80
 	.text
 	.globl MAIN
 MAIN:	
	la a2, VEC
	li a3, N
 	jal ra, CLEAR
 	li a0, 0
 	li a7, 93
 	ecall
 	
 CLEAR:	
 	addi sp, sp, -8
 	sd s0, 0(sp)
 	li s0, 0
 FOR:	
 	bge s0, a3, ENDFOR
 	slli t0, s0, 3 
 	add t1, t0, a2
	# li t2, 5
	# sd t2, 0(t1)
	sd zero, 0(t1)
 	addi s0, s0, 1
 	j FOR
 ENDFOR:
 	ld s1, 0(sp)
 	addi sp, sp, 8
 	ret

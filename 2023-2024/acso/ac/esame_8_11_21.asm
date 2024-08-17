	.data
BUF: .	space 56
	.text
	.globl MAIN
MAIN: 	mv a2, zero
	la t0, SUM
	ld a3, 0(t0)
	jal AUX
	bne a0, zero, MAIN
	mv t1, a0
	addi t1, t1, 1
	la t0, BUF
	sd t1, 0(t0)
	j MAIN
	
	.data
	.eqv CONST, 5
SUM: 	.dword 20
	.text
	.globl AUX
AUX: 	beq a2, a3, SKIP
	ret
SKIP: 	addi a2, a2, CONST
	la t0, BUF
	sd a2, 0(t0)
	ret

	.text
	.globl MAIN
MAIN:
	li a2, 7 #b
	li a3, 5 #e
	jal POW
	mv a0, a0,
	li a7, 1
	ecall
	li a0, 0
	li a7, 93
	ecall
POW:
	addi s0, zero, 1 #ans
	addi s1, zero, 1 #i
FOR:	bgt s1, a3, ENDFOR
IF:	and t0, a3, s1
	beq zero, t0, ENDIF
	mul s0, s0, a2
ENDIF:  mul a2, a2, a2
	slli s1, s1, 1
	jal zero, FOR
ENDFOR: mv a0, s0
	ret
	
	
	

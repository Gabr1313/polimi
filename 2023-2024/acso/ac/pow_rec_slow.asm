.text
MAIN: 
	# a2 - a7 e' dove metto i parametri che passo a funzione
	li a2, 2 #addi a2, zero, 2
	li a3, 5
	jal  POTENZA #jal ra, POTENZA
	# print a0
	li a7, 1
	ecall
	# return 0
	li a0, 0
	li a7, 93
	ecall
POTENZA: 
	# salvo ra sullo stack
	addi sp, sp, -8
	sd ra, 0(sp)
IF:	
	bne a3, zero, ELSE
	li a0, 1
	j EXIT
ELSE:
	addi sp, sp, -8
	sd a2, 0(sp)
	addi a3, a3, -1
	jal POTENZA
	ld a2, 0(sp)
	addi sp, sp, 8
	mul a0, a2, a0
EXIT: 
	ld ra, 0(sp)
	addi sp, sp, 8
	ret
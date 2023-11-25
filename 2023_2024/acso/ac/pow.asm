.text
.global MAIN
MAIN:
li a2, 2
li a3, 5
# per stampare a schermo il contenuto di a0
jal POTENZA
mv a0, a0,
li a7, 1
ecall
# per terminare l’esecuzione tramite exit
li a0, 0
li a7, 93
ecall
POTENZA:
addi sp, sp, -8
sd ra, 0(sp)
bnez a3, ELSE
li a0, 1
j EXIT
ELSE:
addi sp, sp, -8
sd a2, 0(sp)
addi a3, a3, -1
jal POTENZA
ld a2, 0(sp)
addi sp, sp, 8
mul a0, a0, a2
EXIT:
ld ra, 0(sp)
addi sp, sp, 8
jr ra

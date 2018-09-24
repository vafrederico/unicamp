cadeia:
	.ascii "uma cadeia de caracteres com espaco"

.skip 1

espaco:
	.ascii " "

main:
	mov r1, #cadeia
	mov r3, #espaco
	ldrb r3, [r3]
	mov r0, #0
nextChar:
	ldrb r4, [r1]
	cmp r4, r3
	addeq r0, #1
	cmp r4, #0x0
	addne r1, #1
	bne nextChar

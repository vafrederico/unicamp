main:
	mov r0, #100
	mov r1, #1
next:
	lsr r0, #1
	
	cmp r1, #0
	moveq r1, #1
	movne r1, #0

	cmp r0, #1
	bge next

	.end
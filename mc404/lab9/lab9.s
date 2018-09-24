@ modos de interrupção no registrador de status
.set IRQ_MODE,0x12
.set USER_MODE,0x10

@ flag para habilitar interrupções externas no registrador de status
.set IRQ, 0x80

@enderecos dispositivos
.set TIMER,   0x90008
.set LEDADDR,	  0x90000
@ constantes
.set MAXINTERVALOUT,2000
.set MAXINTERVALIN, 1000

@ vetor de interrupções
.org  7*4               @ preenche apenas uma posição do vetor,
                        @ correspondente ao tipo 6
b       tratador_timer


.org 0x1000

@ r4 = tempo do display
@ r5 = nivel atual
@ r6 = botao a ser pressionado
@ r7 = flag tick
@ r8 = botao pressionado
main:
	mov	sp,#0x400	@ seta pilha do modo supervisor
	mov	r0,#IRQ_MODE	@ coloca processador no modo IRQ (interrupção externa)
	msr	cpsr,r0		@ processador agora no modo IRQ
	mov	sp,#0x300	@ seta pilha de interrupção IRQ
	mov	r0,#USER_MODE	@ coloca processador no modo usuário
	bic     r0,r0,#IRQ      @ interrupções IRQ habilitadas
	msr	cpsr,r0		@ processador agora no modo usuário
	mov	sp,#0x10000	@ pilha do usuário no final da memória 
	mov r4, #MAXINTERVALOUT

	mov r5, #2
	mov r7, #1
	mov r3, #0

loopDisplay:
	cmp r7, #1 @ se r7 = 1, deu tick, logo, acabou o tempo de entrar com a sequencia
	bne loopDisplay
	
	cmp r3, r5
	beq loopUsuario

	@ zera led
	mov r0, #0
	mov r1, #LEDADDR
	str r0, [r1]
	
	mov r0, #sequencia
	ldrb r0, [r0,r3, lsl#2]
	
	str r0, [r1]
	add r3, #1

	ldr	r0,=TIMER
	str r4,[r0]	
	mov r7, #0
	
	b loopDisplay

	sub r4, #50
	
loopUsuario:
	cmp r7, #1 @ se r7 = 1, deu tick, logo, acabou o tempo de entrar com a sequencia
	beq gameOver
	cmp r8, #0 @ nenhum botao pressionado, volta ao loop
	beq loopUsuario
	cmp r8, r6
	bne gameOver @ botao errado pressionado

sequencia:
	.byte 0x8, 0x4, 0x2, 0x1

recorde:
 	.word 0

gameOver:
	ldr r1,=recorde
	str r5, [r1]
	b main

tratador_timer:
	mov r7, #1 @ seta flag do timer
	movs	pc,lr		@ e retorna

	.end

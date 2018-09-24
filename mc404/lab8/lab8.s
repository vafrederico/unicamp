@ entrada: endereço do vetor em r0, número de elementos no vetor em r1, valor a ser procurado em r2
@ saída: valor procurado em r0 e indíce do valor procurado no vetor em r5 caso achado, caso contrário, retorna -1 em r0
@ destrói: r0, r3, r4, r5, r6 e flags
buscaBinaria:
	mov r3, #0 @ r3 = esquerda
	sub r4, r1, #1 @ r4 = direita

loop:
	cmp r3, r4 @ esquerda <= direita? se n, não foi achado
	movgt r0, #-1
	bxgt lr

	add r5, r3, r4
	lsr r5, #1
	ldr r6, [r0, r5, lsl#2] @ carrega em r6 <--- r0 + r5*4

	cmp r6, r2
	subgt r4, r5, #1 @ maior => direita = meio - 1
	addlt r3, r5, #1 @ menor => esquerda = meio +1
	moveq r0, r2 @ achou => r0 = valor procurado
	bxeq lr @ retorna

	b loop @ roda novamente o loop

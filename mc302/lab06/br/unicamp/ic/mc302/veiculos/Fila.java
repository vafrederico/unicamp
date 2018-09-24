package br.unicamp.ic.mc302.veiculos;

import java.util.ArrayList;

public class Fila<E> {

	private ArrayList<E> aList = new ArrayList<E>();
	
	public boolean Vazia() {
		return aList.isEmpty();
	}
	
	public void adiciona(E item) {
		aList.add(item);
	}
	
	public void mostraFila() {
		for(E e: aList) {
			System.out.println(e);
		}
	}

}

package br.unicamp.ic.mc302.editor;

import java.util.ArrayList;

public class Figura {

	private ArrayList<Figura> lista = new ArrayList<Figura>();
	
	public void adiciona(Figura e){
		this.lista.add(e);
	}
	
	public void desenhar(){
		System.out.println("Grupo:");
		for( Figura elem : lista ){
			elem.desenhar();
		}
	}
}

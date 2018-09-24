package br.unicamp.ic.mc302.editor;
import java.util.ArrayList;

public class Tela {

	private ArrayList<Figura> lista = new ArrayList<Figura>();
	
	public void adiciona(Figura e){
		this.lista.add(e);
	}
	
	public void desenhar(){
		System.out.println("Polígono:");
		for( Figura elem : lista ){
			elem.desenhar();
		}
	}
	
}

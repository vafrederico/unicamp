package br.unicamp.ic.mc302.editor;
import java.util.ArrayList;
public class Poligono extends Figura{
	
	private ArrayList<Linha> linhas = new ArrayList<Linha>();
	
	public void adiciona(Linha linha){
		this.linhas.add(linha);
	}
	
	public void desenhar(){
		System.out.println("Polígono:");
		for( Linha linha : linhas ){
			linha.desenhar();
		}
	}
}

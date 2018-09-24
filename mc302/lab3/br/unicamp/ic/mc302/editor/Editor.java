package br.unicamp.ic.mc302.editor;

public class Editor {
	
	private Tela tela = new Tela();
	
	public void desenhar(){
		tela.desenhar();
	}

	public void adiciona(Figura e){
		tela.adiciona(e);
	}
}

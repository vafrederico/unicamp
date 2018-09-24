package br.unicamp.ic.mc302.documento;

public class Documento {
	private String autor;
	private int dataDeChegada;

	public void criarDocumento(String nome, int num) {
		autor = nome;
		dataDeChegada = num;
	}

	public void imprimir() {
		System.out.println("Imprime o conte�do de um Documento");
	}

	public void editar() {
		System.out.println("Edita o cont�udo de um Documento");
	}
}

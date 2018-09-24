package br.unicamp.ic.mc302.veiculos;

/**
 * T�tulo: Modulo 3
 * 
 * Classe Caminhao
 */

public class Caminhao extends Veiculo {
	private int capacidade;
	private int numDeEixos;

	public Caminhao(int cap, int num, int ano, String mar, String mod, String pl) {
		super(ano, mar, mod, pl);
		capacidade = cap;
		numDeEixos = num;
	}

	public void mostra() {
		System.out.println("\nTipo--->Caminhao");
		System.out.println("Capacidade = " + capacidade);
		System.out.println("Numero de Eixos = " + numDeEixos);
		super.mostra();
	}
}
package br.unicamp.ic.mc302.veiculos;

/**
 * Titulo: Modulo 3
 * 
 * Classe Carro
 */

public class Carro extends Veiculo {
	private int lotacao;
	private int numPortas;

	public Carro(int lot, int num, int ano, String mar, String mod, String pl) {
		super(ano, mar, mod, pl);
		lotacao = lot;
		numPortas = num;
	}

	private void mostra() {
		System.out.println("\nTipo-->Carro");
		System.out.println("Lota�� o= " + lotacao);
		System.out.println("Numero de Portas =" + numPortas);
		super.mostra();
	}
}
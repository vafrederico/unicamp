package br.unicamp.ic.mc302.veiculos;

public class Caminhao extends Carro {
	
	private int numEixos;
	private int capacidade;
	
	public Caminhao(int lot, int num, int ano, String mar, String mod, String pl, int numEixos, int capacidade){
		super(lot, num, ano, mar, mod, pl);
		this.numEixos = numEixos;
		this.capacidade = capacidade;
	}
	
	public int getNumEixos(){
		return this.numEixos;
	}
	
	public int getCapacidade(){
		return this.capacidade;
	}
}

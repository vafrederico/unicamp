package br.unicamp.ic.mc302.veiculos;

public class Caminhao extends Veiculo {
	private int capacidade;
	private int numDeEixos;

	public Caminhao(int cap, int num, int ano, String mar, String mod, String pl) {
		super(ano, mar, mod, pl);
		capacidade = cap;
		numDeEixos = num;
	}
	
	public boolean ligar(){
		
		System.out.println("O Caminhao foi ligado corretamente");
		return true;
	}

	public String toString(){
		return "\nTipo--->Caminhao" + "\nCapacidade = " + capacidade + "\nNumero de Eixos = " + numDeEixos;
	}
	
	public void mostra() {
		System.out.println("\nTipo--->Caminhao");
		System.out.println("Capacidade = " + capacidade);
		System.out.println("Numero de Eixos = " + numDeEixos);
		super.mostra();
	}
}
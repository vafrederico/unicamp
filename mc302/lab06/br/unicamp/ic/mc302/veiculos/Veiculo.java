package br.unicamp.ic.mc302.veiculos;

public abstract class Veiculo {
	private String marca;
	private String modelo;
	private String placa;
	private int anoModelo;

	public Veiculo(int ano, String mar, String mod, String pl) {
		marca = mar;
		modelo = mod;
		placa = pl;
		anoModelo = ano;
	}
	
	public abstract boolean ligar();
	
	public void mostra() {
		System.out.println("Marca = " + marca);
		System.out.println("Modelo = " + modelo);
		System.out.println("Placa = " + placa);
		System.out.println("Ano Modelo = " + anoModelo);
	}
	

}
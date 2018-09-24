package br.unicamp.ic.mc302.veiculos;

public class ExemploLigar {

	public static void main(String args[]) {
		Veiculo v1;

		v1 = new Carro(5, 4, 2003, "Fiat", "Palio", "CBH-1965");
		v1.ligar();

		v1 = new Caminhao(3000, 6, 2000, "Ford", "AlgumModeloDeCaminhao",
				"LH-1999");
		v1.ligar();
	}
}
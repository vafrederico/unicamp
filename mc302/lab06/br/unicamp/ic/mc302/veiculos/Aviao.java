package br.unicamp.ic.mc302.veiculos;

class Aviao extends Veiculo {

	private int carga;
	private int numTurbinas;
	private int lotacao;

	Aviao(int argCarga, int argNumTurbinas, int argLotacao, int ano, String mar, String mod,
			String pl) {
		super(ano, mar, mod, pl);
		carga = argCarga;
		numTurbinas = argNumTurbinas;
		lotacao = argLotacao;
	}

	public void mostra() {
		System.out.println("\nTipo-->Aviao");
		System.out.println("Num. de Turbinas = " + numTurbinas);
		System.out.println("Lotação = " + lotacao);
		System.out.println("Carga = " + carga);
		super.mostra();
	}

	public boolean ligar() {
		return false;
	}
}

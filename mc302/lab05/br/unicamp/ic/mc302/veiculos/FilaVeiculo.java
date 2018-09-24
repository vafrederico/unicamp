package br.unicamp.ic.mc302.veiculos;

/**
 * Titulo: Modulo 3
 * 
 * Classe FilaVeiculo
 */

public class FilaVeiculo {
	private Veiculo veiculos[];
	private boolean vazia = true;
	private int ultimaPosicao = 0;

	public FilaVeiculo() {
		veiculos = new Veiculo[50];
	}

	public boolean Vazia() {
		return vazia;
	}

	public void adicionaVeiculo(String tipo, int p1, int p2, int ano,
			String mar, String mod, String pla) {
		if (ultimaPosicao <= 50) {
			if (tipo.equalsIgnoreCase("Carro")) {
				veiculos[ultimaPosicao] = new Carro(p1, p2, ano, mar, mod, pla);
			} else {
				if (tipo.equals("Caminhao")) {
					veiculos[ultimaPosicao] = new Caminhao(p1, p2, ano, mar,
							mod, pla);
				} else {
					System.out.println("A Fila contém apenas Carro ou Caminhão\n");
				}
			}
		} else {
			System.out.println("O veiculo não poderá ser adicionado, pois a fila está cheia");
		}
		ultimaPosicao++;
		vazia = false;
	}

	public void mostraFila() {
		for (int i = 0; i < ultimaPosicao; i++) {
			veiculos[i].mostra();
		}
	}

}

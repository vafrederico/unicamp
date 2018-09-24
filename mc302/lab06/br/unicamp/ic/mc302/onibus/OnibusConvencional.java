package br.unicamp.ic.mc302.onibus;

public class OnibusConvencional extends Onibus{
	

	public OnibusConvencional(){
		super(10);
	}

	int totalValor(){
		int total = 0;
		for(int i = 0; i < tam; i++){
			if(i == 0 || i == 1)
				total = fileiras[i].qtdeOcupado()*15; // Valor diferenciado
			else
				total = fileiras[i].qtdeOcupado()*10; // Valor normal
		}
		return total;
	}
}

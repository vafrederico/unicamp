package br.unicamp.ic.mc302.onibus;

public class OnibusLeito extends Onibus{
	
	public OnibusLeito(){
		super(5);
	}
	
	int totalValor(){
		int total = 0;
		for(int i = 0; i < tam; i++){
			total = fileiras[i].qtdeOcupado()*10;
		}
		return total;
	}
}

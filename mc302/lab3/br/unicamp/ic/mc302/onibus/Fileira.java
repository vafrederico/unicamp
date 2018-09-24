package br.unicamp.ic.mc302.onibus;

public class Fileira {
	
	private Assento assentos[] = new Assento[4];

	public Fileira() {
		for(int i = 0; i < 4; i++)
			assentos[i] = new Assento();
	}
	
	private int getNum(char letra){
		int pos = 0; 
		if(letra == 'A')
			pos = 0;
		else if(letra == 'B')
			pos = 1;
		else if(letra == 'C')
			pos = 2;
		else if(letra == 'D')
			pos = 3;
		
		return pos;
	}
	public boolean ocupado(char letra){

		return assentos[getNum(letra)].ocupado();
	}
	
	public boolean possuiLugar(){
		for( Assento assento : assentos){
			if(assento.ocupado() == false)
				return true;
		}
		return false;
	}
	public void setOcupado(char letra){
		this.assentos[getNum(letra)].setOcupado();
	}
}

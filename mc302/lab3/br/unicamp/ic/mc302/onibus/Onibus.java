package br.unicamp.ic.mc302.onibus;

public class Onibus {
 
	private Fileira fileiras[] = new Fileira[10];
	
	public Onibus() {
		for(int i = 0; i < 10; i++)
			fileiras[i] = new Fileira();
	}
	
	private void desenhaLetra(char letra){
		
		for( Fileira fileira : fileiras){
			int a = fileira.ocupado(letra)? 1: 0;
			System.out.print(a + " ");
		}
		
		System.out.println(" ");
	}
	
	public void desenha(){
		desenhaLetra('D');
		desenhaLetra('C');
		desenhaLetra('B');
		desenhaLetra('A');
	}
	
	public boolean possuiLugar(){
		for( Fileira fileira : fileiras){
			if(fileira.possuiLugar())
				return true;
		}
		return false;
	}
	
	public boolean ocupado(int fileira, char letra){
		return fileiras[fileira - 1].ocupado(letra);
	}
	public void setOcupado(int fileira, char letra){
	    if(this.ocupado(fileira, letra))
	    	System.out.println("Poltrona ocupada! Tente outra.");
	    else {
	    	System.out.println("Reserva efetuada!");
	    	fileiras[fileira - 1].setOcupado(letra);
	    }
	}
}

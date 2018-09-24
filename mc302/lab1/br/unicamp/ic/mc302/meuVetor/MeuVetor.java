package br.unicamp.ic.mc302.meuVetor;

public class MeuVetor {
	
	private int vetor[];
	private int tamanho;
	
	public MeuVetor(int tamanho){
		
		this.vetor = new int[tamanho];
		this.tamanho = tamanho;
		
	}
	
	public int getTamanho(){
		return this.tamanho;
	}
	public void setValor(int pos, int valor){
		
		this.vetor[pos] = valor;
		
	}
	
	public int getValor(int pos){
		return this.vetor[pos];
	}
	
	public MeuVetor intercala(MeuVetor vetor2){
		
		MeuVetor v = new MeuVetor(this.getTamanho() + vetor2.getTamanho());
		int i = 0;
		while(i < this.getTamanho() || i < vetor2.getTamanho()){
			
			if(i < this.getTamanho()){
				
				v.setValor(i*2, this.getValor(i));
			
			}
			
			if (i < vetor2.getTamanho()){
				
				v.setValor(i*2+1, vetor2.getValor(i));
				
			}
			
			i++;
			
		}
		
		v.print();
		
		return v;
		
	}
	
	public void print(){
		
		for (int i = 0; i < tamanho; i++){
			
			System.out.println(i + ": " + this.vetor[i]);
			
		}
	}
}

package br.unicamp.ic.mc302.veiculos;

public class TanqueCombustivel {
	
	private int capacidadeMaxima;
	private int combustivelDisponivel;
	
	public TanqueCombustivel(int capacidadeMaxima){
		
		this.capacidadeMaxima = capacidadeMaxima;
		
	}
	
	public void adicionaCombustivel(int qtde){
		
		if(this.combustivelDisponivel+qtde <= this.capacidadeMaxima)
			this.combustivelDisponivel += qtde;
		else
			this.combustivelDisponivel = this.capacidadeMaxima;
		
	}
	
	public int combustivel(){
		
		return this.combustivelDisponivel;
		
	}
	
	public void gasta(int qtde){
		
		this.combustivelDisponivel -= qtde;
		
	}
}

package br.unicamp.ic.mc302.minhaMatriz;

import java.util.ArrayList;

public class MinhaMatriz {
	ArrayList<ArrayList<Integer>> linhas;
	public MinhaMatriz(){
		
		linhas = new ArrayList< ArrayList<Integer> >();
		
	}
	
	public void adicionaLinha(){
		
		ArrayList<Integer> l = new ArrayList<Integer>();
		for(int i = 0; i < numColunas(); i++) // Adiciona as colunas já existentes
			l.add(0);
		
		linhas.add(l);
		
	}

	public void adicionaColuna(){
		
		for( ArrayList<Integer> x: linhas){
			
			x.add(0);
			
		}
		
	}
	
	public void setElemento(int linha,int coluna, int elem){
		
		ArrayList<Integer> l = linhas.get(linha);
		l.set(coluna, elem);
		
	}
	
	public int getElemento(int linha, int coluna){
		
		return linhas.get(linha).get(coluna);
		
	}
	public int numLinhas(){
		return linhas.size();
	}

	public int numColunas(){
		if(linhas.size() > 0)
			return linhas.get(0).size();
		else
			return 0;
	}
	
	public MinhaMatriz multiplica(MinhaMatriz m2){
		
		MinhaMatriz r = new MinhaMatriz();
		for( int l = 0; l < this.numLinhas(); l ++)
			r.adicionaLinha();
		for(int c = 0; c < m2.numColunas(); c++)
			r.adicionaColuna();
		
		for( int l = 0; l < this.numLinhas(); l ++){
			
			for(int c = 0; c < m2.numColunas(); c++){
				
				Integer soma = 0;
		        for (int i = 0; i < this.numColunas(); i++) {
		            
		        	soma += this.getElemento(l, i) * m2.getElemento(i, c);
		        	
		        }
				
		        r.setElemento(l, c, soma);
				
			}
			
		}
		
		return r;
		
	}
	
	public void imprime(){
		 for(int i = 0; i < numLinhas(); i++ ){
			 
			 for(int c = 0; c < numColunas(); c++){
				 System.out.print(getElemento(i, c) + " ");
				 
			 }
			 System.out.print("\n");
		 }
	}
}
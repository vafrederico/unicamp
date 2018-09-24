package br.unicamp.ic.mc302.meuVetor;

public class ExemploMeuVetor {
	 static public void main(String args[ ]){ 
		 
		 MeuVetor v1 = new MeuVetor(4);
		 MeuVetor v2 =  new MeuVetor(4);
		 
		 v1.setValor(0, 0);
		 v1.setValor(1, 2);
		 v1.setValor(2, 4);
		 v1.setValor(3, 6);
		 
		 v2.setValor(0, 1);
		 v2.setValor(1, 3);
		 v2.setValor(2, 5);
		 v2.setValor(3, 7);
		 
		 MeuVetor v3 = v1.intercala(v2);
		 v3.print();
		 
	 }
}

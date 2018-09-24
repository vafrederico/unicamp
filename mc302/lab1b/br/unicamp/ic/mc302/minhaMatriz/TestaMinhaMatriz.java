package br.unicamp.ic.mc302.minhaMatriz;

public class TestaMinhaMatriz {
	 public static void main (String [] args) {
		 
		 MinhaMatriz m1 = new MinhaMatriz();
		 
		 m1.adicionaLinha();
		 m1.adicionaLinha();
		 m1.adicionaColuna();
		 m1.adicionaColuna();
		 m1.setElemento(0, 0, 1);
		 m1.setElemento(0, 1, 2);
		 m1.setElemento(1, 0, 3);
		 m1.setElemento(1, 1, 4);
		 System.out.println("M1");
		 m1.imprime();
		 
		 MinhaMatriz m2 = new MinhaMatriz();
		 
		 m2.adicionaLinha();
		 m2.adicionaLinha();
		 m2.adicionaColuna();
		 m2.adicionaColuna();
		 m2.setElemento(0, 0, 3);
		 m2.setElemento(1, 0, 4);
		 m2.setElemento(0, 1, 6);
		 m2.setElemento(1, 1, 9);
		 System.out.println("M2");
		 m2.imprime();
		 
		 MinhaMatriz m3 = m1.multiplica(m2);
		 
		 System.out.println("M3");
		 m3.imprime();
	 }
}

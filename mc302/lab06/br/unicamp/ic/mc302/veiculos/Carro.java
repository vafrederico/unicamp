package br.unicamp.ic.mc302.veiculos;

public class Carro extends Veiculo {
 private int lotacao;
 private int numPortas;


  public Carro(int lot, int num, int ano, String mar, String mod, String pl) {
     super(ano,mar,mod,pl);
     lotacao=lot;
     numPortas=num;
  }

	public boolean ligar(){
		
		System.out.println("O Carro foi ligado corretamente");
		return true;
	}
	
  public void mostra(){
     System.out.println("\nTipo-->Carro");
     System.out.println("Lotação = "+lotacao);
     System.out.println("Numero de Portas = "+numPortas);
     super.mostra();
 }
  
  public String toString(){
	  return "\nTipo-->Carro" + "\nLotação = "+lotacao+ "\nNumero de Portas = "+numPortas + "\n";
	 		
  }
}
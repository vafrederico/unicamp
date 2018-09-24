package br.unicamp.ic.mc302.oficina;

public class Oficina {

	  public static void main(String[] args) {
		  
		  Funcionario func[] = new Funcionario[10];
		  
		  func[0] = new Funcionario(1, 4, 2, 3);
		  func[1] = new Funcionario(2, 7, 1, 1);
		  func[2] = new Funcionario(3, 1, 3, 3);
		  func[3] = new Funcionario(4, 0, 0, 5);
		  func[4] = new Gerente(5, 3, 0, 2);
		  func[5] = new Funcionario(6, 2, 1, 4);
		  func[6] = new Funcionario(7, 1, 2, 6);
		  func[7] = new Funcionario(8, 6, 4, 2);
		  func[8] = new Funcionario(9, 2, 3, 3);
		  func[9] = new Funcionario(10, 1, 0, 1);
		  
		  for(int i = 0; i < 10; i++){
			  System.out.println("Funcionario " + func[i].getNum() + " / Comissão: " + func[i].calculaComissao() + " / Salário: " + func[i].getSalario());
			  
		  }
	  }
}

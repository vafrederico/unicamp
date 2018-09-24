package br.unicamp.ic.mc302.oficina;

public class Funcionario {
	
	protected int num;
	protected int tipo1, tipo2, tipo3;
	protected boolean gerente = false;
	protected int salario;
	
	public Funcionario (int numero, int t1, int t2, int t3, boolean ger){

		num = numero;
		tipo1 = t1;
		tipo2 = t2;
		tipo3 = t3;
		gerente = ger;
		
	}

	public Funcionario (int numero, int t1, int t2, int t3){

		this(numero, t1, t2, t3, false);
		salario = 500;
	}
	
	public double calculaComissao() {
		
		return calculaComissao(0.1);
	}

	public double calculaComissao(double multiplicador) {
		double comissao;
		comissao = (tipo1*15 + tipo2*50 + tipo3*40)*multiplicador;
		
		return comissao;
	}
	
	public int getNum(){
		return num;
	}
	public int getSalario(){
		return salario;
	}
}

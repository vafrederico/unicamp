package br.unicamp.ic.mc302.oficina;

public class Gerente extends Funcionario{

	public Gerente(int numero, int t1, int t2, int t3) {
		super(numero, t1, t2, t3, true);
		
		salario = 1000;
	}
	
	public double calculaComissao() {
		
		return super.calculaComissao(0.15);
		
	}
	
}

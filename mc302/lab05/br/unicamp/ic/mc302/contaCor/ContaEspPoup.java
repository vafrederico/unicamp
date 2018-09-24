package br.unicamp.ic.mc302.contaCor;

public class ContaEspPoup extends ContaEsp{

	ContaEspPoup(String nome, double val, int num, int pwd) {
		super(nome, val, num, pwd);
	}

	public boolean debitaValor(double val, int pwd) {
		System.out.println("debitaValor ContaEspPoup");
		boolean r;
		return r;
	}
}

package br.unicamp.ic.mc302.contaCor;

public class ExemploPolimorfismoComRedefinicao {

	public static void main(String args[]) {
		ContaCor c1;
		c1 = new ContaCor("Joao da Silva", 500.00, 1234, 1314);
		c1.creditaValor(100.00);
		c1.debitaValor(150.00, 1314);
		System.out.println("Saldo atual: " + c1.getSaldo(1314));
		c1 = new ContaEsp("Jose Ferreira", 1000.00, 1011, 1314);
		System.out.println("Saldo atual: " + c1.getSaldo(1314));
		c1.creditaValor(100.00);
		c1.debitaValor(1200.00, 1314);
		System.out.println("Saldo atual: " + c1.getSaldo(1314));
		//c1.alteraLimite(100.00);
		//System.out.println("Credito usado: " + c1.getCreditoUsado(1314));

		ContaEsp c2 = new ContaEsp("Maria de Souza", 1000.00, 1011, 1516);
		c2.creditaValor(100.00);
		c2.debitaValor(500.00, 1516);
		System.out.println("Saldo atual: " + c2.getSaldo(1516));
		c2.alteraLimite(200.00, 1516);
		System.out.println("Credito usado: " + c2.getCreditoUsado(1516));
	}
}
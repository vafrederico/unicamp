package br.unicamp.ic.mc302.contaCor;

public class ExemploCoercao {

	public static void main(String args[]) {
		double saldoInicialChico = 100;
		int numeroChico = 30;
		int senhaChico = 99;

		double saldoInicialBelchior = 200;
		int numeroBelchior = 31;
		int senhaBelchior = 91;

		ContaCor cc1 = new ContaCor("Chico", saldoInicialChico, numeroChico,
				senhaChico); // Compilacao falha. esse construtor espera
								// (String, double, int, int). O compilardor
								// nao consegue achar um construtor que case
								// com (String, double, float, long).
								// Similarmente
								// para o caso abaixo.

		ContaCor cc2 = new ContaCor("Belchior", saldoInicialBelchior,
				numeroBelchior, senhaBelchior);
		
	}
}

package br.unicamp.ic.mc302.documento;

public class Telegrama extends Documento {

	private String hora;

	public void registrar() {
		System.out.println("Registra o Telegrama.");
	}

	public void pagar() {
		System.out.println("Paga o Telegrama.");
	}
}
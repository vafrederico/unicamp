package br.unicamp.ic.mc302.contaCor;

public class ExemploDoisConstrutores {

	public static void main(String args[]) {
		String titular = "Bob";
		int numConta = 30;
		int senha = 99;

		ContaCor cc1 = new ContaCor(titular, 0, numConta,senha); 
		ContaCor cc2 = new ContaCor(titular, numConta, senha);
		
		System.out.println("CC1: titular: " + cc1.getTitular() + " Saldo: " + cc1.getSaldo(senha) + " numConta: " + cc1.getNumConta() + " Senha: " + cc1.getSenha());
		System.out.println("CC2: titular: " + cc2.getTitular() + " Saldo: " + cc2.getSaldo(senha) + " numConta: " + cc2.getNumConta() + " Senha: " + cc2.getSenha());
		
		
	}
}

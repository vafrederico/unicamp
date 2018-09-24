package br.unicamp.ic.mc302.contaCor;

class Exemplo{ 
    static public void main(String args[ ]){ 
        ContaCor c1 = new ContaCor("Ursula", 500, 1, 1);
        c1.creditaValor(100); 
        c1.debitaValor(50 ,1); 	
        c1.saldoAtual += 100;
        ContaCor c2 = new ContaCor("Bob", 500, 2, 2);
        c1.transferir(c2, 100, 1);
        System.out.println("Saldo final c1 = " + c1.getSaldo(1));
        System.out.println("Saldo final c2 = " + c2.getSaldo(2));
    }
}

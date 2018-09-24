package br.unicamp.ic.mc302.veiculos;

public class ExemploCaminhao {
	
    public static void main(String args[]) {
    	
    	Caminhao caminhao = new Caminhao(1, 2, 2000, "Scania", "Modelo 1", "DDDD-2922", 2, 1000);
    	
    	System.out.println("numEixos: " + caminhao.getNumEixos());
    	System.out.println("capacidade: " + caminhao.getCapacidade());
    	
    }
}

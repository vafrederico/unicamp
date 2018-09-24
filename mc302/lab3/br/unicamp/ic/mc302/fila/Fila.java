package br.unicamp.ic.mc302.fila;

public class Fila extends Lista {

    public void enfileirar(int i) {
        super.adicionaFim(i);
        System.out.println("Enfileirou o elemento " + i);
    }
    
    public int pegarPrimeiro() {
        int i = super.removeInicio();
        System.out.println("Tirou o elemento " + i + " do início da fila.");
        return i;
    }

}
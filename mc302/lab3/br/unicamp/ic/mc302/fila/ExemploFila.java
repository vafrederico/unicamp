package br.unicamp.ic.mc302.fila;

public class ExemploFila {

    public static void main(String args[]) {
    
        Fila fila = new Fila();
        
        fila.enfileirar(1);
        fila.enfileirar(2);
        fila.enfileirar(3);
                
        fila.pegarPrimeiro();
        fila.enfileirar(5);
        fila.pegarPrimeiro();
        fila.pegarPrimeiro();
        fila.pegarPrimeiro();
    }
}
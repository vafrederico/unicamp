package br.unicamp.ic.mc302.contador;

// arquivo Contador.java
public class Contador{ 
    private int num; // valor do contador
    public void incrementa ( ) { 
        num = num +1; }
    public void decrementa ( ) {
        num = num -1; }
    public void comeca(int n) {
        num = n; }
    public int retornaNum( ) { 
        return this.num; } // this  é uma referencia para o objeto corrente
} // fim da classe Contador 

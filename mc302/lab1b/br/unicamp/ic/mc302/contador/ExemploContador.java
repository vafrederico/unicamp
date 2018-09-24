// arquivo ExemploContador.java
package br.unicamp.ic.mc302.contador;

class ExemploContador{
    static public void  main (String args[ ]) {
        Contador umCont;
        umCont = new Contador( ); // alocação dinâmica de memória
        umCont.comeca(0); 
        System.out.println(umCont.retornaNum()); 
        umCont.incrementa( );
        System.out.println(umCont.retornaNum());
    }
} // fim da classe Principal

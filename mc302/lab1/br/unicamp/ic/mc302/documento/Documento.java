package br.unicamp.ic.mc302.documento;

/*
 * Um exercício: modificar a classe para que ela realmente imprima os elementos
 * do objeto (autor e dataDeChegada). 
 */

public class Documento {
    private String autor;
    private int dataDeChegada;
    public void criarDocumento(String nome, int num) {
        autor = nome;
        dataDeChegada = num; 
    }
    public void imprimir( ) {
        System.out.println( "autor: " + this.autor + "\ndataDeChegada: " + this.dataDeChegada);
      
    }
    public void editar ( ){
        System.out.println("Edita o contéudo de um Documento");
    }
} // fim da classe Documento

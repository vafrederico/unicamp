package br.unicamp.ic.mc302.listaInts;
/*
 * Uma classe para demonstrar o uso de listas parametrizadas (ArrayList) em Java
 * concentrando no uso da estrutura de laço "for each".
 */

import java.util.ArrayList;

public class ListaInts {
    ArrayList<Integer> lista;

    // Constructor
    ListaInts() {
        lista = new ArrayList<Integer>();
    }
    
    public void removeElem(Object elem){
    	
    	this.lista.remove(elem);
    	
    }
    // método de adição de elementos para o ArrayList
    // Outros métodos podem ser adicionados de maneira similar
    void add(Integer n) {
        lista.add(n);
    }

    // n é um elemento da lista?
    Boolean elem(Integer n) {
        for (Integer x: lista) {
            if (x.equals(n)) return true;
        }
        return false;
    }

    // Soma dos elementos da lista
    Integer sum() {
        Integer total = 0;
        for (Integer x: lista) {
            total = total + x;
        }
        return total;
    }

    // Encontra o menor elemento da lista
    // A lista precisa ter pelo menos um elemento
    Integer minimum() {
        // mantém o menor elemento encontrado na lista
        // Inicializa com o primeiro elemento da lista.
        Integer smallestSoFar = lista.get(0);
        for (Integer x: lista) {
            if (x < smallestSoFar)
                smallestSoFar = x;
        }
        return smallestSoFar;
    }

    // Uma outra versão, utilizando laços padrões.
    Integer minimum_version2() {
        Integer smallestSoFar = lista.get(0);
        for (int index = 1; index < lista.size(); index++) {
            if (lista.get(index) < smallestSoFar)
                smallestSoFar = lista.get(index);
        }
        return smallestSoFar;
    }

    // cria uma representação textual da lista.
    public String toString() {
    	StringBuilder s = new StringBuilder(); // Creates an empty string builder with default capacity (16 empty elements).
    	s.append("[");						   // Appends the argument to this string builder.	
    	for (Integer x:lista) {
    		s.append(x);  					   // The data is converted to a string before the append operation takes place. 
    		s.append(", ");
    	}
    	int i = s.length();
    	if (i > 1) {
    		s.replace(i-2, i-1, "]");		   // Replaces the specified character(s) in this string builder.
    	}
    	else s.append("]");
        return s.toString();                   // Returns a string that contains the character sequence in the builder.
    }

} // Fim da classe ListLints


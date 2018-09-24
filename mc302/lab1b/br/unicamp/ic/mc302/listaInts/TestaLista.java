package br.unicamp.ic.mc302.listaInts;

/*
 * Uma classe simples para testar a classe ListaInts
 */

class TestaLista {
    public static void main (String [] args) {
        ListaInts list1 = new ListaInts();
        ListaInts list2 = new ListaInts();

        list1.add(9);
        list1.add(8);
        list1.add(7);
        list1.add(6);
        list1.add(5);
        list1.add(4);
        list1.add(3);
        list1.add(2);
        list1.add(1);
        list1.add(0);

        System.out.println("3 pertende à  list1? "      + list1.elem(3));
        System.out.println("42 está na list1? "        + list1.elem(42));
        System.out.println("3 está na list2 (vazia)? " + list2.elem(3));

        System.out.println("Soma dos elementos da list1: " + list1.sum());
        System.out.println("Soma dos elementos da list2: " + list2.sum());
        
        System.out.println("list1: " + list1.toString());
        System.out.println("list2: " + list2.toString());
        
        System.out.println("3 pertende à  list1? "      + list1.elem(3));
        list1.removeElem(3);
        System.out.println("3 pertende à  list1? "      + list1.elem(3));
    }
}

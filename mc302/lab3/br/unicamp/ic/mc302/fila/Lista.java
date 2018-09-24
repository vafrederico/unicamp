package br.unicamp.ic.mc302.fila;

import java.util.Vector;

public class Lista {

	private int numElementos = 0;
	
	private Vector lista = new Vector();
	
    public void adicionaInicio(int i) {
        lista.insertElementAt(new Integer(i), 0);
        numElementos++;
    }
    
    public void adicionaFim(int i) {
        lista.add(new Integer(i));
        numElementos++;
    }
    
    public int removeInicio() {
	    int retorno = -1;
	    if(numElementos > 0) {
		    retorno = ((Integer)lista.elementAt(0)).intValue();
		    lista.remove(0);
		    numElementos--;
	    }    
	    return retorno;	    
    }
    
    public int removeFim() {
	    int retorno = -1;
	    if(numElementos > 0) {
		    retorno = ((Integer)lista.elementAt(numElementos - 1)).intValue();
		    lista.remove(numElementos - 1);    
		    numElementos--;
  	    }    
	    return retorno;
    }
}
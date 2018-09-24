package br.unicamp.ic.mc302.onibus;

import java.io.*;

public class ExemploOnibus {

    public static void main(String args[]) {
    	
    	Onibus onibus = new Onibus();
    	InputStreamReader istream = new InputStreamReader(System.in) ;
    	BufferedReader bufRead = new BufferedReader(istream) ;
    	while(onibus.possuiLugar()){
	    	try {
	    		onibus.desenha();
	    		System.out.println("Poltrona: (Formato: Fileira Letra - 1 A 3 C)");
	    	    String linha = bufRead.readLine();

	    	    int fileira;
	    	    if(linha.indexOf(' ') == -1)
	    	    	fileira = Integer.parseInt(linha);
	    	    else
		    	    fileira = Integer.parseInt(linha.substring(0, linha.indexOf(' ')));
	    	    
	    	    if(fileira < 0)
	    	    	break;
	    	    else { char letra =  linha.charAt(linha.indexOf(' ') + 1);
	    	    onibus.setOcupado(fileira, letra);
	    	    }
	    	}
	    	catch (IOException err) {
	    	     System.out.println("Error reading line");
	    	}
    	}
    }
}

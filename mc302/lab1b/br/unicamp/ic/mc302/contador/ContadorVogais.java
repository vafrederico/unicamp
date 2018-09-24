package br.unicamp.ic.mc302.contador;

// Arquivo ContadorVogais.java
public class ContadorVogais {

    public static void main(String args[]) {
	    char fraseExaminada[] = {'T','e','x','t','o',' ','E','x','e','m','p','l','o',' ','P','a','r','a',' ','A',' ','C','o','n','t','a','g','e','m',' ','D','o',' ','N','u','m','e','r','o',' ','D','e',' ','V','o','g','a','i','s','.'};
		Contador[] contVogais = new Contador[5]; // um para cada vogal
	    
		for(int i = 0; i < 5; i++){
			contVogais[i] = new Contador();
		}
		
	    for(int i = 0; i< fraseExaminada.length; i++){
	    	switch(Character.toLowerCase(fraseExaminada[i])){
		    	case 'a':
		    		contVogais[0].incrementa();
		    		break;
		    		
		    	case 'e':
		    		contVogais[1].incrementa();
		    		break;
		    	
		    	case 'i':
		    		contVogais[2].incrementa();
		    		break;
		    	
		    	case 'o':
		    		contVogais[3].incrementa();
		    		break;
		    		
		    	case 'u':
		    		contVogais[4].incrementa();
		    		break;
		    		
	    		default:
	    			break;
	    	}
	    	
	    }
	    
	    System.out.println("A: " + contVogais[0].retornaNum());
	    System.out.println("E: " + contVogais[1].retornaNum());
	    System.out.println("I: " + contVogais[2].retornaNum());
	    System.out.println("O: " + contVogais[3].retornaNum());
	    System.out.println("U: " + contVogais[4].retornaNum());
	    
    }
} // Fim da classe ContadorVogais

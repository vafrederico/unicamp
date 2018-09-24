package br.unicamp.ic.mc302.circulo;

// arquivo TestaCirculo.java
class TestaCirculo {
    public static void main (String args[ ]) {

    	Circulo v1[] = new Circulo[5];
    	
    	v1[0] = new Circulo(1,2,7);
    	v1[1] = new Circulo(3,2,3);
    	v1[2] = new Circulo(1,5,8);
    	v1[3] = new Circulo(7,4,5);
    	v1[4] = new Circulo(6,6,2);
    	
    	System.out.println("b) Imprimindo v1");
    	for(int i = 0; i < 5; i++)
    		System.out.println("v1[" + i + "]: (" + v1[i].getX() + ", " + v1[i].getY() + ", " + v1[i].getRaio() + ")");
    	
    	System.out.println("e) Imprimindo v1 e v2");
    	Circulo v2[] = v1;
    	for(int i = 0; i < 5; i++){
    		System.out.print("v1[" + i + "]: (" + v1[i].getX() + ", " + v1[i].getY() + ", " + v1[i].getRaio() + ") ");
    		System.out.println("v2[" + i + "]: (" + v2[i].getX() + ", " + v2[i].getY() + ", " + v2[i].getRaio() + ")");
    	}
    	
    	Circulo v3[] = new Circulo[5];
    	for(int i = 0; i < 5; i++)
    		v3[i] = v1[i];
    	
    	v1[0].setRaio(3);
    	v1[1].setRaio(3);
    	v1[2].setRaio(3);
    	v1[3].setRaio(3);
    	v1[4].setRaio(3);
    	
    	System.out.println("i) Imprimindo v1, v2, v3");
    	for(int i = 0; i < 5; i++){
    		System.out.print("v1[" + i + "]: (" + v1[i].getX() + ", " + v1[i].getY() + ", " + v1[i].getRaio() + ") ");
    		System.out.print("v2[" + i + "]: (" + v2[i].getX() + ", " + v2[i].getY() + ", " + v2[i].getRaio() + ") ");
    		System.out.println("v3[" + i + "]: (" + v3[i].getX() + ", " + v3[i].getY() + ", " + v3[i].getRaio() + ")");
    	}
    	
    }

} // Fim da classe TestaCirculo
 

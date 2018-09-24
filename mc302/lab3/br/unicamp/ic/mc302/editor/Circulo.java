package br.unicamp.ic.mc302.editor;

public class Circulo  extends Figura{
	
	private int centro[] = new int[2];
	private int raio;
	
	public Circulo(int centroX, int centroY, int raio){
		this.centro[0] = centroX;
		this.centro[1] = centroY;
		this.raio = raio;
	}
	
	public void desenhar(){
		System.out.println("Circulo: Centro: (" + this.centro[0] + "," + this.centro[1] + ") Raio: " + this.raio);
	}
}

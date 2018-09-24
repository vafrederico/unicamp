package br.unicamp.ic.mc302.editor;

public class Linha  extends Figura{
	
	private int p1[] = new int[2];
	private int p2[] = new int[2];
		
	public Linha(int p1X, int p1Y, int p2X, int p2Y){
		this.p1[0] = p1X;
		this.p1[1] = p1Y;
		this.p2[0] = p2X;
		this.p2[1] = p2Y;
	}
	
	public void desenhar(){
		System.out.println("Linha: P1: (" + this.p1[0] + "," + this.p1[1] + ") P2: (" + this.p2[0] + "," + this.p2[1] + ")");
	}
}

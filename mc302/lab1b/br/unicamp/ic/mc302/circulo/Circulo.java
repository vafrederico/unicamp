package br.unicamp.ic.mc302.circulo;

// arquivo Circulo.java
public class Circulo {
	private int x, y;
	private int raio;

	public static final double PI = 3.14159;

	public Circulo (int x1, int y1, int raio) {
		x = x1;
		y = y1;
		this.raio = raio;
	}
	public int getX () {
		return x;
	}
	public int getY () {
		return y;
	}
	public int getRaio () {
		return raio;
	}
	public void setRaio(int r){
		this.raio = r;
	}
	public double circunferencia() {
		return 2 * PI * raio;
	}

} // Fim da classe Circulo

 

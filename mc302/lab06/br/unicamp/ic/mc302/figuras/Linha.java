package br.unicamp.ic.mc302.figuras;

class Linha extends Figura {

	private int pt1X;
	private int pt1Y;
	private int pt2X;
	private int pt2Y;
/*
	void esconder() {
		System.out.println("esconder() de Linha.");
	}
*/
	void mostrar(int x, int y) {
		System.out.println("mostrar() de Linha. (" + x + ", " + y + ")");
	}
}

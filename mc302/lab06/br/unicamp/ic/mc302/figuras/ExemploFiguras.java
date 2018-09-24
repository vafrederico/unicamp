package br.unicamp.ic.mc302.figuras;

public class ExemploFiguras {

	public static void main(String args[]) {
		Figura circ = new Circulo();
		Figura lin = new Linha();
		circ.mover(1, 1);
		circ.mover(3, 3);
		circ.mover(5, 5);

		lin.mover(1, 2);
		lin.mover(4, 2);
		lin.mover(7, 2);
	}
}
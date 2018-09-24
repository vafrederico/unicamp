package br.unicamp.ic.mc302.figuras;

abstract class Figura {

	void mover(int x, int y) {
		esconder();
		mostrar(x, y);
	}

	void esconder(){
		System.out.println("Esconder da classe Figura.");
	}

	void mostrar(int x, int y){
		System.out.println("Esconder da classe Figura.");
	}
}

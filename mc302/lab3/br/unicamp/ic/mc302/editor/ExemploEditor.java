package br.unicamp.ic.mc302.editor;

public class ExemploEditor {

	
    public static void main(String args[]) {
		
    	Editor editor = new Editor();
    	
    	Grupo g = new Grupo();
		Figura a = new Figura();
		Circulo c = new Circulo(1,2, 3);
		a.adiciona(c);
		g.adiciona(c);
		c = new Circulo(1,2, 4);
		a.adiciona(c);
		g.adiciona(c);
		editor.adiciona(a);
		
		Figura b = new Figura();
		b.adiciona(new Linha(1,1,2,2));
		b.adiciona(new Linha(2,2,1,1));	
		b.adiciona(new Linha(0,0,2,2));
		g.adiciona(b);
		editor.adiciona(b);
		

		Figura c1 = new Figura();
		Poligono p = new Poligono();
		p.adiciona(new Linha(1,1,2,2));
		p.adiciona(new Linha(2,2,1,1));
		p.adiciona(new Linha(0,0,2,2));
		c1.adiciona(p);
		g.adiciona(c1);
		editor.adiciona(c1);
		
		editor.adiciona(g);
		editor.desenhar();
		
	}
}

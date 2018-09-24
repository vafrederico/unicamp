package br.unicamp.ic.mc302.documento;

public class ExemploPolimorfismoSemRedefinicao {

	public static void main(String args[]) {
		Documento d = new Documento();
		d.imprimir();
		d = new Carta(); // d pode tambem referenciar um objeto do tipo Carta
		if(d instanceof Carta){
			Carta carta = (Carta) d;
				
			carta.imprimir();
			carta.anexar(); 
		}
		d = new Telegrama(); // d pode tambem referenciar um objeto do tipo
								// Telegrama
		if(d instanceof Telegrama){
			Telegrama telegrama = (Telegrama) d;
				
			telegrama.imprimir();
			telegrama.registrar();
			telegrama.pagar();
		}
	}
}
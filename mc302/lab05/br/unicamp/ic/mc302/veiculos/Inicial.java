package br.unicamp.ic.mc302.veiculos;


/**
 * Título:  Modulo 3
 *
 *  Classe Inicial
 */

public class Inicial {

  public static void main(String[] args) {
	  FilaVeiculo fila;
	  fila= new FilaVeiculo();
	  System.out.println("A Fila de Veiculos contem:");
	  fila.adicionaVeiculo("Carro",5,2,1999,"VOLKSWAGEN","GOL","EST3245");
	  fila.adicionaVeiculo("Caminhao",15000,3,1997,"VOLKSWAGEN","TITAN","KED9871");
	  fila.adicionaVeiculo("Carro",5,1,1998,"FIAT","PALIO","JKU2171");
	  fila.adicionaVeiculo("Carro",5,5,2001,"FORD","FIESTA","JNM2464");
	  fila.adicionaVeiculo("Caminhao",10000,2,2000,"FORD","CARGO","KMG4171");
	  fila.adicionaVeiculo("Carro",4,2,2001,"CHEVROLET","CELTA","JGH5432");
	  fila.adicionaVeiculo("Caminhao",8000,4,1996,"FORD","SCANIA","DEY6429");
		if (!fila.Vazia()) {
			fila.mostraFila();
		} else {
			System.out.println("\n Fila está vazia \n");
		}
	}
}// fim classe Inicial
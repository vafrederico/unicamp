package br.unicamp.ic.mc302.termostato;

public class Chave {
	private int estadoChave = 0; // 0-desligado; 1-ligado.
	public void ligar(){
		estadoChave = 1; 
	}
	public void desligar(){
		estadoChave = 0; 
	}
	public boolean ligada() {
		return estadoChave == 1;
	}
}

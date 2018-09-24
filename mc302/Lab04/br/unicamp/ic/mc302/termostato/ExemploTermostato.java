package br.unicamp.ic.mc302.termostato;

public class ExemploTermostato {
    public static void main(String args[]) {
    	
    	Termostato t = new Termostato();
    	t.setTempRequerida(25);
    	
    	System.out.println("Termostato ligado: " + t.chaveLigada());
    	t.fazerMonitoramento();
    	System.out.println("Termostato ligado: " + t.chaveLigada());
    }
}

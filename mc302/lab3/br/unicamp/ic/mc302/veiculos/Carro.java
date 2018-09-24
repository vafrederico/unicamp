package br.unicamp.ic.mc302.veiculos;

public class Carro {
    
	private int lotacao;
    private int numPortas;
    private String marca;
    private String modelo;
    private String placa;
    private int anoModelo;
    
    private Motor motor = new Motor();
    private TanqueCombustivel tanque = new TanqueCombustivel(40);
    
    public Carro(int lot, int num, int ano, String mar, String mod, String pl) {
        marca=mar;
        modelo=mod;
        placa=pl;
        anoModelo=ano;
        lotacao=lot;
        numPortas=num;
    }
    
    public void Ligar(){
    	
    	this.motor.ligar();
    	this.tanque.gasta(1);
    	
    }
    
}
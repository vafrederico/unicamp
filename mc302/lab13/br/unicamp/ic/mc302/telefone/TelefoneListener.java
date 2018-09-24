package br.unicamp.ic.mc302.telefone;

public interface TelefoneListener extends java.util.EventListener {

	public void telefoneTocou(TelefoneEvent e);
	
	public void telefoneAtendido(TelefoneEvent e);

}
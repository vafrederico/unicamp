package br.unicamp.ic.mc302.telefone;

@SuppressWarnings("serial")
public class TelefoneEvent extends java.util.EventObject {
	
	public int num;
	public String data, hora;

	public TelefoneEvent(Telefone source) {
		super(source);
	}
	
	public TelefoneEvent(Telefone source, int num, String data, String hora) {
		super(source);
		this.num = num;
		this.data = data;
		this.hora = hora;
	}
	
}

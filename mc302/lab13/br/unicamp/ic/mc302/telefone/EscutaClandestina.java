package br.unicamp.ic.mc302.telefone;

public class EscutaClandestina extends TelefoneAdapter {

	public void telefoneTocou(TelefoneEvent e) {
		System.out.println("EscutaClandestina escuta o telefone tocando. (Telefone: " + e.num + ", Data: " + e.data + ", Hora: " + e.hora + ")");
	}

	public void telefoneAtendido(TelefoneEvent e) {
		System.out.println("EscutaClandestina sabe que o telefone foi atendido.");
	}

}

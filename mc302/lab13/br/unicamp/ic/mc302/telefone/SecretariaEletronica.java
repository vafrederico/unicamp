package br.unicamp.ic.mc302.telefone;

public class SecretariaEletronica implements TelefoneListener {

	public void telefoneTocou(TelefoneEvent e) {
		System.out.println("Secretaria escuta o telefone tocando. (Telefone: " + e.num + ", Data: " + e.data + ", Hora: " + e.hora + ")");
	}

	public void telefoneAtendido(TelefoneEvent e) {
		System.out.println("Secretaria sabe que o telefone foi atendido.");
	}

}

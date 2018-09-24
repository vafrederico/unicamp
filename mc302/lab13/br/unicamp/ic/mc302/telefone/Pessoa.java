package br.unicamp.ic.mc302.telefone;

public class Pessoa {
	
    public void escutaTelefone(Telefone t) {
    	
        t.addTelefoneListener(
            new TelefoneAdapter() {
                public void telefoneTocou(TelefoneEvent e) {
                    System.out.println("Pessoa atende o telefone! (Telefone: " + e.num + ", Data: " + e.data + ", Hora: " + e.hora + ")");
                    ((Telefone)(e.getSource())).atendeFone();
                }
            }
        );
        
    }
}
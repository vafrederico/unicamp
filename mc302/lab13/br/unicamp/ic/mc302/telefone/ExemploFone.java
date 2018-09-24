package br.unicamp.ic.mc302.telefone;

public class ExemploFone {
	
    public static void main(String[] args) {
    	
        Telefone fone = new Telefone();
        Pessoa fulano = new Pessoa();
        SecretariaEletronica se = new SecretariaEletronica();
        EscutaClandestina escuta = new EscutaClandestina();
        
        fone.addTelefoneListener(se);
        fone.addTelefoneListener(escuta);
        fulano.escutaTelefone(fone);

        fone.tocaFone(51515151, "11/06/2013", "16:37");
        
    }
}

package br.unicamp.ic.mc302.telefone;

import java.util.*;

public class Telefone {
	
    private Collection <TelefoneListener> telefoneListeners = new ArrayList<TelefoneListener>();

    // método de suporte para testar a solução
    public void tocaFone(int num, String data, String hora) {
        disparaTelefoneTocou(num, data, hora);
    }

    // método de suporte para testar a solução
    public void atendeFone() {
        disparaTelefoneAtendido();
    }

    public void addTelefoneListener(TelefoneListener tl) {
        if(!telefoneListeners.contains(tl)) {
            telefoneListeners.add(tl);
        }
    }

    public void removeTelefoneListener(TelefoneListener tl) {

        telefoneListeners.remove(tl);
    }

    private void disparaTelefoneTocou(int num, String data, String hora) {
         TelefoneEvent evento = new TelefoneEvent(this, num, data, hora);                
        for (TelefoneListener t : telefoneListeners) {
                t.telefoneTocou(evento);
        }
    }
            

    // disparaTelefoneAtendido() é semelhante a disparaTelefoneTocou()
    private void disparaTelefoneAtendido() {
        TelefoneEvent evento = new TelefoneEvent(this);
        for (TelefoneListener t : telefoneListeners) {
                t.telefoneAtendido(evento);
        }        
    }
    
}

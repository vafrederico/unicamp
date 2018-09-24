package br.unicamp.ic.mc302.documento;

class ExemploDocumento{ 
    static public void main(String args[ ]){ 
        Documento d1; // declaração de uma referência para um 
                      // objeto do tipo Documento  
        d1 = new Documento( ); //alocação dinâmica de memória para a 
                                       //criação do objeto
        d1.criarDocumento("Camila",181101);
        d1.imprimir( ); // envio de mensagem para o objeto
        d1.editar();
        
        Documento d2;
        d2 = new Documento();
        d2.criarDocumento("Bob",18181);
        d2.imprimir();
        
    }
}

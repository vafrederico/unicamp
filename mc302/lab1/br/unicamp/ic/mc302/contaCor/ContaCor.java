package br.unicamp.ic.mc302.contaCor;

class ContaCor {
    private int estado; // 1 = conta ativa ; 2 = conta inativa
    private int senha;
    private int numConta;
    private String titular;
    public double saldoAtual;

    public static final int ATIVA = 1;
    public static final int INATIVA = 2;

    public boolean creditaValor (double val) {
        if (estado!=ATIVA) return(false); // conta deve estar ativa
        if (val<=0) return (false); // val>0;
        saldoAtual+= val; // credita valor;
        return(true); // operação terminada com sucesso
    } // fim de creditaValor( )

    public boolean debitaValor (double val, int pwd) {
        if (estado!=ATIVA) return(false); // conta deve estar ativa
        if (val<=0) return (false); // val>0;
        if (pwd!=senha) return (false); // senha deve ser válida
        if (val>saldoAtual) return (false); // val<= saldoAtual
        saldoAtual -= val; //debita valor
        if(saldoAtual ==0) estado=INATIVA; // se saldo=0, torna conta inativa
        return(true);
    } // fim de debitaValor( )

    public double getSaldo (int pwd) {
        if (estado!=ATIVA) return(-1); // conta deve estar ativa
        if (pwd!=senha) return(-1); //senha deve ser válida
        return(saldoAtual);
    } // fim de getSaldo( )
    
    public void transferir(ContaCor conta, double quantia, int senha){
    	
    	if(this.senha == senha){
    		
    		if(this.saldoAtual >= quantia){
    			
    			this.debitaValor(quantia, senha);

        		conta.creditaValor(quantia);
        		
    		}
    		
    	}
    }
    public ContaCor(String nome, double val, int num, int pwd) {
        titular = nome;
        numConta = num;
        senha = pwd;
        saldoAtual = val;
        estado=1; //conta é ativada quando criada
    } // fim do construtor
} // fim da classe ContaCor


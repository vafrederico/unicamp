package br.unicamp.ic.mc302.contaCor;

class ContaCor {
	private int estado; // 1 = conta ativa ; 2 = conta inativa
	private int senha;
	private int numConta;
	private String titular;
	private double saldoAtual;
	
	public ContaCor(String nome, int num, int pwd){
		titular = nome;
		numConta = num;
		senha = pwd;
		estado = 1; // conta � ativada quando criada
	}
	public ContaCor(String nome, double val, int num, int pwd) {
		
		this(nome, num ,pwd);
		saldoAtual = val;
		
	} // fim do construtor

	public static final int ATIVA = 1;
	public static final int INATIVA = 2;

	public boolean creditaValor(double val) {
		if (estado != ATIVA)
			return (false); // conta deve estar ativa
		if (val <= 0)
			return (false); // val>0;
		saldoAtual += val; // credita valor;
		return (true); // opera��o terminada com sucesso
	} // fim de creditaValor( )

	public boolean debitaValor(double val, int pwd) {
		System.out.println("debitaValor ContaCor");
		if (estado != ATIVA)
			return (false); // conta deve estar ativa
		if (val <= 0)
			return (false); // val>0;
		if (pwd != senha)
			return (false); // senha deve ser valida
		if (val > saldoAtual)
			return (false); // val<= saldoAtual
		saldoAtual -= val; // debita valor
		if (saldoAtual == 0)
			estado = INATIVA; // se saldo=0, torna conta inativa
		return (true);
	} // fim de debitaValor( )

	public double getSaldo(int pwd) {
		if (estado != ATIVA)
			return (-1); // conta deve estar ativa
		if (pwd != senha)
			return (-1); // senha deve ser valida
		return (saldoAtual);
	} // fim de getSaldo( )
	
	public String getTitular(){
		return titular;
	}
	public int getNumConta(){
		return numConta;
	}
	public int getSenha(){
		return senha;
	}
	protected void setEstado(int argEstado) {
		this.estado = argEstado;
	}

	protected int getEstado() {
		return this.estado;
	}
} // fim da classe ContaCor


package br.unicamp.ic.mc302.contaCor;

class ContaEsp extends ContaCor {
	private double limite;

	ContaEsp(String nome, double val, int num, int pwd) {
		super(nome, val, num, pwd); // construtor da superclasse
		limite = 200;
		creditaValor(limite);
	} // fim construtor ContaCor( )

	public boolean alteraLimite(double lim, int pwd) {
		boolean r;
		if (lim > limite) // aumento de limite
			r = creditaValor(lim - limite);
		else
			// reducao de limite
			r = debitaValor(limite - lim, pwd);
		if (r)
			limite = lim; // se lancamento ok, altera o limite atual
		return r;
	} // fim de alteraLimite( )

	public double getCreditoUsado(int pwd) {
		double s;
		s = getSaldo(pwd); // obtem saldo atual
		if (s == -1) // senha invalida
			return (-1); // falha
		return (s > limite ? 0 : limite - s); // retorna zero se o limite nao
												// foi usado
	} // fim de getCreditoUsado( )

	public final boolean debitaValor(double val, int pwd) {
		System.out.println("debitaValor ContaEsp");
		boolean r;
		if (limite == 0)// conta especial e tratada como uma
						// conta comum
			return super.debitaValor(val, pwd);
		else {
			r = super.debitaValor(val, pwd);
			if (r && (getEstado() == INATIVA))// conta especial inativa
				setEstado(ATIVA); // conta especial ativa
			return r;
		}
	}// fim redefinicao de debitaValor

} // fim da classe ContaEsp


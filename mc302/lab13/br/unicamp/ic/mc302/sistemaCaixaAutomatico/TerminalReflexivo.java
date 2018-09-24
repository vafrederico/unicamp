package br.unicamp.ic.mc302.sistemaCaixaAutomatico;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.io.StreamTokenizer;
import java.lang.reflect.*;
public class TerminalReflexivo {
		
	private int getInt(String str) {


		System.out.println("Entre com "+str);

		// lÃª os valores digitados na entrada padrÃ£o
		Reader r = new BufferedReader(new InputStreamReader (System.in));
		StreamTokenizer st = new StreamTokenizer(r);

		try {
			st.nextToken();
		}
		catch (IOException e) {
			System.out.println("Erro na leitura do teclado");
			return(0);
		}

		return((int)st.nval);
	}




	private int getOp() {
		int op;

		do {

			op=getInt
					("opcao: \n1 = Imprimir a hierarquia de classes da classe ContaCor;\n2 = Imprimir todos os atributos da classe de Caixa;\n3 = Imprimir todos os métodos públicos da classe CadastroContas;\n4 = Realizar uma operação de crédito em uma conta usando o meta-nível ao invés do nível base;\n9 = Sair.");
			if (op < 1 || op > 4) op=0;

		} while (op==0);
		return(op);
	}

	public void iniciarOperacao (){
		int op;	// cÃ³digo da operaÃ§Ã£o solicitada 
		op=getOp();
		while (op!=9) {
			switch (op) {
				case 1:
					System.out.println("a");
					try {
						Class cls = Class.forName("br.unicamp.ic.mc302.sistemaCaixaAutomatico.ContaCor");
						Class sup;
						System.out.println(cls.getSimpleName());

						do {
							sup = cls.getSuperclass();
							System.out.println(sup.getSimpleName());
							
						} while (!sup.getSimpleName().equals("Object"));
						
					} catch (ClassNotFoundException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					
					break;
	
				case 2:
					try {
						Class cls = Class.forName("br.unicamp.ic.mc302.sistemaCaixaAutomatico.ContaCor");
						System.out.println(cls.getSimpleName());
						Field[] atributos = cls.getDeclaredFields();
						for(Field f: atributos){
							System.out.println(f.getName());
						}
					} catch (ClassNotFoundException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					
					break;
	
				case 3:
					try {
						Class cls = Class.forName("br.unicamp.ic.mc302.sistemaCaixaAutomatico.CadastroContas");
						System.out.println(cls.getSimpleName());
						Method[] metodos = cls.getMethods();
						for(Method m: metodos){
							System.out.println(m.getName());
						}
					} catch (ClassNotFoundException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					
					break;
	
				case 4:
					ContaCor c = new ContaCor("bob", 100, 1, 1);
					try {
						Class cls;
						cls = Class.forName("br.unicamp.ic.mc302.sistemaCaixaAutomatico.ContaCor");
	
						Field f = cls.getDeclaredField("saldoAtual");
						System.out.println(c.obterSaldo(1));
						f.setAccessible(true);
						f.setFloat(c, 200);
						System.out.println(c.obterSaldo(1));
						break;
					} catch (ClassNotFoundException | NoSuchFieldException | SecurityException | IllegalArgumentException | IllegalAccessException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
			}
			op=getOp();
		}
	}

}

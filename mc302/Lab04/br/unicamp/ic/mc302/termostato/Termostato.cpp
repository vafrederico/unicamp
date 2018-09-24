#include <iostream>
using namespace std;

class Termometro {
	private:
		int temperatura;
	public:
		int getTemperatura() {
			return temperatura;
		}
		int setTemperatura(int nTemp) {
			temperatura = nTemp;
		}
};

class Chave {
	private:
		int estadoChave; // 0 - desligada; 1 - ligada
	public:
		void ligar() {
			this -> estadoChave = 1;
		}
		void desligar() {
			this -> estadoChave = 0;
		}
		int getEstadoChave() {
			return estadoChave;
		}
};

class Termostato: public Termometro, public Chave {
	private:
		int tempRequerida;
	public:
		Termostato(int nTemp) {
			tempRequerida = nTemp;
		}
		void setTempRequerida(int nTemp) {
			if(nTemp > 0)
				tempRequerida = nTemp;
		}
		void fazerMonitoramento() {
			if(getTemperatura() < tempRequerida) {
				ligar();
			} else {
				desligar();
			}
		}
};

int main() {
	Termostato *t = new Termostato(25);
	t->desligar();
	t->setTemperatura(20);

	cout << "estado inicial: " << t->getEstadoChave() << endl;
	t->fazerMonitoramento();
	cout << "estado final: " << t->getEstadoChave() << endl;

	return 0;
}

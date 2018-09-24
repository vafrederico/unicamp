#include <iostream>
using namespace std;

class Veiculo {
	public:
		int placa;
		int peso;
};

class vPasseio: public virtual Veiculo {
	public:
		int numBancos;
		void display() {
			cout << "Numero de bancos: " << numBancos << endl;
		}
};

class vCarga: public virtual Veiculo {
	public:
		int capacidadeCarga;
		void display() {
			cout << "Capacidade de carga: " << capacidadeCarga << endl;
		}
};

class vUtilitario: public vPasseio, public vCarga {
	public:
		int pesoUtil;
};

int main() {
	vUtilitario *vu = new vUtilitario();
	vu -> peso = 3500;
	vu -> numBancos = 2;
	vu -> capacidadeCarga = 1000;
	vu->display();
	return 0;
}
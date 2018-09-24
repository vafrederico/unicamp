#include <iostream>
using namespace std;

class Lista { 
       // lista de inteiros
	private: 
	     struct node {
		int num;
	        node *link;
	      }*p;
	public:
	      Lista();	      
	      void adicionaInicio(int x);
	      int removeInicio();
	      int removeFim();
	      void adicionaFim(int x);
};

Lista::Lista() {
    p=NULL;
};

void Lista::adicionaInicio(int x) {
    // x é a nova cabeça da lista
    node *q;
    q = new node;
    q->num = x;
    q->link = p;
    p = q;
};
	      
int Lista::removeInicio() {
    // remove e retorna o valor final da lista
    node *q;
    int res;
    if (p!=NULL) {
	q = p;
	p = p->link;
	res = q->num;
	delete q;
	return res;
    }
    else {
      cout<< "\nLista Vazia";
      return 0;
    }
};
     
int Lista::removeFim() {
    // remove e retorna o último elemento da lista
    node *q,*t;
    int res;
    if ( p != NULL ) {
	t = NULL;
	q = p;
	while( q->link != NULL ) {
	  t = q;
	  q = q->link;
	}
	if (t!=NULL) {
	    t->link = NULL;
	    res = q->num;
	    delete q;
	    return res;
	}
	else {
	    res = p->num;
	    delete p;
	    p = NULL;
	    return res;
	}
    }
    else {
      cout<< "\nListaVazia";
      return 0;
    }
};
	      
void Lista::adicionaFim(int x) {
    // x torna-se o último elemento da lista
    node *q,*t;
    if( p == NULL ) {
	p = new node;
	p->num = x;
	p->link = NULL;
    }
    else {
	q = p;
	while ( q->link != NULL )
	    q = q->link;
	t = new node;
	t->num = x;
	t->link = NULL;
	q->link = t;
    }
};


class Pilha : public Lista {
	public:
	      Pilha() { Lista (); };	      
	      void empilha (int x) { adicionaFim(x); }	      
	      int desempilha() { return removeFim(); }
};

int main() {
      Lista* lst = new Lista();
      lst->adicionaInicio(10);
      lst->adicionaFim(20);
      cout<< "\nValor retornado: " << lst->removeFim();
      cout<< "\nValor retornado: " << lst->removeInicio();
      
      Pilha* plh = new Pilha();
      plh->empilha(30);
      cout<< "\nValor retornado: " << plh->desempilha();
      plh->empilha(40);
      plh->adicionaInicio(50);
      cout<< "\nValor retornado: " <<plh->desempilha();
      cout<< "\nValor retornado: " <<plh->desempilha();
      return 0;
};


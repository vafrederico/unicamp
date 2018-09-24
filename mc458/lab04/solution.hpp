#include <vector>
#include <iostream>
#include <utility>
#include <stdlib.h>
using namespace std;

int preenche_matriz(vector<int> &input, vector< vector<int> > &matriz);
vector<int> recuperacao(vector<int> &input, vector< vector<int> > &matriz, int coluna_final);
void print(vector<vector<int> > matriz);
//retorna as empresas ( em qualquer ordem) de uma das torres. As empresas restantes são colocadas na outra torre.
vector<int> solution(vector<int> & input) {

	int tamanho = 0;
	int soma = 0;
	for (int i = 0; i < input.size(); i++){
		soma += input[i	];
	}
	// Melhor tamanho possível é metade de todos
	tamanho = (soma % 2?1:0) + soma / 2;

	// Inicializa matriz
	vector< vector<int> > matriz;
	matriz.resize(input.size()+1);
	for (int i = 0; i <= input.size(); i++){
		matriz[i].resize(tamanho+1);
	}
	for (int i = 0; i <= tamanho; i++){
		matriz[0][i] = 0;
	}
	for (int i = 1; i <= input.size(); i++){
		matriz[i][0] = 0;
	}

	// Preenche matriz com máximos de andares ocupados para cada tamanho
	preenche_matriz (input, matriz);

	// Busca coluna em que o máximo seja igual ao tamanho do prédio
	int coluna_final = 0;
	for (int i = matriz[0].size()-1; i >= 0; i--){
		if(i == matriz[matriz.size()-1][i]){
			coluna_final = i;
			break;
		}
	}
	// Recupera quais itens são utilizados para construção daquele andar
	vector<int> items = recuperacao(input, matriz, coluna_final);
	return items;
}

// Algoritmo da mochila visto em aula
int preenche_matriz(vector<int> &input, vector< vector<int> > &matriz){
	int maximo_atual;
	for (int i = 1; i <= input.size(); i++){
		for(int j = 1; j < matriz[0].size(); j++){
			matriz[i][j] = matriz[i-1][j];
			if (input[i-1] <= j && input[i-1] + matriz[i-1][j-input[i-1]] > matriz[i][j]){
				matriz[i][j] = input[i-1] + matriz[i-1][j-input[i-1]];
			}
		}
	}

}

// Algoritmo de recuperação da mochila visto em aula
vector<int> recuperacao(vector<int> &input, vector< vector<int> > &matriz, int coluna_final){
	vector<int> items;
	int i = matriz.size()-1;
	int j = coluna_final;
	while (i > 0){
		if (matriz[i][j] != matriz[i-1][j]){
			items.resize(items.size() + 1);
			items[items.size()-1] = i-1;
			j -= input[i-1];
		}
		i -= 1;
	}
	return items;
}

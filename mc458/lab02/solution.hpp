#include "pint.hpp"
#include <vector>
#include <iostream>
#include <utility>
#include <stdlib.h>
#include <map>

using namespace std;

int intercala(vector<Pint> & input, vector<int> & posicoes, int p, int q, int r);
int mergesort(vector<Pint> & input, vector<int> & posicoes, int p, int r);

//retorna o custo total
int solution(vector<Pint> & input) {

  int size = input.size();
  // vetor com os indíces, conterá no final, os índices de input ordenados pelo valor do Pint
  vector<int> posicoes(input.size(), -1);
  int inversoes = mergesort(input, posicoes, 0, size - 1);

  // acha maior distancia
  int maxDist = 0;
  for(int i = 0; i<size; i++){
    maxDist = max(abs(posicoes[i] - i), maxDist);
  }
  
  return inversoes*maxDist;
}

/** Algoritmo de mergesort */
int mergesort(vector<Pint> & input, vector<int> & posicoes, int p, int r){
  
  if (p >= r){
    return 0;
  }

  int q = (p + r)/2;
  int inversoes = mergesort(input, posicoes, p, q);
  inversoes += mergesort(input, posicoes, q+1, r);
  inversoes += intercala(input, posicoes, p, q, r);
  return inversoes;
}

int intercala(vector<Pint> & input, vector<int> & posicoes, int p, int q, int r){
  
  int size = r -p + 1;
  vector<int> aux(size, 0);
  int inversoes = 0;
  int i, j, k;
  
  // popula vetor auxiliar com o indice já ordenado previamente em posicoes ou com o indice em input
  // para primeira metade
  j = 0;
  for (i = p; i <= q; i++){
    if(posicoes[i] != -1)
      aux[j++] = posicoes[i];
    else
      aux[j++] = i;
  }
  j = aux.size() - 1;
  
  // para outra metade
  for (i = q+1; i <= r; i++){
    if(posicoes[i] != -1)
      aux[j--] = posicoes[i];
    else
      aux[j--] = i;
  }
  i = 0;
  j = aux.size() -1;

  // intercalando os valores
  for (int k = p; k <= r; k++) {
    // se ainda não colocou todos valores da esquerda e esquerda < direita, ou, colocou todos da direita
    // adiciona elemento da esquerda
    if (i + p <= q && input[aux[i]].compare(input[aux[j]]) == -1 || p + j == q){
      posicoes[k] = aux[i++];
    } else {
      posicoes[k] = aux[j--];
      // se está colocando elementos da direita, e ainda tem elemento na esquerda, 
      // o número de elementos na esquerda é o número de inversões
      if (i + p <= q){
        inversoes += (q - p - i + 1);        
      }
    }
  }
  return inversoes;

}
#include "pint.hpp"
#include <vector>
#include <iostream>
#include <utility>
#include <stdlib.h>


using namespace std;

//pares utilizados para reduzir o código
typedef pair<int,int> pii;
typedef pair<Pint,int> ppi;

int intercala(vector<Pint> & input, vector<int> & posicoes, int p, int q, int r);
int mergesort(vector<Pint> & input, vector<int> & posicoes, int p, int r);
void mergesort_ppi(vector<ppi> & input, int p, int r);
void intercala_ppi(vector<ppi> & input, int p, int q, int r);
vector<ppi> find_maxes(vector<ppi> & input, int start, int end, int num_maxes);

vector<ppi> solution(vector<vector<ppi> > & input,int M) {
  vector<Pint> medias(input.size(), 0);
  vector<int> posicoes(medias.size(), -1);
  // Calcula médias
  for (int i = 0; i < input.size(); i++){
    Pint soma = Pint(0);
    for (int j = 0; j < input[i].size(); j++){
      soma = soma + input[i][j].first;
    }
    medias[i] = soma/input[i].size();
  }

  // Ordena médias e guarda índices ordenados em posicoes
  mergesort(medias, posicoes, 0, medias.size() - 1);
  
  ppi aux1;
  vector<ppi> out(M);
  vector<vector<ppi> > maximos;
  maximos.resize(input.size());
  // Número de máximos necessário em cada escola = Vagas/# de escolas + 1
  int num_maxes = M/input.size() + 1;
  // Para cada escola
  for (int k = 0; k < input.size(); k++){
    // Procura os máximos necessários
    vector <ppi> max = find_maxes(input[k], 0, input[k].size()-1, num_maxes);
    // Ordena os máximos
    mergesort_ppi(max, 0, num_maxes-1);
    maximos[k] = max;
  }

  int escola = 0;
  ppi max;
  int escola_atual;
  int pos_vetor = 0;
  // Para cada vaga
  for (int i = 0; i < M; i++)
  {
    // Escola que deve ser usada à partir da ordenação
    escola_atual = posicoes[posicoes.size() - (escola++) - 1];
    // Obtém o máxmo
    max = maximos[escola_atual][num_maxes -1 - pos_vetor];
    out[i] = max;
    // Soma à posição do vetor e começa da primeira escola caso todas escolas tenham preenchido vaga nessa rodada
    if(escola == input.size()){
      escola = 0;
      pos_vetor++;
    }
  }

  return out;
}

vector<ppi> find_maxes(vector<ppi> & input, int start, int end, int num_maxes){
  if(end == 0) return input;
  int size = end - start + 1;

  // Pivo aleatório
  int pivo = rand() % end;
  int maiores_count = 0, menores_count = 0;
  vector<ppi> maiores(size);
  vector<ppi> menores(size);

  // Particiona vetor em menores ou maiores
  for (int i = start; i <= end; i++){
    if(i == pivo) continue;
    int compare = input[i].first.compare(input[pivo].first);
    if(compare == 1){
      maiores[maiores_count++] = input[i];
    } else {
      menores[menores_count++] = input[i];
    }
  }

  // Se temos o número de máximos necessário, retorna
  if (maiores_count == num_maxes) {
    return maiores;
  } else if (maiores_count < num_maxes) {
    // Se falta maiores, adiciona o pivô e pega os máximos dos menores para completar
    maiores[maiores_count++] = input[pivo];
    vector<ppi> maiores_menores = find_maxes(menores, 0, menores_count - 1, num_maxes-maiores_count);
    for (int i = 0; i < maiores_menores.size() && maiores_count + i < maiores.size(); i++){
      maiores[maiores_count + i] = maiores_menores[i];
    }
    return maiores;
  }
  // Se há maiores além do necessário, procura os máximos no vetor de maiores
  return find_maxes(maiores, 0, maiores_count - 1, num_maxes);
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

  // print_vector(aux);
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

/** Algoritmo de mergesort */
void mergesort_ppi(vector<ppi> & input, int p, int r){
 
  if (p >= r){
    return;
  }

  int q = (p + r)/2;
  mergesort_ppi(input, p, q);
  mergesort_ppi(input, q+1, r);
  intercala_ppi(input, p, q, r);
}

void intercala_ppi(vector<ppi> & input, int p, int q, int r){
  
  int size = r -p + 1;
  vector<ppi> aux;
  aux.resize(size);

  int i, j, k;
  
  j = 0;
  for (i = p; i <= q; i++){
      aux[j++] = input[i];
  }
  j = aux.size() - 1;
  
  // para outra metade
  for (i = q+1; i <= r; i++){
      aux[j--] = input[i];
  }
  i = 0;
  j = aux.size() -1;

  // intercalando os valores
  for (int k = p; k <= r; k++) {
    // se ainda não colocou todos valores da esquerda e esquerda < direita, ou, colocou todos da direita
    // adiciona elemento da esquerda
    if (i + p <= q && aux[i].first.compare(aux[j].first) == -1 || p + j == q){
      input[k] = aux[i++];
    } else {
      input[k] = aux[j--];
    }
  }
}
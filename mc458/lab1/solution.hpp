#include "pint.hpp"
#include <vector>
#include <iostream>
#include <math.h>
using namespace std;

// retornar o indice (começando em 0) da embalagem mais leve
int solution(const vector<Pint> & input) {
  
  int start = 0, end = input.size() - 1;
  // Divide a entrada em 3 blocos
  int blockSize = input.size() / 3;
  // Enquanto tiver 2 ou mais elementos no subvetor
  while (end - start + 1 > 2) {
    Pint firstBlock = Pint(0);
    Pint secondBlock = Pint(0);
    
    // Soma os blocos
    for (int i = 0; i < blockSize; i++){
      firstBlock = firstBlock + input[start + i];
      secondBlock = secondBlock + input[start + i + blockSize];
    }

    int comparison = firstBlock.compare(secondBlock);
    if (comparison == 0){
      // Igual -> rodar 3o bloco
      start = start + blockSize * 2;
    } else if(comparison < 0) {
      // -1 -> Primeiro bloco < segundo, rodar primeiro
      end = start + blockSize - 1;
    } else {
      // 1 - > segundo < primeiro, rodar segundo
      start = start + blockSize;
      end = start + blockSize - 1;
    }

    // Tamanho do bloco = tamanho a olhar dividido por 3 arredondando pra cima
    blockSize = ceil((end - start + 1)/3.0);
  } 
  
  // Se tiver 2 elementos, retorna o menor
  if(end - start + 1 == 2){
    int comparison = input[start].compare(input[start + 1]);
    if (comparison == 1) {
      return start + 1;
    } else {
      return start;
    }

  } else {
    // Se tiver 1 elemento, retorna ele mesmo
    return start;
  }
  
}
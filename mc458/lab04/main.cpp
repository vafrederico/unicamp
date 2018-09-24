#include "solution.hpp"
#include <vector>
#include <iostream>

//constroi as torres e retorna a altura da mais alta
int verify(std::vector<int> & input, std::vector<int> & first_tower) {
  // inicialmente todas as empresas estao na segunda torre
  int second_tower_p = 0;
  for(int i = 0; i < input.size();i++)
    second_tower_p += input[i];

  //transfere as empresas para a primeira torre
  int first_tower_p = 0;
  for(int i = 0; i < first_tower.size();i++) {
    first_tower_p += input[first_tower[i]];
    second_tower_p -= input[first_tower[i]];
  }

  return std::max(first_tower_p, second_tower_p);
}
void execute_test(std::vector<int> & input) {
  std::vector<int> first_tower = solution(input);
  int ans = verify(input,first_tower);
  std::cout << ans << std::endl;
}

int main(int argc, char ** argv) {
  int N;
  std::vector<int> input;

  std::cin >> N;
  input.resize(N);
  for(int i = 0; i < N;i++) {
    std::cin >> input[i];
  }

  execute_test(input);
}



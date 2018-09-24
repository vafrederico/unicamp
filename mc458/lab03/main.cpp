#include "pint.hpp"
#include "solution.hpp"
#include <vector>
#include <iostream>

//ppi = pair<Pint,int> para acessar use input[i][j].first e input[i][j].second
void execute_test(std::vector<vector<ppi> >&input,
                  int M,
                  int max_num_comparisons) {
  vector<ppi> output = solution(input, M);
  for(int i = 0; i < output.size();i++) {
    if(i != 0)
      std::cout << " ";
    std::cout << output[i].second << " ";
    output[i].first.print();
  }

  std::cout << std::endl;

  int num_comparisons = Pint::getNumComparisons();
  if(num_comparisons <= max_num_comparisons)
    std::cout << "OK" << std::endl;
  else
    std::cout << "Numero excessivo de comparacoes" << std::endl;

  // std::cout << " comparacoes : " << num_comparisons << endl;
}

int main(int argc, char ** argv) {
  int K,M,N;
  std::vector<std::vector<ppi> > input;
  int max_num_comparisons;

  std::cin >> K >> M >> N;
  std::cin >> max_num_comparisons;
  input.resize(K);
  for(int i = 0; i < K;i++) {
    input[i].resize(N);
    for(int j = 0; j < N;j++) {
      int id, value;
      std::cin >> id >> value;
      input[i][j] = ppi(value,id);
    }
  }

  execute_test(input, M, max_num_comparisons);
}



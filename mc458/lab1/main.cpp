#include "pint.hpp"
#include "solution.hpp"
#include <vector>
#include <iostream>

void execute_test(const std::vector<Pint>&input,
                  int max_num_comparisons) {
  int output = solution(input);
  std::cout << output << std::endl;

  int num_comparisons = Pint::getNumComparisons();
  if(num_comparisons < max_num_comparisons)
    std::cout << "OK" << std::endl;
  else
    std::cout << "Numero excessivo de comparacoes" << std::endl;
}

int main(int argc, char ** argv) {
  int input_size;
  std::vector<Pint> input;
  int max_num_comparisons;

  std::cin >> input_size;
  std::cin >> max_num_comparisons;
  input.resize(input_size);
  for(int i = 0; i < input_size;i++) {
    int value;
    std::cin >> value;
    input[i] = Pint(value);
  }

  execute_test(input, max_num_comparisons);
	
  return 0;
}



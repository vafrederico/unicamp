#include "pint.hpp"
#include <iostream>
int Pint::num_comparisons = 0;

Pint::Pint(int value) {
  this->value = value;
}

int Pint::compare(const Pint & o) const {
  num_comparisons++;
  if(value == o.value)
    return 0;
  if(value < o.value)
    return -1;
  return 1;
}

Pint Pint::operator + (const Pint & o) const {
  return Pint(value+o.value);
}

void Pint::print() const{
  std::cout << value; 
}

int Pint::getNumComparisons(){
  return num_comparisons; 
}

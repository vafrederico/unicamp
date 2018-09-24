#pragma once

class Pint {
  private:
    int value;
    static int num_comparisons;
  public:
  Pint(int value=0);

  //compara com outro Pint
  //Retorno:
  //  -1: *this < o
  //   0: *this == o
  //   1: *this > o
  int compare(const Pint & o) const;
  Pint operator + (const Pint & o) const;
  Pint operator / (const Pint & o) const;
  void print() const;
  static int getNumComparisons();
};

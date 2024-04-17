#include <iostream>

#include "trinary.h"

int main() {
  trinary<16> trit1(8000.0);
  trinary<16> trit2(0.8);
  std::cout << (trit1 * trit2).to_double() << '\n';
  std::cout << trit2.to_double() << '\n';
  std::cout << trit1 << '\n';
  return 0;
}
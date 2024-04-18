#include <iostream>

#include "trinary.h"

int main() {
  trinary<32> trit1(12.5);
  trinary<32> trit2(0.5);
  std::cout << (trit2 - trit1).to_double() << '\n';
  std::cout << (trit1 / trit2).to_double() << '\n';
  trit1 += trit2;
  std::cout << trit1.to_double() << '\n';
  std::cout << trit1 << '\n';
  trit1 *= trit2;
  std::cout << trit1.to_double() << '\n';
  std::cout << trit1 << '\n';
  return 0;
}

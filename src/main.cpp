#include <iostream>

#include "trinary.h"

int main() {
  trinary<32> trit1(1.5f);
  trinary<32> trit2(555.5f);
  trit1.draw_raw();
  trit2.draw_raw();
  std::cout << (trit2 - trit1).to_double() << '\n';
  trit1.draw_raw();
  std::cout << trit2.to_double() << '\n';
  return 0;
}
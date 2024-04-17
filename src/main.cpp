#include <iostream>

#include "trinary.h"

int main() {
  trinary<32> trit1(1.3f);
  trinary<32> trit2(0.7f);
  trit1.draw_raw();
  trit2.draw_raw();
  trit1 += trit2;
  std::cout << trit1.to_double() << '\n';
  trit1.draw_raw();
  std::cout << trit2.to_double() << '\n';
  return 0;
}
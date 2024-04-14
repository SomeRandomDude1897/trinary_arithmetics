#include <iostream>

#include "trinary.h"

int main() {
  trinary<32> trit1(12.12f);
  trinary<32> trit2(12.25f);
  trinary<32> trit3(24.37f);
  trit1.draw_raw();
  trit2.draw_raw();
  trit1 += trit2;
  trit1.draw_raw();
  trit3.draw_raw();
  return 0;
}
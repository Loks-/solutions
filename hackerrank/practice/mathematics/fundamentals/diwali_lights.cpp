// https://www.hackerrank.com/challenges/diwali-lights

#include "common/modular_io.h"
#include "common/stl/base.h"

using TModular = ModularComposite32<100000>;

int main_diwali_lights() {
  unsigned T, N;
  TModular two(2);
  cin >> T;
  for (unsigned it = 0; it < T; ++it) {
    cin >> N;
    cout << two.PowU(N) - 1 << endl;
  }
  return 0;
}

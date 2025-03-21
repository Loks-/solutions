// https://www.hackerrank.com/challenges/summing-the-n-series

#include "common/modular_io.h"
#include "common/stl/base.h"

int main_summing_the_n_series() {
  unsigned T;
  cin >> T;
  for (unsigned it = 0; it < T; ++it) {
    ModularDefault n;
    cin >> n;
    cout << n.PowU(2) << endl;
  }
  return 0;
}

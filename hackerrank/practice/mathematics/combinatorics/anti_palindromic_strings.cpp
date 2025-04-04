// https://www.hackerrank.com/challenges/antipalindromic-strings

#include "common/modular_io.h"
#include "common/stl/base.h"

int main_anti_palindromic_strings() {
  unsigned T, N, M;
  cin >> T;
  for (unsigned iT = 0; iT < T; ++iT) {
    cin >> N >> M;
    if (N == 1)
      cout << M << endl;
    else if (M == 1)
      cout << 0 << endl;
    else
      cout << ModularDefault(M - 2).PowU(N - 2) * (M - 1) * M << endl;
  }
  return 0;
}

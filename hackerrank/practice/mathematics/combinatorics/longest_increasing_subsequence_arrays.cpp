// https://www.hackerrank.com/challenges/longest-increasing-subsequence-arrays

#include "common/modular/static/factorial.h"
#include "common/modular_io.h"
#include "common/stl/base.h"

using TFactorial = modular::mstatic::Factorial<ModularDefault>;

int main_longest_increasing_subsequence_arrays() {
  TFactorial f;
  unsigned T, n, m;
  cin >> T;
  for (unsigned iT = 0; iT < T; ++iT) {
    cin >> m >> n;
    f.Adjust(m);
    ModularDefault s = 0, k = ModularDefault(n - 1) / ModularDefault(n), p = 1;
    for (unsigned l = n; l <= m; ++l, p *= k)
      s += f.BinomialCoefficient(l - 1, n - 1) * p;
    cout << s * ModularDefault(n).PowU(m - n) << endl;
  }
  return 0;
}

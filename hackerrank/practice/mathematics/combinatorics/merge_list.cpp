// https://www.hackerrank.com/challenges/merge-list

#include "common/modular/static/factorial.h"
#include "common/modular_io.h"
#include "common/stl/base.h"

using TFactorial = modular::mstatic::Factorial<ModularDefault>;

int main_merge_list() {
  TFactorial f;
  unsigned T, n, m;
  cin >> T;
  for (unsigned iT = 0; iT < T; ++iT) {
    cin >> n >> m;
    cout << f.BinomialCoefficient(n + m, n) << endl;
  }
  return 0;
}

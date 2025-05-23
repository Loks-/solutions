// https://www.hackerrank.com/challenges/picking-cards

#include "common/modular_io.h"
#include "common/stl/base.h"
#include "common/vector/read.h"

int main_picking_cards() {
  unsigned T, n;
  cin >> T;
  for (unsigned iT = 0; iT < T; ++iT) {
    cin >> n;
    vector<unsigned> v = nvector::Read<unsigned>(n);
    sort(v.begin(), v.end());
    v.push_back(n);
    ModularDefault r = 1;
    for (unsigned i = 0, j = 0; i < n; ++i) {
      for (; v[j] <= i;) ++j;
      r *= max(i, j) - i;
    }
    cout << r << endl;
  }
  return 0;
}

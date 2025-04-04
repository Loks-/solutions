// https://www.hackerrank.com/challenges/hyperrectangle-gcd

#include "common/modular_io.h"
#include "common/stl/base.h"
#include "common/vector/min.h"
#include "common/vector/read.h"

int main_hyperrectangle_gcd() {
  vector<ModularDefault> v(100001);
  unsigned T, K;
  cin >> T;
  for (unsigned iT = 0; iT < T; ++iT) {
    cin >> K;
    vector<unsigned> vnk = nvector::Read<unsigned>(K);
    unsigned n0 = nvector::Min(vnk);
    for (unsigned i = 1; i <= n0; ++i) {
      v[i] = 1;
      for (unsigned nk : vnk) v[i] *= ModularDefault(nk / i);
    }
    ModularDefault s = 0;
    for (unsigned i = n0; i; --i) {
      for (unsigned j = 2 * i; j <= n0; j += i) v[i] -= v[j];
      s += v[i] * ModularDefault(i);
    }
    cout << s << endl;
  }
  return 0;
}

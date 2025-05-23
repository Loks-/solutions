// https://www.hackerrank.com/challenges/hyperrectangle-gcd

#include "common/factorization/table/eulers_totient.h"
#include "common/modular_io.h"
#include "common/stl/base.h"
#include "common/vector/min.h"
#include "common/vector/read.h"

int main_hyperrectangle_gcd__totient() {
  factorization::table::EulersTotient eulers_totient(100000);
  unsigned T, K;
  cin >> T;
  for (unsigned iT = 0; iT < T; ++iT) {
    cin >> K;
    vector<unsigned> vnk = nvector::Read<unsigned>(K);
    unsigned n0 = nvector::Min(vnk);
    ModularDefault s = 0;
    for (unsigned i = 1; i <= n0; ++i) {
      ModularDefault t = eulers_totient(i);
      for (unsigned nk : vnk) t *= ModularDefault(nk / i);
      s += t;
    }
    cout << s << endl;
  }
  return 0;
}

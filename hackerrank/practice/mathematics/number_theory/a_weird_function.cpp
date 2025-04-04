// https://www.hackerrank.com/challenges/a-weird-function

#include "common/factorization/table/eulers_totient.h"
#include "common/local.h"
#include "common/stl/base.h"

int main_a_weird_function() {
  const uint64_t maxi = kIsLocalRun ? 1000000ull : 1000000000000ull;
  factorization::table::EulersTotient eulers_totient(kIsLocalRun ? 1500
                                                                 : 1500000);
  vector<uint64_t> vi, vs(1, 0);
  uint64_t phi1 = 1, phi2 = 1;
  for (uint64_t j = 2;; ++j) {
    uint64_t i = (j * (j - 1)) / 2;
    if (i > maxi) break;
    vi.push_back(i);
    phi1 = phi2;
    phi2 = eulers_totient(j & 1 ? j : j / 2);
    vs.push_back(vs.back() + phi1 * phi2);
  }
  unsigned T;
  cin >> T;
  for (unsigned it = 0; it < T; ++it) {
    uint64_t l, r;
    cin >> l >> r;
    size_t i1 = lower_bound(vi.begin(), vi.end(), l) - vi.begin();
    size_t i2 = upper_bound(vi.begin(), vi.end(), r) - vi.begin();
    cout << vs[i2] - vs[i1] << endl;
  }
  return 0;
}

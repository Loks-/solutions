// https://www.hackerrank.com/challenges/divisor-exploration-2

#include "common/factorization/primes_list.h"
#include "common/modular_io.h"
#include "common/stl/base.h"

int main_divisor_exploration_ii() {
  factorization::PrimesList primes_list(2000000);
  const vector<uint64_t>& primes = primes_list.GetPrimes();
  unsigned T, m, a;
  cin >> T;
  for (unsigned it = 0; it < T; ++it) {
    TModularD r = 1, one = 1;
    cin >> m >> a;
    for (unsigned i = 0; i < m; ++i) {
      TModularD p = primes[i];
      r *= ((p.PowU(a + i + 2) - one) / (p - one) * p - TModularD(a + i + 2)) /
           (p - one);
    }
    cout << r << endl;
  }
  return 0;
}

// https://www.hackerrank.com/challenges/gcd-product

#include "common/factorization/primes_range.h"
#include "common/modular_io.h"
#include "common/stl/base.h"

int main_gcd_product() {
  uint64_t n, m;
  cin >> n >> m;
  if (n < m) swap(n, m);
  ModularDefault r = 1;
  for (uint64_t p : factorization::PrimesRange(m)) {
    for (uint64_t pp = p; pp <= m; pp *= p)
      r *= ModularDefault(p).PowU((m / pp) * (n / pp));
  }
  cout << r << endl;
  return 0;
}

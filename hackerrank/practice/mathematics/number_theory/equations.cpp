// https://www.hackerrank.com/challenges/equations

#include "common/factorization/primes_range.h"
#include "common/modular_io.h"
#include "common/stl/base.h"

using TModular = ModularPrime32<1000007>;

int main_equations() {
  uint64_t n;
  cin >> n;
  TModular r = 1;
  for (uint64_t p : factorization::PrimesRange(n)) {
    uint64_t c = 0;
    for (uint64_t t = n / p; t; t /= p) c += t;
    r *= TModular(2 * c + 1);
  }
  cout << r << endl;
  return 0;
}

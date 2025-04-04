// https://www.hackerrank.com/challenges/manasa-and-combinatorics

#include "common/modular/static/binomial_coefficient_prime.h"
#include "common/modular_io.h"
#include "common/stl/base.h"

using TModular = ModularPrime32<99991>;

int main_manasa_and_combinatorics() {
  unsigned T;
  cin >> T;
  for (unsigned iT = 0; iT < T; ++iT) {
    uint64_t n;
    cin >> n;
    cout << modular::mstatic::BinomialCoefficientPrime<TModular>(3 * n, n) -
                modular::mstatic::BinomialCoefficientPrime<TModular>(3 * n,
                                                                     n - 1) *
                    2 +
                modular::mstatic::BinomialCoefficientPrime<TModular>(3 * n,
                                                                     n - 2)
         << endl;
  }
  return 0;
}

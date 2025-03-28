// https://www.hackerrank.com/challenges/divisor-exploration

#include "common/modular_io.h"
#include "common/stl/base.h"

int main_divisor_exploration() {
  ModularDefault half = ModularDefault(2).Inverse();
  vector<ModularDefault> v(1, 1);
  for (unsigned i = 0; i < 200000; ++i)
    v.push_back(v.back() * ModularDefault(i + 3) * ModularDefault(i + 2) *
                half);
  unsigned T, m, a;
  cin >> T;
  for (unsigned it = 0; it < T; ++it) {
    cin >> m >> a;
    cout << v[a + m] / v[a] << endl;
  }
  return 0;
}

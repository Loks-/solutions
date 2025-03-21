// https://www.hackerrank.com/challenges/surveillance

#include "common/modular_io.h"
#include "common/stl/base.h"

int main_academy_surveillance() {
  unsigned maxn = 1000;
  vector<ModularDefault> p2(maxn / 3 + 2), p3(maxn / 3 + 2);
  p2[0] = p3[0] = 1;
  for (size_t i = 1; i < p2.size(); ++i) {
    p2[i] = ModularDefault(2) * p2[i - 1];
    p3[i] = ModularDefault(3) * p3[i - 1];
  }
  ModularDefault f = 36;
  vector<ModularDefault> fv(maxn + 1), fvv(maxn + 1);
  for (size_t i = 0; i <= maxn; ++i) {
    ModularDefault p2i0 = p2[i / 3], p2i1 = p2[(i + 1) / 3],
                   p2i2 = p2[(i + 2) / 3];
    ModularDefault p3i0 = p3[i / 3], p3i1 = p3[(i + 1) / 3],
                   p3i2 = p3[(i + 2) / 3];
    fv[i] = ModularDefault(6) * (p3i0 + p3i1 + p3i2) +
            ModularDefault(3) * (p2i0 + p2i1 + p2i2);
    fvv[i] = p3i0 * p3i1 + p3i0 * p3i2 + p3i1 * p3i2 + p3i0 + p3i1 + p3i2;
  }

  unsigned T, n, m;
  cin >> T;
  for (unsigned it = 0; it < T; ++it) {
    cin >> n >> m;
    ModularDefault r = fvv[n] + fvv[m] - fv[n] - fv[m] + f;
    for (unsigned i = 0; i < 3; ++i) {
      for (unsigned j = 0; j < 3; ++j) {
        uint64_t ni = (n + i) / 3, mi = (m + j) / 3;
        r += p2[ni] * p3[mi] + p3[ni] * p2[mi] - p2[ni] * p2[mi];
      }
    }
    cout << r << endl;
  }
  return 0;
}

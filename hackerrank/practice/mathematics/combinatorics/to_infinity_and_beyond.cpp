// https://www.hackerrank.com/challenges/to-infinity-and-beyond

#include "common/modular/static/factorial.h"
#include "common/modular_io.h"
#include "common/stl/base.h"

using TFactorial = modular::mstatic::Factorial<ModularDefault>;

int main_to_infinity_and_beyond() {
  TFactorial f;
  unsigned T;
  cin >> T;
  uint64_t x, y, z;
  for (unsigned it = 0; it < T; ++it) {
    cin >> x >> y >> z;
    unsigned mk = unsigned(min(x, y));
    ModularDefault s(0), v = f.GetI(mk);
    for (unsigned l = 1; l <= mk; ++l) v *= ModularDefault(x + y + 1 - l);
    ModularDefault a(1), b(1), c(1);
    v -= a * b;
    s += v;
    for (unsigned l = 1; l < mk; ++l) {
      a *= ModularDefault(x + 1 - l);
      b *= ModularDefault(y + 1 - l);
      c *= ModularDefault(z - l);
      v -= a * b * f.GetI(l) * f.GetI(l);
      s += v * c * f.GetI(l);
    }
    cout << s << endl;
  }
  return 0;
}

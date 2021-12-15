#include "common/geometry/d2/axis/rectangle.h"
#include "common/geometry/d2/point.h"
#include "common/geometry/d2/utils/neighbors.h"
#include "common/stl/base.h"
#include "common/vector/read_lines.h"

int main_2109a() {
  auto vs = nvector::ReadLines();
  int64_t n = vs.size(), m = vs[0].size();
  I2ARectangle b({0, 0}, {n - 1, m - 1});
  auto Get = [&](const I2Point& p) { return b.Inside(p) ? vs[p.x][p.y] : '9'; };

  unsigned r = 0;
  I2Point p;
  for (p.x = 0; p.x < n; ++p.x) {
    for (p.y = 0; p.y < m; ++p.y) {
      auto c = Get(p);
      if (c == '9') continue;
      bool low_point = true;
      for (auto p0 : I2NeighborsD4(p)) {
        if (Get(p0) <= c) low_point = false;
      }
      if (low_point) r += 1 + (c - '0');
    }
  }
  cout << r << endl;
  return 0;
}

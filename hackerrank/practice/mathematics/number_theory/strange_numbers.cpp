// https://www.hackerrank.com/challenges/strange-numbers

#include "common/heap.h"
#include "common/stl/base.h"

int main_strange_numbers() {
  uint64_t max_value = 1000000000000000000ull;
  auto length = [](uint64_t t) {
    uint64_t l = 0;
    for (; t; t /= 10) ++l;
    return l;
  };
  vector<uint64_t> v(1, 0);
  MinHeap<uint64_t> q;
  for (unsigned i = 1; i < 10; ++i) q.Add(i);
  for (; !q.Empty();) {
    uint64_t u = q.Extract();
    if (u <= v.back()) continue;
    v.push_back(u);
    for (uint64_t l = length(u);; ++l) {
      uint64_t u2 = u * l;
      if ((u2 > max_value) || (length(u2) < l)) break;
      if (length(u2) > l) continue;
      q.Add(u2);
    }
  }

  unsigned T;
  cin >> T;
  for (unsigned it = 0; it < T; ++it) {
    uint64_t l, r;
    cin >> l >> r;
    auto it1 = lower_bound(v.begin(), v.end(), l);
    auto it2 = upper_bound(v.begin(), v.end(), r);
    cout << it2 - it1 << endl;
  }
  return 0;
}

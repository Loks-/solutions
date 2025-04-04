// https://www.hackerrank.com/challenges/jesse-and-cookies

#include "common/heap.h"
#include "common/stl/base.h"
#include "common/vector/read.h"

int main_jesse_and_cookies() {
  unsigned N;
  int count = 0;
  uint64_t K, a1, a2;
  cin >> N >> K;
  auto v = nvector::Read<uint64_t>(N);
  MinHeap<uint64_t> q(v);
  for (; (q.Size() > 1) && (q.Top() < K);) {
    a1 = q.Extract();
    a2 = q.Extract();
    q.Add(a1 + 2 * a2);
    ++count;
  }
  cout << (((q.Size() > 0) && (q.Top() >= K)) ? count : -1) << endl;
  return 0;
}

// https://www.hackerrank.com/challenges/array-and-simple-queries

#include "common/binary_search_tree/base/to_vector.h"
#include "common/binary_search_tree/treap.h"
#include "common/binary_search_tree/utils/swap_intervals.h"
#include "common/stl/base.h"
#include "common/vector/read.h"
#include "common/vector/write.h"

using TTreap = bst::Treap<false, false, int>;
using TNode = TTreap::NodeType;

int main_array_and_simple_queries__treap() {
  unsigned N, M;
  cin >> N >> M;
  vector<int> va = nvector::Read<int>(N);
  TTreap treap(N);
  TNode* root = treap.build(va);
  for (; M; --M) {
    unsigned t, i, j;
    cin >> t >> i >> j;
    if (t == 1)
      bst::SwapIntervals<TTreap>(root, 0, i - 1, j);
    else
      bst::SwapIntervals<TTreap>(root, i - 1, j, N);
  }
  vector<int> vf = bst::base::to_vector(root);
  cout << abs(vf[0] - vf.back()) << endl;
  nvector::Write(vf);
  return 0;
}

#include "common/binary_search_tree/subtree_data/max.h"
#include "common/binary_search_tree/subtree_data/min.h"
#include "common/binary_search_tree/treap.h"
#include "common/stl/base.h"
#include "common/vector/read.h"

using TMin = bst::subtree_data::Min<int>;
using TMax = bst::subtree_data::Max<int>;
using TTree =
    bst::Treap<true, true, int, std::tuple<TMin, TMax>, std::tuple<>, int>;
using TNode = TTree::NodeType;

int main_fair_fight() {
  unsigned T;
  cin >> T;
  for (unsigned it = 1; it <= T; ++it) {
    int n, k;
    cin >> n >> k;
    TTree tree(2 * n + 4);
    vector<vector<int>> vv{nvector::Read<int>(n), nvector::Read<int>(n)};
    vector<TNode*> vh(4, 0);
    for (int j = 0; j < 2; ++j) {
      for (int i = 0; i < n; ++i) {
        TNode* p = tree.create_node(i, vv[j][i]);
        vh[2 * j + 1] = tree.insert(vh[2 * j + 1], p);
      }
    }
    for (int j = 0; j < 4; ++j) {
      TNode* p = tree.create_node((j & 1) ? n : -1, 300000);
      vh[j] = tree.insert(vh[j], p);
    }
    int64_t total = 0;
    TNode *p0, *p1;
    for (int i = 0; i < n; ++i) {
      int k0 = vv[0][i];
      tree.split(vh[0], k0, p0, p1);
      int l0 = TMax::get(p1);
      vh[0] = tree.join(p0, p1);
      tree.split(vh[1], k0 + 1, p0, p1);
      int r0 = TMin::get(p1);
      vh[1] = tree.join(p0, p1);
      tree.split(vh[2], k0 + k + 1, p0, p1);
      int l1 = TMax::get(p1);
      vh[2] = tree.join(p0, p1);
      tree.split(vh[3], k0 + k + 1, p0, p1);
      int r1 = TMin::get(p1);
      vh[3] = tree.join(p0, p1);
      tree.split(vh[2], k0 - k, p0, p1);
      int l2 = TMax::get(p1);
      vh[2] = tree.join(p0, p1);
      tree.split(vh[3], k0 - k, p0, p1);
      int r2 = TMin::get(p1);
      vh[3] = tree.join(p0, p1);
      l1 = max(l0, l1);
      l2 = max(l0, l2);
      r1 = min(r0, r1);
      r2 = min(r0, r2);
      total += int64_t(i - l1) * (r1 - i);
      total -= int64_t(i - l2) * (r2 - i);
      for (unsigned j = 0; j < 2; ++j) {
        TNode* p = tree.manager_at(i + j * n);
        vh[2 * j + 1] = tree.remove_node(p);
        vh[2 * j] = tree.insert(vh[2 * j], p);
      }
    }
    cout << "Case #" << it << ": " << total << std::endl;
  }
  return 0;
}

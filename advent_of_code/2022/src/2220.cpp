#include "common/binary_search_tree/base/inorder_index.h"
#include "common/binary_search_tree/treap.h"
#include "common/binary_search_tree/utils/swap_intervals.h"
#include "common/modular/arithmetic.h"
#include "common/stl/base.h"
#include "common/vector/read_all.h"

using TTree = bst::Treap<false, true, int64_t>;
using TNode = TTree::TNode;

int main_2220() {
  auto v = nvector::ReadAll<int64_t>();
  for (bool ab : {false, true}) {
    int64_t n = v.size();
    TTree tree(v.size());
    vector<TNode *> nodes;
    for (auto x : v) nodes.push_back(tree.New(x * (ab ? 811589153 : 1)));
    auto root = tree.BuildTree(nodes);
    for (unsigned itt = 0; itt < (ab ? 10 : 1); ++itt) {
      for (auto node : nodes) {
        auto p = bst::base::inorder_index(node);
        bst::VectorRotateLeft<TTree>(root, p);
        auto pnew = modular::TArithmetic_C32U::ApplyS(node->data, n - 1);
        bst::IntervalRotateLeft<TTree>(root, 0, pnew + 1, 1);
      }
    }
    TNode *p0 = nullptr;
    for (auto node : nodes) {
      if (node->data == 0) p0 = node;
    }
    int64_t p = bst::base::inorder_index(p0), r = 0;
    for (int64_t i = 1; i <= 3; ++i)
      r += tree.FindByOrder(root, (p + i * 1000) % n)->data;
    cout << r << endl;
  }
  return 0;
}

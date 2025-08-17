#include "common/binary_search_tree.h"
#include "common/binary_search_tree/base/at.h"
#include "common/binary_search_tree/base/index.h"
#include "common/binary_search_tree/utils/interval_rotate.h"
#include "common/modular/arithmetic.h"
#include "common/stl/base.h"
#include "common/vector/read_all.h"

using TTree = BinarySearchTree<false, true, int64_t>;
using TNode = TTree::NodeType;

int main_2220() {
  auto v = nvector::ReadAll<int64_t>();
  for (bool ab : {false, true}) {
    int64_t n = v.size();
    TTree tree(v.size());
    vector<TNode *> nodes;
    for (auto x : v)
      nodes.push_back(tree.create_node(x * (ab ? 811589153 : 1)));
    auto root = tree.build_tree(nodes);
    for (unsigned itt = 0; itt < (ab ? 10 : 1); ++itt) {
      for (auto node : nodes) {
        auto p = bst::base::index(node);
        bst::VectorRotateLeft<TTree>(root, p);
        auto pnew = modular::TArithmetic_C32U::ApplyS(node->data, n - 1);
        bst::IntervalRotateLeft<TTree>(root, 0, pnew + 1, 1);
      }
    }
    TNode *p0 = nullptr;
    for (auto node : nodes) {
      if (node->data == 0) p0 = node;
    }
    int64_t p = bst::base::index(p0), r = 0;
    for (int64_t i = 1; i <= 3; ++i)
      r += bst::base::at(root, (p + i * 1000) % n)->data;
    cout << r << endl;
  }
  return 0;
}

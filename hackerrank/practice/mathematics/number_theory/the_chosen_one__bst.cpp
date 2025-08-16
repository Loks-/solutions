// https://www.hackerrank.com/challenges/the-chosen-one

#include "common/binary_search_tree.h"
#include "common/binary_search_tree/subtree_data/gcd.h"
#include "common/binary_search_tree/subtree_data/utils/propagate_to_root.h"
#include "common/stl/base.h"
#include "common/vector/read.h"

using TGCD = bst::subtree_data::GCD<uint64_t>;
using TTreap = BinarySearchTree<false, true, uint64_t, std::tuple<TGCD>>;
using TNode = TTreap::NodeType;

int main_the_chosen_one__bst() {
  unsigned n;
  cin >> n;
  vector<uint64_t> v = nvector::Read<uint64_t>(n);
  if (n == 1) {
    cout << v[0] + 1 << endl;
    return 0;
  }
  TTreap treap(n);
  TNode* root = treap.build(v);
  for (unsigned i = 0; i < n; ++i) {
    TNode* node = treap.manager_at(i);
    uint64_t value = node->data;
    node->data = 0;
    bst::subtree_data::propagate_to_root(node);
    uint64_t gcd = TGCD::get(root);
    if ((value % gcd) != 0) {
      cout << gcd << endl;
      return 0;
    }
    node->data = value;
    bst::subtree_data::propagate_to_root(node);
  }
  return 0;
}

// https://www.hackerrank.com/challenges/the-chosen-one

#include "common/binary_search_tree/subtree_data/gcd.h"
#include "common/binary_search_tree/treap.h"
#include "common/stl/base.h"
#include "common/vector/read.h"

using TTreap =
    bst::Treap<false, true, uint64_t,
               bst::subtree_data::GCD<uint64_t, bst::subtree_data::None>>;
using TNode = TTreap::TNode;

int main_the_chosen_one__treap() {
  unsigned n;
  cin >> n;
  vector<uint64_t> v = nvector::Read<uint64_t>(n);
  if (n == 1) {
    cout << v[0] + 1 << endl;
    return 0;
  }
  TTreap treap(n);
  TNode* root = treap.Build(v);
  for (unsigned i = 0; i < n; ++i) {
    TNode* node = treap.NodeByRawIndex(i);
    uint64_t value = node->data;
    node->data = 0;
    bst::subtree_data::update_node_to_root(node);
    uint64_t gcd = root->subtree_data.gcd_value;
    if ((value % gcd) != 0) {
      cout << gcd << endl;
      return 0;
    }
    node->data = value;
    bst::subtree_data::update_node_to_root(node);
  }
  return 0;
}

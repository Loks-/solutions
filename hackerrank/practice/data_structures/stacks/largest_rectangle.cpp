// https://www.hackerrank.com/challenges/largest-rectangle

#include "common/binary_search_tree/subtree_data/size.h"
#include "common/binary_search_tree/subtree_data/treap_height.h"
#include "common/binary_search_tree/treap.h"
#include "common/stl/base.h"

using TTreap = bst::Treap<false, false, MetaEmpty>;
using TNode = TTreap::NodeType;

int main_largest_rectangle() {
  unsigned N, h;
  cin >> N;
  TTreap tree(N);
  vector<TNode*> vnodes(N);
  for (unsigned i = 0; i < N; ++i) {
    cin >> h;
    vnodes[i] = tree.create_node({});
    bst::subtree_data::TreapHeight::set(vnodes[i], ~h);
  }
  tree.build_tree(vnodes);
  uint64_t output = 0;
  for (TNode* p : vnodes)
    output = max(output, unsigned(~bst::subtree_data::TreapHeight::get(p)) *
                             uint64_t(bst::subtree_data::size(p)));
  cout << output << endl;
  return 0;
}

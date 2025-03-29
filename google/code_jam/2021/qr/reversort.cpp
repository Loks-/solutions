#include "common/binary_search_tree/base/index.h"
#include "common/binary_search_tree/deferred/reverse.h"
#include "common/binary_search_tree/deferred/utils/propagate_to_node.h"
#include "common/binary_search_tree/subtree_data/size.h"
#include "common/binary_search_tree/treap.h"
#include "common/binary_search_tree/utils/add_action_to_segment_by_index.h"
#include "common/stl/base.h"
#include "common/template.h"
#include "common/vector/read.h"

using TTree =
    bst::Treap<false, true, MetaEmpty, std::tuple<bst::subtree_data::Size>,
               std::tuple<bst::deferred::Reverse>>;
using TNode = TTree::TNode;

int main_reversort() {
  unsigned T, N;
  cin >> T;
  for (unsigned it = 0; it < T; ++it) {
    cin >> N;
    TTree tree(N);
    for (unsigned i = 0; i < N; ++i) tree.New();
    auto vu = nvector::Read<unsigned>(N);
    std::vector<TNode*> vn;
    for (unsigned u : vu) vn.push_back(tree.NodeByRawIndex(u - 1));
    auto r = tree.BuildTree(vn);
    uint64_t c = 0;
    for (unsigned i = 0; i < N - 1; ++i) {
      auto node = tree.NodeByRawIndex(i);
      bst::deferred::propagate_to_node(node);
      auto position = bst::base::index(node);
      c += position - i + 1;
      r = bst::AddActionToSegmentByIndex<bst::deferred::Reverse, TTree>(
          r, i, position + 1, MetaEmpty{});
    }
    cout << "Case #" << it + 1 << ": " << c << endl;
  }
  return 0;
}

// https://www.hackerrank.com/challenges/lazy-white-falcon

#include "common/binary_search_tree/subtree_data/none.h"
#include "common/binary_search_tree/subtree_data/sum.h"
#include "common/graph/tree.h"
#include "common/graph/tree/link_cut_tree.h"
#include "common/stl/base.h"

int main_lazy_white_falcon__lct() {
  unsigned N, Q;
  cin >> N >> Q;
  TreeGraph tree(N);
  tree.ReadEdges(true);
  graph::LinkCutTree<unsigned,
                     bst::subtree_data::Sum<unsigned, bst::subtree_data::None>>
      lct(tree);

  for (unsigned iQ = 0; iQ < Q; ++iQ) {
    unsigned t, u, x;
    cin >> t >> u >> x;
    if (t == 1) {
      lct.SetData(u, x);
    } else if (t == 2) {
      cout << lct.GetPathInfo(u, x).sum_value << endl;
    }
  }
  return 0;
}

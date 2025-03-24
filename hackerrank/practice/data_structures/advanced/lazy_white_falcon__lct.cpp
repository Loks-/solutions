// https://www.hackerrank.com/challenges/lazy-white-falcon

#include "common/binary_search_tree/subtree_data/sum.h"
#include "common/graph/tree.h"
#include "common/graph/tree/link_cut_tree.h"
#include "common/stl/base.h"

using TSum = bst::subtree_data::Sum<unsigned>;
int main_lazy_white_falcon__lct() {
  unsigned N, Q;
  cin >> N >> Q;
  TreeGraph tree(N);
  tree.ReadEdges(true);
  graph::LinkCutTree<unsigned, std::tuple<TSum>> lct(tree);

  for (unsigned iQ = 0; iQ < Q; ++iQ) {
    unsigned t, u, x;
    cin >> t >> u >> x;
    if (t == 1) {
      lct.SetData(u, x);
    } else if (t == 2) {
      cout << TSum::get(lct.GetPathInfo(u, x)) << endl;
    }
  }
  return 0;
}

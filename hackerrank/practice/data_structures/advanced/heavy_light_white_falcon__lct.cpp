// https://www.hackerrank.com/challenges/heavy-light-white-falcon

#include "common/binary_search_tree/subtree_data/max.h"
#include "common/graph/tree.h"
#include "common/graph/tree/link_cut_tree.h"
#include "common/stl/base.h"

using TMax = bst::subtree_data::Max<unsigned>;

int main_heavy_light_white_falcon__lct() {
  unsigned N, Q;
  cin >> N >> Q;
  TreeGraph tree(N);
  tree.ReadEdges(true);
  graph::LinkCutTree<unsigned, std::tuple<TMax>> lct(tree);

  for (unsigned iQ = 0; iQ < Q; ++iQ) {
    unsigned t, u, x;
    cin >> t >> u >> x;
    if (t == 1) {
      lct.SetData(u, x);
    } else if (t == 2) {
      cout << TMax::get(lct.GetPathInfo(u, x)) << endl;
    }
  }
  return 0;
}

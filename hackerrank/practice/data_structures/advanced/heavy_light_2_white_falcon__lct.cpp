// https://www.hackerrank.com/challenges/heavy-light-2-white-falcon

#include "common/binary_search_tree/deferred/add_arithmetic_sequence.h"
#include "common/binary_search_tree/subtree_data/size.h"
#include "common/binary_search_tree/subtree_data/sum.h"
#include "common/graph/tree.h"
#include "common/graph/tree/link_cut_tree.h"
#include "common/modular_io.h"
#include "common/stl/base.h"

using TSum = bst::subtree_data::Sum<ModularDefault>;
using TSize = bst::subtree_data::Size;
using TASequence = bst::deferred::AddArithmeticSequence<ModularDefault>;

int main_heavy_light_2_white_falcon__lct() {
  unsigned N, Q;
  cin >> N >> Q;
  TreeGraph tree(N);
  tree.ReadEdges(true);
  graph::LinkCutTree<ModularDefault, std::tuple<TSize, TSum>,
                     std::tuple<TASequence>>
      lct(tree);

  for (unsigned iQ = 0; iQ < Q; ++iQ) {
    unsigned t, u, v, x;
    cin >> t >> u >> v;
    if (t == 1) {
      cin >> x;
      lct.AddActionOnPath<TASequence>(u, v, std::make_pair(x, x));
    } else if (t == 2) {
      cout << TSum::get(lct.GetPathInfo(u, v)) << endl;
    }
  }
  return 0;
}

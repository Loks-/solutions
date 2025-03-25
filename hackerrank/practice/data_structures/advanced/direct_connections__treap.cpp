// https://www.hackerrank.com/challenges/direct-connections

#include "common/binary_search_tree/subtree_data/size.h"
#include "common/binary_search_tree/subtree_data/sum_keys.h"
#include "common/binary_search_tree/treap.h"
#include "common/modular_io.h"
#include "common/stl/base.h"
#include "common/vector/read.h"

using TSumKeys = bst::subtree_data::SumKeys<uint64_t>;
using TSize = bst::subtree_data::Size;
using TTree = bst::Treap<true, false, MetaEmpty, std::tuple<TSumKeys, TSize>,
                         std::tuple<>, uint64_t>;
using TNode = TTree::TNode;

int main_direct_connections__treap() {
  unsigned T, N;
  cin >> T;
  TTree tree(200000);
  for (unsigned it = 0; it < T; ++it) {
    cin >> N;
    vector<uint64_t> vx = nvector::Read<uint64_t>(N);
    vector<uint64_t> vp = nvector::Read<uint64_t>(N);
    vector<pair<uint64_t, uint64_t>> vpx;
    for (unsigned i = 0; i < N; ++i) vpx.push_back({vp[i], vx[i]});
    sort(vpx.begin(), vpx.end());
    ModularDefault total = 0;
    TNode *root = 0, *l, *r;
    for (auto px : vpx) {
      tree.SplitByKey(root, px.second, l, r);
      ModularDefault s = 0;
      if (l)
        s += ModularDefault(bst::subtree_data::size(l) * px.second -
                            TSumKeys::get(l));
      if (r)
        s += ModularDefault(TSumKeys::get(r) -
                            bst::subtree_data::size(r) * px.second);
      total += s * ModularDefault(px.first);
      TNode* m = tree.New({}, px.second);
      root = tree.Join(tree.Join(l, m), r);
    }
    tree.ReleaseTree(root);
    cout << total << endl;
  }
  return 0;
}

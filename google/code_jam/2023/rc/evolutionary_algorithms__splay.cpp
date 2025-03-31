#include "common/binary_search_tree/splay_tree.h"
#include "common/stl/base.h"
#include "common/vector/read.h"

#include <queue>

using TTree = bst::SplayTree<true, MetaEmpty>;
using TNode = TTree::NodeType;

int main_evolutionary_algorithms__splay() {
  unsigned T, N, K;
  cin >> T;
  for (unsigned it = 1; it <= T; ++it) {
    cin >> N >> K;
    auto vs = nvector::Read<int64_t>(N);
    auto vss = vs;
    sort(vss.begin(), vss.end());
    auto vp = nvector::Read<unsigned>(N - 1);
    vector<unsigned> vc(N, 0);
    for (auto p : vp) vc[p - 1] += 1;

    TTree tree(N);
    uint64_t r = 0;
    vector<TNode *> vn(N);
    queue<unsigned> q;
    for (unsigned i = 0; i < N; ++i) {
      vn[i] = tree.create_node({}, vs[i]);
      if (vc[i] == 0) q.push(i);
    }
    for (; !q.empty(); q.pop()) {
      auto i = q.front();
      auto s = vs[i];
      if (s > K) {
        auto s1 = (s - 1) / K;
        uint64_t tt = upper_bound(vss.begin(), vss.end(), s1) - vss.begin();
        if (tt > 1) {
          auto node = TTree::floor(vn[i], s1 + 1);
          uint64_t tc = (node ? TTree::index(node) + 1 : size_t(0));
          r += tc * (tt - tc);
        }
      }
      if (i > 0) {
        unsigned j = vp[i - 1] - 1;
        vn[j] = TTree::merge(vn[j], vn[i]);
        vc[j] -= 1;
        if (vc[j] == 0) q.push(j);
      }
    }
    cout << "Case #" << it << ": " << r << endl;
    tree.release_tree(vn[0]);
  }
  return 0;
}

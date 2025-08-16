#include "common/binary_search_tree.h"
#include "common/binary_search_tree/base/to_vector.h"
#include "common/binary_search_tree/deferred/reverse.h"
#include "common/binary_search_tree/subtree_data/size.h"
#include "common/stl/base.h"

#include <functional>

using TTree =
    BinarySearchTree<false, true, unsigned, std::tuple<bst::subtree_data::Size>,
                     std::tuple<bst::deferred::Reverse>>;
using TNode = TTree::NodeType;

int main_reversort_engineering() {
  unsigned T, N, C;
  cin >> T;
  for (unsigned it = 0; it < T; ++it) {
    cin >> N >> C;
    ++C;
    if ((C < N) || (N * (N + 1) < 2 * C)) {
      cout << "Case #" << it + 1 << ": "
           << "IMPOSSIBLE" << endl;
    } else {
      TTree tree(N);

      std::function<TNode*(unsigned, unsigned)> Solve =
          [&](unsigned n, unsigned c) -> TNode* {
        auto node = tree.create_node(N - n + 1);
        if (n == 1) {
          assert(c == 1);
          return node;
        } else {
          if (c >= 2 * n - 1) {
            auto r = Solve(n - 1, c - n);
            bst::deferred::reverse_subtree(r);
            return tree.join(node, r);
          } else {
            auto r = Solve(n - 1, c - 1);
            return tree.join(r, node);
          }
        }
      };

      auto r = Solve(N, C);
      auto v = bst::base::to_vector(r);
      std::reverse(v.begin(), v.end());
      cout << "Case #" << it + 1 << ":";
      for (unsigned u : v) std::cout << " " << u;
      cout << endl;
    }
  }
  return 0;
}

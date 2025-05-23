#include "common/binary_search_tree/base/at.h"
#include "common/binary_search_tree/base/to_vector.h"
#include "common/binary_search_tree/treap.h"
#include "common/stl/base.h"
#include "common/vector/write.h"

using TTree = bst::Treap<false, true, unsigned>;
using TNode = TTree::NodeType;

int main_median_sort() {
  unsigned T, N, Q, jr;
  cin >> T >> N >> Q;
  assert(N > 1);
  for (unsigned it = 0; it < T; ++it) {
    TTree tree(N);
    auto root = tree.join(tree.create_node(1u), tree.create_node(2u));
    for (unsigned i = 3; i <= N; ++i) {
      unsigned l = 0, r = i - 1;
      for (; r > l;) {
        unsigned p1 = (2 * l + r) / 3, p2 = (l + 2 * r) / 3;
        if (p1 == p2) {
          if (p1 > 0)
            --p1;
          else
            ++p2;
        }
        unsigned i1 = bst::base::at(root, p1)->data,
                 i2 = bst::base::at(root, p2)->data;
        cout << i << " " << i1 << " " << i2 << endl;
        cin >> jr;
        if (jr == i1) {
          r = p1;
        } else if (jr == i) {
          l = p1 + 1;
          r = p2;
        } else if (jr == i2) {
          l = p2 + 1;
        } else {
          return -1;
        }
      }
      root = tree.insert_new_at(root, i, l);
    }
    nvector::Write(bst::base::to_vector(root));
    cin >> jr;
    if (jr != 1) return -2;
  }
  return 0;
}

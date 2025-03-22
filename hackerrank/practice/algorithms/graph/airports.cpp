// https://www.hackerrank.com/challenges/airports

#include "common/binary_search_tree/subtree_data/size.h"
#include "common/binary_search_tree/treap.h"
#include "common/binary_search_tree/utils/get_segment_info_by_key.h"
#include "common/stl/base.h"
#include "common/vector/read.h"

namespace {
class SubtreeData : public bst::subtree_data::Size {
 public:
  using Base = bst::subtree_data::Size;

  static constexpr bool use_data = false;
  static constexpr bool support_insert = false;
  static constexpr bool support_remove = false;

  int64_t l, r, d;

  template <class TNode>
  void update(TNode* node) {
    Base::update(node);
    l = (node->l) ? node->l->subtree_data.l : node->key;
    r = (node->r) ? node->r->subtree_data.r : node->key;
    d = 0;
    if (node->l)
      d = std::max(d, std::max(node->l->subtree_data.d,
                               node->key - node->l->subtree_data.r));
    if (node->r)
      d = std::max(d, std::max(node->r->subtree_data.d,
                               node->r->subtree_data.l - node->key));
  }
};
}  // namespace

using TTree = bst::Treap<true, false, MetaEmpty, SubtreeData>;
using TNode = TTree::TNode;

int main_airports() {
  unsigned T;
  cin >> T;
  for (unsigned it = 0; it < T; ++it) {
    unsigned n;
    int64_t d;
    cin >> n >> d;
    auto v = nvector::Read<int64_t>(n);
    int64_t l = min(v[0], v[1]), r = max(v[0], v[1]);
    TTree tree(n);
    cout << 0 << " " << max<int64_t>(d - (r - l), 0);
    TNode* head = nullptr;
    typename TNode::TInfo subtree_data;
    for (unsigned i = 2; i < n; ++i) {
      if (v[i] < l) {
        head = tree.InsertNewNode(head, {}, l);
        l = v[i];
      } else if (r < v[i]) {
        head = tree.InsertNewNode(head, {}, r);
        r = v[i];
      } else {
        head = tree.InsertNewNode(head, {}, v[i]);
      }
      subtree_data.size = 0;
      head =
          bst::GetSegmentInfoByKey<TTree>(head, r - d + 1, l + d, subtree_data);
      int64_t lrd = max<int64_t>(d - (r - l), 0);
      if (subtree_data.size == 0) {
        cout << " " << lrd;
      } else {
        int64_t md = max(subtree_data.l - (r - d),
                         max(subtree_data.d, (l + d) - subtree_data.r));
        cout << " " << max(lrd, l - r + 2 * d - md);
      }
    }
    cout << endl;
  }
  return 0;
}

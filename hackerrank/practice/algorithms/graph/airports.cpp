// https://www.hackerrank.com/challenges/airports

#include "common/binary_search_tree/subtree_data/base.h"
#include "common/binary_search_tree/subtree_data/size.h"
#include "common/binary_search_tree/treap.h"
#include "common/binary_search_tree/utils/get_segment_info_by_key.h"
#include "common/stl/base.h"
#include "common/vector/read.h"

namespace {
class PSubtreeData : public bst::subtree_data::Base {
 public:
  using Self = PSubtreeData;

  static constexpr bool use_keys = true;

  int64_t l, r, d;

  template <class TNode>
  void update(TNode* node) {
    Base::update(node);
    l = (node->left) ? node->left->subtree_data.template get<Self>().l
                     : node->key;
    r = (node->right) ? node->right->subtree_data.template get<Self>().r
                      : node->key;
    d = 0;
    if (node->left)
      d = std::max(
          d, std::max(
                 node->left->subtree_data.template get<Self>().d,
                 node->key - node->left->subtree_data.template get<Self>().r));
    if (node->right)
      d = std::max(
          d, std::max(
                 node->right->subtree_data.template get<Self>().d,
                 node->right->subtree_data.template get<Self>().l - node->key));
  }
};
}  // namespace

using TTree = bst::Treap<true, false, MetaEmpty,
                         std::tuple<bst::subtree_data::Size, PSubtreeData>>;
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
      typename TNode::SubtreeDataType subtree_data;
      head =
          bst::GetSegmentInfoByKey<TTree>(head, r - d + 1, l + d, subtree_data);
      int64_t lrd = max<int64_t>(d - (r - l), 0);
      if (bst::subtree_data::size(subtree_data) == 0) {
        cout << " " << lrd;
      } else {
        int64_t md =
            max(subtree_data.template get<PSubtreeData>().l - (r - d),
                max(subtree_data.template get<PSubtreeData>().d,
                    (l + d) - subtree_data.template get<PSubtreeData>().r));
        cout << " " << max(lrd, l - r + 2 * d - md);
      }
    }
    cout << endl;
  }
  return 0;
}

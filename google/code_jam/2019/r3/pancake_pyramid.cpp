#include "common/binary_search_tree/subtree_data/base.h"
#include "common/binary_search_tree/subtree_data/size.h"
#include "common/binary_search_tree/subtree_data/treap_height.h"
#include "common/binary_search_tree/treap.h"
#include "common/modular_io.h"
#include "common/stl/base.h"
#include "common/vector/read.h"

namespace {
class PInfo : public bst::subtree_data::Base {
 public:
  using Self = PInfo;

  static constexpr bool use_data = true;

  ModularDefault s, sp, sl, sr;

  template <class TNode>
  static unsigned treap_height(const TNode* node) {
    return bst::subtree_data::TreapHeight::get(node);
  }

  template <class TNode>
  void update(TNode* node) {
    uint64_t size_l = bst::subtree_data::size(node->left),
             size_r = bst::subtree_data::size(node->right);
    s = sl = sr = 0;
    sp = treap_height(node);
    if (node->left) {
      const auto& l = node->left->subtree_data.template get<PInfo>();
      s += l.s;
      s += l.sl * (size_r + 1);
      sp += l.sp;
      sl += l.sl;
      sr += l.sr;
      sr += (ModularDefault(treap_height(node) * size_l) - l.sp) * (size_r + 1);
    }
    if (node->right) {
      const auto& r = node->right->subtree_data.template get<PInfo>();
      s += r.s;
      s += r.sr * (size_l + 1);
      sp += r.sp;
      sl += r.sl;
      sr += r.sr;
      sl += (ModularDefault(treap_height(node) * size_r) - r.sp) * (size_l + 1);
    }
  }
};
}  // namespace

using TTree = bst::Treap<false, false, MetaEmpty,
                         std::tuple<bst::subtree_data::Size, PInfo>>;
using TNode = typename TTree::TNode;

int main_pancake_pyramid() {
  unsigned T, S;
  cin >> T;
  for (unsigned iT = 1; iT <= T; ++iT) {
    cin >> S;
    auto vs = nvector::Read<unsigned>(S);
    TTree tree(S);
    vector<TNode*> vn;
    for (unsigned p : vs) {
      TNode* node = tree.New({});
      bst::subtree_data::TreapHeight::set(node, p);
      vn.push_back(node);
    }
    TNode* head = TTree::BuildTree(vn);
    cout << "Case #" << iT << ": " << head->subtree_data.template get<PInfo>().s
         << endl;
  }
  return 0;
}

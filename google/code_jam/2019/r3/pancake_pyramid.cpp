#include "common/binary_search_tree/subtree_data/size.h"
#include "common/binary_search_tree/treap.h"
#include "common/modular_io.h"
#include "common/stl/base.h"
#include "common/vector/read.h"

namespace {
class PInfo : public bst::subtree_data::Size {
 public:
  using Base = bst::subtree_data::Size;
  using Self = PInfo;
  static constexpr bool use_data = true;
  static constexpr bool support_insert = false;
  static constexpr bool support_remove = false;

  ModularDefault s, sp, sl, sr;

  template <class TNode>
  void update(TNode* node) {
    Base::update(node);
    uint64_t size_l = node->l ? node->l->subtree_data.size : 0,
             size_r = node->r ? node->r->subtree_data.size : 0;
    s = sl = sr = 0;
    sp = node->subtree_data.treap_height;
    if (node->l) {
      s += node->l->subtree_data.s;
      s += node->l->subtree_data.sl * (size_r + 1);
      sp += node->l->subtree_data.sp;
      sl += node->l->subtree_data.sl;
      sr += node->l->subtree_data.sr;
      sr += (ModularDefault(node->subtree_data.treap_height * size_l) -
             node->l->subtree_data.sp) *
            (size_r + 1);
    }
    if (node->r) {
      s += node->r->subtree_data.s;
      s += node->r->subtree_data.sr * (size_l + 1);
      sp += node->r->subtree_data.sp;
      sl += node->r->subtree_data.sl;
      sr += node->r->subtree_data.sr;
      sl += (ModularDefault(node->subtree_data.treap_height * size_r) -
             node->r->subtree_data.sp) *
            (size_l + 1);
    }
  }
};
}  // namespace

using TTree = bst::Treap<false, false, MetaEmpty, PInfo>;
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
      node->subtree_data.treap_height = p;
      vn.push_back(node);
    }
    TNode* head = TTree::BuildTree(vn);
    cout << "Case #" << iT << ": " << head->subtree_data.s << endl;
  }
  return 0;
}

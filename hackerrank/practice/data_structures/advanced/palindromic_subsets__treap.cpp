// https://www.hackerrank.com/challenges/palindromic-subsets

#include "common/binary_search_tree/deferred/base.h"
#include "common/binary_search_tree/subtree_data/size.h"
#include "common/binary_search_tree/subtree_data/sum.h"
#include "common/binary_search_tree/treap.h"
#include "common/binary_search_tree/utils/add_action_to_segment_by_index.h"
#include "common/binary_search_tree/utils/get_segment_info_by_index.h"
#include "common/linear_algebra/vector_static_size.h"
#include "common/modular_io.h"
#include "common/stl/base.h"

#include <string>

namespace {
// Forward declaration of the helper function
template <class Node>
constexpr void rotate_external(Node* node, unsigned r);

template <class TVector>
class RotateVector : public bst::deferred::Base {
 public:
  using ValueType = TVector;
  using Self = RotateVector;

  using SDSum = bst::subtree_data::Sum<ValueType>;

  static constexpr bool modify_data = true;

  constexpr void clear() { r_ = 0; }

  constexpr bool apply_required() const { return r_ != 0; }

  template <class Node>
  constexpr void rotate(Node* node, unsigned r) {
    rotate_one(SDSum::get_ref(node), r);
    r_ = (r_ + r) % TVector::Size();
  }

  template <class Node>
  constexpr void apply(Node* node) {
    if (r_ != 0) {
      rotate_one(node->data, r_);
      rotate_external(node->left, r_);
      rotate_external(node->right, r_);
      r_ = 0;
    }
  }

  template <class Node>
  static constexpr void add(Node* node, unsigned r) {
    rotate_external(node, r);
  }

 protected:
  size_t r_ = 0;

  static constexpr void rotate_one(TVector& v, size_t r) {
    if (r == 0) return;
    TVector vt;
    const size_t size = v.Size();
    for (size_t i = 0; i < size; ++i) vt((i + r) % size) = v(i);
    v.swap(vt);
  }
};

using TVector = la::VectorStaticSize<unsigned, 26>;
using TSum = bst::subtree_data::Sum<TVector>;
using TRotate = RotateVector<TVector>;

template <class Node>
constexpr void rotate_external(Node* node, unsigned r) {
  if (node) {
    node->deferred.template get<TRotate>().rotate(node, r);
  }
}

}  // namespace

using TTree =
    bst::Treap<false, false, TVector, std::tuple<bst::subtree_data::Size, TSum>,
               std::tuple<TRotate>>;
using TNode = TTree::NodeType;

int main_palindromic_subsets__treap() {
  unsigned n, q;
  cin >> n >> q;
  string s;
  cin >> s;
  vector<TVector> vs(n);
  for (unsigned i = 0; i < n; ++i) vs[i](s[i] - 'a') = 1;
  TTree tree(n);
  TNode* root = tree.build(vs);
  for (unsigned i = 0; i < q; ++i) {
    unsigned t, a, b, c;
    cin >> t;
    if (t == 1) {
      cin >> a >> b >> c;
      root = bst::AddActionToSegmentByIndex<TRotate, TTree>(root, a, b + 1, c);
    } else if (t == 2) {
      cin >> a >> b;
      TTree::SubtreeDataType info;
      root = bst::GetSegmentInfoByIndex<TTree>(root, a, b + 1, info);
      unsigned nsum = 0, nnonzero = 0;
      for (unsigned j = 0; j < 26; ++j) {
        if (TSum::get(info)(j)) {
          nsum += TSum::get(info)(j);
          nnonzero += 1;
        }
      }
      ModularDefault two = 2;
      cout << (ModularDefault(nnonzero + 1) * two.PowU(nsum - nnonzero) - 1)
           << endl;
    }
  }
  return 0;
}

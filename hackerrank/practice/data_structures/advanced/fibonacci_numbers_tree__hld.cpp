// https://www.hackerrank.com/challenges/fibonacci-numbers-tree

#include "common/data_structures/segment_tree/action/none.h"
#include "common/data_structures/segment_tree/info/sum.h"
#include "common/graph/tree.h"
#include "common/graph/tree/hld.h"
#include "common/modular/static/fibonacci_matrix.h"
#include "common/modular_io.h"
#include "common/stl/base.h"
#include "common/stl/pair.h"

using TFibonacci = modular::mstatic::FibonacciMatrix<ModularDefault>;

namespace {
class FData {
 public:
  ModularDefault f0, f1, v;

  FData operator+(const FData& r) const {
    return FData{f0 + r.f0, f1 + r.f1, v + r.v};
  }
};

class ActionAdd : public ds::st::action::None {
 public:
  using TData = std::pair<ModularDefault, ModularDefault>;
  [[maybe_unused]] static const bool modify_data = true;

  TData x;

  bool IsEmpty() const { return (x.first == 0) && (x.second == 0); }
  void Clear() { x = {0, 0}; };

  template <class TNode>
  void Add(TNode* node, const TData& value) {
    auto& i = node->info.sum;
    i.v += i.f0 * value.first + i.f1 * value.second;
    x += value;
  }

  template <class TNode>
  void Apply(TNode* node) {
    if (IsEmpty()) return;
    if (node->IsLeaf()) {
      auto& d = node->GetData();
      d.v += d.f0 * x.first + d.f1 * x.second;
    } else {
      node->l->AddAction(x);
      node->r->AddAction(x);
    }
    Clear();
  }
};
}  // namespace

int main_fibonacci_numbers_tree__hld() {
  unsigned N, Q;
  cin >> N >> Q;
  TreeGraph tree(N);
  tree.ReadTreeEdges();
  graph::HLD<FData, ds::st::info::Sum<FData>, ActionAdd> hld(tree);

  for (unsigned i = 0; i < N; ++i) {
    auto p = TFibonacci::GetPU(hld.Deep(i));
    hld.SetData(i, FData{p.first, p.second, 0});
  }

  for (unsigned iQ = 0; iQ < Q; ++iQ) {
    char c;
    cin >> c;
    if (c == 'Q') {
      unsigned x, y;
      cin >> x >> y;
      cout << hld.Path(x - 1, y - 1).GetInfo().sum.v << endl;
    } else if (c == 'U') {
      unsigned x;
      int64_t kx;
      cin >> x >> kx;
      x -= 1;
      auto p0 = TFibonacci::GetPS(kx - hld.Deep(x) + 1);
      hld.Subtree(x).AddAction(p0);
    }
  }
  return 0;
}

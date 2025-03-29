// https://www.hackerrank.com/challenges/median

#include "common/binary_search_tree/perfect_tree.h"
#include "common/binary_search_tree/subtree_data/size.h"
#include "common/binary_search_tree/subtree_data/sum.h"
#include "common/binary_search_tree/subtree_data/utils/propagate_to_root.h"
#include "common/binary_search_tree/utils/prefix_sum_upper_bound.h"
#include "common/stl/base.h"

#include <iomanip>
#include <unordered_set>

using TSum = bst::subtree_data::Sum<unsigned>;
using TTree =
    bst::PerfectTree<true, unsigned, std::tuple<bst::subtree_data::Size, TSum>>;
using TNode = TTree::TNode;

int main_median_updates__fixed_tree() {
  cout << setprecision(1) << fixed;
  unsigned N;
  cin >> N;
  vector<pair<char, int64_t>> input;
  unordered_set<int64_t> set_x;
  for (unsigned i = 0; i < N; ++i) {
    char c;
    int64_t x;
    cin >> c >> x;
    x *= 2;
    input.push_back({c, x});
    set_x.insert(x);
  }
  vector<int64_t> vx(set_x.begin(), set_x.end());
  TTree tree(unsigned(vx.size()));
  TNode* root = tree.Build(vector<unsigned>(vx.size(), 0), vx);

  for (auto p : input) {
    TNode* node = TTree::FindByKey(root, p.second);
    assert(node);
    if (p.first == 'a') {
      node->data += 1;
    } else if (p.first == 'r') {
      if (node->data == 0) {
        cout << "Wrong!" << endl;
        continue;
      }
      node->data -= 1;
    }
    bst::subtree_data::propagate_to_root(node);
    if (TSum::get(root) == 0) {
      cout << "Wrong!" << endl;
      continue;
    }
    unsigned size = TSum::get(root);
    int64_t s = (bst::PrefixSumUpperBound<TSum>(root, (size - 1) / 2)->key +
                 bst::PrefixSumUpperBound<TSum>(root, size / 2)->key) /
                2;
    if (s & 1)
      cout << s / 2.0 << endl;
    else
      cout << s / 2 << endl;
  }
  return 0;
}

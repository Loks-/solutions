// https://www.hackerrank.com/challenges/median

#include "common/binary_search_tree/red_black_tree.h"
#include "common/binary_search_tree/utils/median.h"
#include "common/stl/base.h"

#include <iomanip>

using TTree = bst::RedBlackTree<MetaEmpty>;
using TNode = TTree::TNode;

int main_median_updates__upt_red_black() {
  cout << setprecision(1) << fixed;
  unsigned N;
  cin >> N;
  TTree tree(N);
  TNode* root = 0;
  for (unsigned i = 0; i < N; ++i) {
    char c;
    int64_t x;
    cin >> c >> x;
    x *= 2;
    if (c == 'a') {
      root = tree.insert_new(root, {}, x);
    } else if (c == 'r') {
      TNode* node = TTree::find(root, x);
      if (node == 0) {
        cout << "Wrong!" << endl;
        continue;
      }
      root = tree.remove_and_release(root, x);
    }
    if (root == 0) {
      cout << "Wrong!" << endl;
    } else {
      int64_t s = bst::Median<TNode, int64_t>(root);
      if (s & 1)
        cout << s / 2.0 << endl;
      else
        cout << s / 2 << endl;
    }
  }
  return 0;
}

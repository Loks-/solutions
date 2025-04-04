// https://www.hackerrank.com/challenges/find-the-running-median

#include "common/binary_search_tree/avl_tree.h"
#include "common/binary_search_tree/utils/median.h"
#include "common/stl/base.h"

#include <iomanip>

using TTree = bst::AVLTree<false, MetaEmpty>;
using TNode = TTree::NodeType;

int main_find_the_running_median() {
  cout << setprecision(1) << fixed;
  unsigned N;
  cin >> N;
  TTree tree(N);
  TNode* root = 0;
  for (unsigned i = 0; i < N; ++i) {
    int64_t x;
    cin >> x;
    root = tree.insert_new(root, {}, x);
    cout << bst::Median<TNode, double>(root) << endl;
  }
  return 0;
}

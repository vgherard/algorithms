#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void in_order(const vector<Node>& tree, size_t index, vector <int>& result) {
  // std::cout << "Checking index:" << index << "\n";
  // std::cin.get();
  if (tree[index].left != -1) {
    in_order(tree, tree[index].left, result);
    if (tree[index].key <= result.back())
      return;
  }
    if (not result.empty() and tree[index].key < result.back())
      return;
  result.push_back(tree[index].key);
  if (tree[index].right != -1) {
    in_order(tree, tree[index].right, result);
  }
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  if (tree.size() == 0) return true;
  vector <int> sorted;
  in_order(tree, 0, sorted);
  return sorted.size() == tree.size();
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}

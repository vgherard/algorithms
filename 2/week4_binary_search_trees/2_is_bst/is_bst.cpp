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
  if (tree[index].left != -1) {
    in_order(tree, tree[index].left, result);
  }
  result.push_back(tree[index].key);
  if (tree[index].right != -1) {
    in_order(tree, tree[index].right, result);
  }
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  vector <int> sorted;
  if (tree.size() == 0) return true;
  in_order(tree, 0, sorted);
  int prev = sorted[0];
  for(size_t i = 1; i < sorted.size(); i++) {
    if (sorted[i] < prev)
      return false;
    prev = sorted[i];
  }
  return true;
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

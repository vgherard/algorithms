#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <stack>


using std::vector;
using std::pair;
using std::stack;
using std::unordered_set;

using Graph = vector<vector<int> >;

void explore(const Graph &g,
             int start,
             unordered_set<int> & visited
) {
  visited.insert(start);
  for (const int & x : g[start])
    if (visited.find(x) == visited.end())
      explore(g, x, visited);
}

// Explore an undirected graph through Depth-First Search
void explore_po(const Graph &g,
                int start,
                unordered_set<int> & visited,
                stack<int> & postorder
) {
  visited.insert(start);
  for (const int & x : g[start])
    if (visited.find(x) == visited.end())
      explore_po(g, x, visited, postorder);
    postorder.push(start);
}


// Depth-First-Search exploration with postorder
struct DFS_po {
  unordered_set<int> visited;
  stack<int> postorder;

  DFS_po(const Graph &g) {
    int clock = 0;
    int V = g.size();
    for (int v = 0; v < V; v++) {
      if (visited.find(v) == visited.end())
        explore_po(g, v, visited, postorder);
    }
  }
};

vector<int> toposort(vector<vector<int> > adj) {
  vector<int> used(adj.size(), 0);
  vector<int> order;
  //write your code here
  return order;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  stack<int> order = DFS_po(adj).postorder;
  while (not order.empty()) {
    std::cout << order.top() + 1 << " ";
    order.pop();
  }
}

#include <iostream>
#include <vector>
#include <unordered_set>

using std::vector;
using std::pair;
using std::unordered_set;

// Explore an undirected graphs through Depth-First Search
void explore(const vector<vector<int> > &adj, int start, unordered_set<int> & visited) {
    visited.insert(start);
    for (const int & x : adj[start])
        if (visited.find(x) == visited.end())
            explore(adj, x, visited);
}

int number_of_components(vector<vector<int> > &adj) {
    int num_cc = 0;
    unordered_set<int> visited;
    for (size_t i = 0; i < adj.size(); ++i) {
        if (visited.find(i) == visited.end()) {
            num_cc++;
            explore(adj, i, visited);
        }
    }
    return num_cc;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj);
}

#include <iostream>
#include <vector>
#include <unordered_set>

using std::vector;
using std::pair;
using std::unordered_set;

// Vertexes are numbered from 1 to n; 
// adj[i] stores the vertexes adjacent to the i-th vertex.


// Explore an undirected graphs through Depth-First Search
void explore(const vector<vector<int> > &adj, int start, unordered_set<int> & visited) {
    visited.insert(start);
    for (const int & x : adj[start])
        if (visited.find(x) == visited.end())
            explore(adj, x, visited);
}

// Get the connected component of a vertex
unordered_set<int> get_cc(const vector<vector<int> > &adj, int x) {
    unordered_set<int> cc;
    explore(adj, x, cc);
    return cc;
}

// Returns '1' if there is a path between 'start' and 'end', '0' if not.
// N.B.: The approach below is optimal in the case when one needs to make 
// several calls for different 'start' but same 'end' position. 
// In that case, the function below should be memoised (not implemented).
int reach(const vector<vector<int> > &adj, int start, int end) {
    unordered_set<int> cc_end = get_cc(adj, end);
    if (cc_end.find(start) != cc_end.end())
        return 1;
    else
        return 0;
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
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using std::vector;
using std::queue;
using std::unordered_set;

// Represent a graph by its adjacency list
using Graph = vector<vector<int> >;

enum Color { white, black, gray };
Color opposite(Color c) {
    if (c == Color::white) return Color::black;
    else if (c == Color::black) return Color::white;
    return Color::gray;
}

int is_bipartite(Graph &g) {
  int V = g.size();
  std::vector<Color> color(V, Color::gray);
  unordered_set<int> still_gray;
  for (int v = 0; v < V; v++)
    still_gray.insert(v);
  while(not still_gray.empty()) {
    int s = *still_gray.begin();
    color[s] = white;
    still_gray.erase(s);
    queue<int> to_explore;
    to_explore.push(s);
    while(not to_explore.empty()) {
      int v = to_explore.front();
        for (const int & x : g[v]) {
          if (color[x] == Color::gray) {
            to_explore.push(x);
            color[x] = opposite(color[v]);
            still_gray.erase(x);
          } else {
            if (color[x] != opposite(color[v]))
              return 0;
          }
        }
      to_explore.pop();
    }
  }
  return 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << is_bipartite(adj);
}

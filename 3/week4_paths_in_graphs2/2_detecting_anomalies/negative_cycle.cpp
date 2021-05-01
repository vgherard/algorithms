#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_set>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using std::unordered_set;
using weight_type = double;

// Maximum distance < 1e+7 due to problem constraints
const weight_type INFTY = 1e+9;
const int INFTY_VERTEX = -1;

struct WeightedLink {
  int end;
  weight_type weight;
  WeightedLink (int end_, weight_type weight_) : end(end_), weight(weight_) {}
};


using WeightedGraph = vector<vector<WeightedLink> >;

int negative_cycle(const WeightedGraph &g) {
    int V = g.size();
    vector<weight_type> dist(V, INFTY);
    dist[0] = 0;
    bool updated;
    for (int iter = 0; iter < V; iter++) {
        updated = false;
        for (int u = 0; u < V; u++) {
            for (const auto & v : g[u]) {
                if (dist[v.end] > dist[u] + v.weight) {
                    dist[v.end] = dist[u] + v.weight;
                    updated = true;
                }
            }
        }
        if (not updated) return 0;
    }
    return 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<WeightedLink> > adj(n, vector<WeightedLink>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(WeightedLink(y - 1, w));
  }
  std::cout << negative_cycle(adj);
}

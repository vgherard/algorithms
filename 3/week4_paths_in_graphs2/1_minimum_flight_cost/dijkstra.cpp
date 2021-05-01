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
using weight_type = long long;

// Maximum distance < 1e+13 due to problem constraints
const weight_type INFTY = 1e+15;
const int INFTY_VERTEX = -1;

struct WeightedLink {
    int end;
    weight_type weight;
    WeightedLink (int end_, weight_type weight_) : end(end_), weight(weight_) {}
};

struct VertexDistance {
    int vertex;
    weight_type distance;
    VertexDistance (int v, weight_type d) : vertex(v), distance(d) {}
    friend bool operator>(const VertexDistance & l, const VertexDistance & r) {
        return l.distance > r.distance;
    }
};

using WeightedGraph = vector<vector<WeightedLink> >;

weight_type distance(const WeightedGraph &g, int s, int t) {
    int V = g.size();
    vector<weight_type> dist(V, INFTY);
    vector<int> prev(V, INFTY_VERTEX);
    dist[s] = 0;

    priority_queue<VertexDistance,
                   vector<VertexDistance>,
                   std::greater<VertexDistance>
      > H;
    unordered_set<int> processed;
    for (int v = 0; v < V; v++)
        H.push(VertexDistance(v, dist[v]));

    while (not H.empty()) {
        VertexDistance u = H.top(); H.pop();
        if (processed.find(u.vertex) != processed.end())
              continue;
        processed.insert(u.vertex);
        for (const WeightedLink & v : g[u.vertex]) {
            weight_type new_distance = u.distance + v.weight;
            if (dist[v.end] > new_distance) {
                dist[v.end] = new_distance;
                prev[v.end] = u.vertex;
                H.push(VertexDistance(v.end, new_distance));
              }
          }
    }

    if (dist[t] < INFTY)
        return dist[t];
    else
        return -1;
}

// int main() {
//   vector<vector<WeightedLink> > adj(4, vector<WeightedLink>());
//
//   adj[0].push_back(WeightedLink(1, 1));
//   adj[3].push_back(WeightedLink(0, 2));
//   adj[1].push_back(WeightedLink(2, 2));
//   adj[0].push_back(WeightedLink(2, 5));
//   int s = 0, t = 2;
//   int d = distance(adj, s, t);
//   std::cout << d;
//   return 0;
// }

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<WeightedLink> > adj(n, vector<WeightedLink>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(WeightedLink(y - 1, w));
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}

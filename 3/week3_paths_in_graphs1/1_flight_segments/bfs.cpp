#include <iostream>
#include <vector>
#include <queue>


using std::vector;
using std::queue;

// Represent a graph by its adjacency list
using Graph = vector<vector<int> >;

const int INFTY_INT = -1;

// Return distance between 's' and 't', or -1 if the points are not connected
int distance(Graph &g, int s, int t) {
    int V = g.size();
    std::vector<int> distance(V, INFTY_INT);
    distance[s] = 0;
    queue<int> to_explore;
    to_explore.push(s);
    while(not to_explore.empty()) {
        int v = to_explore.front();
        for (const int & x : g[v]) {
            if (distance[x] == INFTY_INT) {
                to_explore.push(x);
                distance[x] = distance[v] + 1;
            }
        }
        to_explore.pop();
    }
    return distance[t];
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
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, s, t);
}

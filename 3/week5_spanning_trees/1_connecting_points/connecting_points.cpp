#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <unordered_set>
#include <cmath>

using std::vector;
using std::priority_queue;
using std::unordered_set;

const double INFTY = 1e+6;

struct Point {
    int x, y;
    Point () : x(0), y(0) {}
    Point (int x_, int y_) : x(x_), y(y_) {}
    friend double distance (const Point & a, const Point & b) {
      double dx = a.x - b.x, dy = a.y - b.y;
      return sqrt(dx * dx + dy * dy);
    }
};

struct IndexCost {
  int index;
  double cost;
  IndexCost (int index_, double cost_) : index(index_), cost(cost_) {}
  friend bool operator>(const IndexCost & l, const IndexCost & r) {
      return l.cost > r.cost;
  }
};

double minimum_length(vector<Point> s) {
    double result = 0.;
    int N = s.size();
    vector<double> cost(N, INFTY);
    cost[0] = 0.;

    priority_queue<IndexCost,
                   vector<IndexCost>,
                   std::greater<IndexCost>
      > Q;
    for (int i = 0; i < N; i++)
        Q.push(IndexCost(i, cost[i]));

    unordered_set<int> visited;
    while (not Q.empty()) {
      int i = Q.top().index; Q.pop();
      if (visited.find(i) != visited.end())
          continue;
      visited.insert(i);
      result += cost[i];
      for (int j = 0; j < N; j++) {
          if (j == i)
              continue;
          double new_cost = distance(s[i], s[j]);
          if (cost[j] > new_cost) {
            cost[j] = new_cost;
            Q.push(IndexCost(j, cost[j]));
          }
      }
    }
    return result;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<Point> s(n);
  int x,y;
  for (size_t i = 0; i < n; i++) {
    std::cin >> x >> y;
    s[i] = Point(x, y);
  }
  std::cout << std::setprecision(10) << minimum_length(s) << std::endl;
}

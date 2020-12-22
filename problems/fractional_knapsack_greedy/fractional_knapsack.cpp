// Solve the fractional Knapsack problem

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

// #include "fractional_knapsack.h"

using std::vector;
using std::pair;

namespace fractional_knapsack {
    
    double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
        double value = 0.0;
        
        // Define vector of value-weight pairs --- O(n)
        vector<pair<int, int> > values_weights;
        for(int i = 0; i < values.size(); i++) {
            values_weights.push_back({values[i], weights[i]});
        }
        
        // Sort value-weight pairs by decreasing value density --- O(n log(n))
        std::sort(values_weights.begin(), values_weights.end(), 
                  [](auto &left, auto &right) {
                      double left_density = (double(left.first) / left.second);
                      double right_density = (double(right.first) / right.second);
                      return  left_density > right_density;
                      }
                 );
        
        // Fill the knapsack greedily --- O(n)
        for(const auto& pair : values_weights) {
            if (capacity == 0) break;
            double amount = std::min(capacity, pair.second);
            capacity -= amount;
            value += amount * ((double) pair.first / pair.second);
        }
        
        return value;
    }
    
} // namespace fractional_knapsack

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = fractional_knapsack::get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}

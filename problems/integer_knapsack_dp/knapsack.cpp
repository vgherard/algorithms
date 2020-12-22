// Solve the integer Knapsack problem without repetitions.
//
// Dynamic programming solution with pseudo-polynomial 
// time complexity O(W * length(weights))
//
// Problem: given an integer vector 'weights': 
// find the largest sum of distinct elements of 'weights', 
// with the constraint 'sum < W'.

#include <iostream>
#include <vector>

using std::vector;    

int optimal_weight(int W, const vector<int> &weights) {
    int nrow = W + 1, ncol = weights.size() + 1;
    int ROW = 1, COL = nrow;
    vector<int> value(nrow * ncol);
    
    for (int i = 0; i < nrow; i++)
        value[ROW * i + COL * 0] = 0;
    for (int j = 0; j < ncol; j++)
        value[ROW * 0 + COL * j] = 0;
    
    int temp_value;
    for (int j = 1; j < ncol; ++j) {
        for (int i = 1; i < nrow; ++i) {
            temp_value = value[ROW * i + COL * (j - 1)];
            int w_j = weights[j - 1];
            if (w_j <= i)
                temp_value = std::max(temp_value, value[ROW * (i - w_j) + COL * (j - 1)] + w_j);
            value[ROW * i + COL * j] = temp_value;
        }
    }
    
//     Print edit_matrix
//     for (int i = 0; i < nrow; i++) {
//         for (int j = 0; j < ncol; j++) {
//             std::cout << value[ROW * i + COL * j] << " ";
//         }
//         std::cout << "\n";
//     }
    

    
    return value[ROW * W + COL * weights.size()];
}

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}

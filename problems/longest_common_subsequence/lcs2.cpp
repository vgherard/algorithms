// Compute the longest common substring length of two strings
//
// Dynamic programming solution with time complexity O(n * m)

#include <iostream>
#include <vector>

using std::vector;

int lcs2(vector<int> &a, vector<int> &b) {
    
    int nrow = a.size() + 1, ncol = b.size() + 1;
    int ROW = 1, COL = nrow;
    std::vector<int> lcs_matrix(nrow * ncol);
    int i, j;
    
    // Initialize first row and column
    for(i = 1; i < nrow; i++) {
        lcs_matrix[ROW * i + COL * 0] = 0;
    }
    for(j = 1; j < ncol; j++) {
        lcs_matrix[ROW * 0 + COL * j] = 0;
    }
    
    // Fill recursively the LCS matrix
    int prev; 
    for (i = 1; i < nrow; i++) {
        for (j = 1; j < ncol; j++) {
            if (a[i - 1] == b[j - 1]) {
                prev = lcs_matrix[ROW * (i - 1) + COL * (j - 1)];
                lcs_matrix[ROW * i + COL * j] = prev + 1;
            } else {
                prev = std::max(lcs_matrix[ROW * (i - 1) + COL * j], 
                                lcs_matrix[ROW * i + COL * (j - 1)]
                               );
                lcs_matrix[ROW * i + COL * j] = prev;   
            }
        }
    }
    
// Print lcs_matrix
//     for (i = 0; i < nrow; i++) {
//         for (j = 0; j < ncol; j++) {
//             std::cout << lcs_matrix[ROW * i + COL * j] << " ";
//         }
//         std::cout << "\n";
//     }
    
    return lcs_matrix[ROW * (nrow - 1) + COL * (ncol - 1)];
    
    
}


int main() {
    size_t n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    size_t m;
    std::cin >> m;
    vector<int> b(m);
    for (size_t i = 0; i < m; i++) {
        std::cin >> b[i];
    }

    std::cout << lcs2(a, b) << std::endl;
}

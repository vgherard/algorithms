// Compute the edit distance between two strings
//
// This dynamic programming solution has time complexity 
// O(n * m), where 'n' and 'm' are the length of the two strings.

#include <iostream>
#include <string>
#include <vector>

using std::string;

int edit_distance(const string &a, const string &b) {
    int nrow = a.length() + 1, ncol = b.length() + 1;
    int ROW = 1, COL = nrow;
    std::vector<int> edit_matrix(nrow * ncol);
    int i, j;
    
    // Initialize first row and column
    for(i = 1; i < nrow; i++) {
        edit_matrix[ROW * i + COL * 0] = i;
    }
    for(j = 1; j < ncol; j++) {
        edit_matrix[ROW * 0 + COL * j] = j;
    }
    
    // Fill recursively the edit edit_matrix
    int cost; 
    for (i = 1; i < nrow; i++) {
        for (j = 1; j < ncol; j++) {
            cost = edit_matrix[ROW * (i - 1) + COL * j] + 1;
            cost = std::min(cost, edit_matrix[ROW * i + COL * (j - 1)] + 1);
            cost = std::min(cost, edit_matrix[ROW * (i - 1) + COL * (j - 1)] + (a[i - 1] != b[j - 1]));
            edit_matrix[ROW * i + COL * j] = cost;
        }
    }
    
//// Print edit_matrix
//     for (i = 0; i < nrow; i++) {
//         for (j = 0; j < ncol; j++) {
//             std::cout << edit_matrix[ROW * i + COL * j] << " ";
//         }
//         std::cout << "\n";
//     }
//     
    return edit_matrix[ROW * (nrow - 1) + COL * (ncol - 1)];
    
}

int main() {
    string str1;
    string str2;
    std::cin >> str1 >> str2;
    std::cout << edit_distance(str1, str2) << std::endl;
    return 0;
}

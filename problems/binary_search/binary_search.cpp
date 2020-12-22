// Binary Search
//
// Find an element 'x' in a sorted array 'a' in logarithmic time


#include <vector>

using std::vector;

// #include "binary_search.h"

namespace binary_search {
    
    // Limit the search to the sub-vector a[l:r]
    int binary_search(const vector<int> &a, int x, int l, int r) {
        // Handle case where 'x' is not in 'a'
        if (r < l) return -1;
        
        // Divide and conquer: split array by two
        int m = l + (r - l) / 2;
        
        // If a[m] != x, look in the half of 'a' where 'x' could be found.
        if (a[m] == x) return m;
        else if (x < a[m]) return binary_search(a, x, l, m - 1);
        else return binary_search(a, x, m + 1, r);
    }
    
    // Wrapper around binary_search with some left and right limits
    int binary_search(const vector<int> &a, int x) {
        return binary_search(a, x, 0, a.size() - 1);
    }

} // namespace binary_search


// #include <iostream>
// int main() {
//     vector<int> v{0, 0, 0, 1, 2, 2, 2};
//     std::cout << binary_search::binary_search(v, 1) << '\n'; // 3
// }

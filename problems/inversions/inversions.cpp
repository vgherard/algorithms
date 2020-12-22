// Sort a vector with 'MergeSort'; compute the number of inversions in the original.

#include <iostream>
#include <vector>

// #include "inversions.h"

using std::vector;

void merge(vector<int> &a, size_t l, size_t r, size_t m, long long & inversions) {
    vector<int> temp;
    
    size_t l_pos = l, r_pos = m;
    while (temp.size() < r - l) {
        while (l_pos < m and r_pos < r) {
            if (a[l_pos] <= a[r_pos]) {
                temp.push_back(a[l_pos]); l_pos++;
            } else {
                temp.push_back(a[r_pos]); r_pos++;
                inversions += m - l_pos;
            }
        }
        while (l_pos < m) {
            temp.push_back(a[l_pos]); l_pos++;
        }
        while (r_pos < r) {
            temp.push_back(a[r_pos]); r_pos++;
        }
        
    }
    
    for(size_t i = l; i < r; ++i) a[i] = temp[i - l];
    return;    
}

void merge_sort(vector<int> &a, size_t l, size_t r, long long & inversions) {
    // Nothing to do for less than two elements
    if (r - l < 2) return;
    size_t m = l + (r - l) / 2;
    merge_sort(a, l, m, inversions);
    merge_sort(a, m, r, inversions);
    merge(a, l, r, m, inversions);
    return;
}

long long get_inversions(vector <int> &a) {
    long long inversions = 0;
    merge_sort(a, 0, a.size(), inversions);
    return inversions;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    std::cout << get_inversions(a) << '\n';
}

// Check if input vector has a majority element in O(nlog(n)) time.
//
// Majority element: an element occupying more than 50% of the
// given array

#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

bool has_majority_element(vector<int> &a) {
    int n = a.size();
    
    // Sort input array --- O(nlog(n))
    std::sort(a.begin(), a.end());
    
    // Scan sorted array; --- O(n)
    // stop if an element repeats more than n / 2 times.
    int x_prev = a[0]; 
    int count = 0;
    for(const auto & x : a) {
        count = count * (x == x_prev) + 1;
        if (count > n / 2) {
            return true;
        }
        x_prev = x;
    }
    
    return false;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    std::cout << has_majority_element(a) << '\n';
}

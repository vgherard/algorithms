// Dynamic programming solution to the 'Change' problem (see also change.cpp)
// 
//
// Compared to the greedy algorithm, this has O(n * m) pseudo-polynomial runtime,
// but gives always the correct solution.

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

int get_change(int m, std::vector<int> denominations) {
    // coins[m] is the number of coins required to change 'm' using the money stored in denominations
    std::unordered_map<int, int> coins;
    coins[0] = 0;
    for(int n = 1; n <= m; n++) {
        std::vector<int> candidates;
        int min = n + 1;
        for (const int & denomination : denominations) {
            if (denomination <= n) {
                min = std::min(min, coins[n - denomination] + 1);
            }
        }
        coins[n] = min;
    }
    return coins[m];
}

int main() {
    int m;
    std::cin >> m;
    std::cout << get_change(m, {1, 3, 4}) << '\n';
}

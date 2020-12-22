// Greedy algorithm for the Change problem
//
//      Given an amount 'm' and denominations d = {d1, d2, ..., dN}, 
//      find a minimal number of indices {i1, i2, ..., in} s.t.
//      d[i1] + d[i2] + ... + d[in] = m.
//      N.B.: The greedy algorithm does not always give an optimal
//      (in terms of the number 'n' of coins) solution.

#include <iostream>
#include <array>

// #include "change.h"

namespace change {
    
    std::array<int, 3> values {10, 5, 1};
    
    int get_change(int m) {
        int n = 0;
        for(const auto& value : values){
            n += m / value;
            m = m % value;
        }
        return n;
    }

} // namespace change



int main() {
  int m;
  std::cin >> m;
  std::cout << change::get_change(m) << '\n';
}

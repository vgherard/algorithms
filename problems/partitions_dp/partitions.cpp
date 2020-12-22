// Check if integer vector can be partitioned in 'n' sub-vectors with equal sums.
//
// Below the solution for n = 3.

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

// #include "partitions.h"

namespace partitions {
    
    // Find all partitions of 'A[from:...)' summing to 's' --- O(length(A)^2)
    std::vector<std::vector<int> > summing_to(int s, std::vector<int> &A, int from) {
        std::vector<std::vector<int> > partitions;
    
        for(int i = from; i < A.size(); i++) {
            if (s < A[i]) 
                continue;
            if (s == A[i]) {
                partitions.push_back(std::vector<int> {i});
                continue;
            }
            std::vector<std::vector<int> > previous_partitions = summing_to(s - A[i], A, from = i + 1);
            for (auto & p: previous_partitions) {
                p.push_back(i);
                partitions.push_back(p);
            }
        }
    
        return partitions;
    }
    
    // Check whether decreasing vectors A and B have common elements --- O(n)
    bool intersect(std::vector<int> & A, std::vector<int> & B) {
        auto a = A.begin(), b = B.begin(), a_end = A.end(), b_end = B.end();
        while(a < a_end and b < b_end) {
            if (*a == *b) return true;
            else if (*a > *b) ++a;
            else ++b;
        }
        return false;
    }
    
    // Check whether there are at least three non-intersecting partitions
    bool three_distinct(std::vector<std::vector<int> > & partitions) {
        if(partitions.size() < 3) return false;
        for(int i = 0; i < partitions.size() - 2; i++) {
            for(int j = i + 1; j < partitions.size() - 1; j++) {
                for(int k = j + 1; k < partitions.size(); k++) {
                    if(intersect(partitions[i], partitions[j])) continue;
                    if(intersect(partitions[j], partitions[k])) continue;
                    if(intersect(partitions[k], partitions[i])) continue;
                    return true;
                }
            }
        }
        return false;
    } 
} // namespace partitions


// Solve the main problem
bool partitions3(vector<int> &A) {
    int total; for(const auto & a: A) total += a;
    // If 'total', can be split in three equal parts, then it must be a multiple of three.
    if (total % 3 != 0) return false;
    auto partitions = partitions::summing_to(total / 3, A, 0);
    return partitions::three_distinct(partitions);
}

int main() {
    int n;
    std::cin >> n;
    vector<int> A(n);
    for (size_t i = 0; i < A.size(); ++i) {
        std::cin >> A[i];
    }
    std::cout << partitions3(A) << '\n';
}

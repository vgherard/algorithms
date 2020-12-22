#if !defined(INVERSIONS_H)
#define INVERSIONS_H

#include <vector>

void merge(std::vector<int> &, size_t, size_t, size_t, long long &);
void merge_sort(std::vector<int> &, size_t, size_t, long long &);
long long get_inversions(std::vector<int> &);


#endif

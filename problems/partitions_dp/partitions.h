#if !defined(PARTITIONS_H)
#define PARTITIONS_H
#include <vector>

namespace partitions {
    std::vector<std::vector<int> > summing_to(int, std::vector<int> &, int from = 0);
    bool intersect(std::vector<int> &, std::vector<int> &);
} // namespace partitions

#endif

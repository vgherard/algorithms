#if !defined(CAR_FUELING_H)
#define CAR_FUELING_H

#include <vector>

namespace car_fueling {
    int compute_min_refills(int dist, int tank, std::vector<int> & stops);
} // namespace car_fueling

#endif

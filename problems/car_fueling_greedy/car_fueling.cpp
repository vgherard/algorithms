// Problem statement. 
//      You have to travel a distance 'd'; 
//      with a full tank of gasoline, you can travel at most a distance 'm';
//      You can stop and refill gasoline at 'stops[0], stops[1], ...'.
//      Find the minimal number of stops required to get to the end.
//
// Greedy solution below.

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;

// #include "car_fueling.h"

namespace car_fueling {
    
    int compute_min_refills(int d, int m, vector<int> & stops) {
        
        stops.insert(stops.begin(), 0);
        stops.push_back(d);
        
        int refills = 0;
        
        auto current = stops.begin(), next = current, end = stops.end() - 1;
        while (current != end) {
            while (next != end and *(next + 1) - *current <= m) ++next;
            if (next == current) return -1;
            if (next != end) refills++;
            current = next;
        }
        
        return refills;
    }
    
} // namespace car_fueling




int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << car_fueling::compute_min_refills(d, m, stops) << "\n";

    return 0;
}

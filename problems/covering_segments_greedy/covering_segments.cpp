// Given a set of segments, find a minimal set of points hitting intersecting all segments

#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

struct Segment {
  int start, end;
};

vector<int> optimal_points(vector<Segment> &segments) {
    vector<int> points;
    
    std::sort(segments.begin(), segments.end(),
              [](Segment& left, Segment& right) {return left.start < right.start;}
             );
    auto it = segments.begin(), end = segments.end();
    while (it < end) {
        int end_max = (*it).end;
        while( 
            it < end - 1 and  
            (*(it + 1)).start <= std::min(end_max, (*it).end)
        ) it++;
        points.push_back( (*it).start );
        it++;
    }
    
    return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

size_t LeftChild(size_t i) { return 2 * i + 1;}
size_t RightChild(size_t i) { return 2 * i + 2;}

class HeapBuilder {
private:
    vector<int> data_;
    vector< pair<int, int> > swaps_;

    void WriteResponse() const {
        cout << swaps_.size() << "\n";
        for (int i = 0; i < swaps_.size(); ++i) {
            cout << swaps_[i].first << " " << swaps_[i].second << "\n";
        }
    }

    void ReadData() {
        int n;
        cin >> n;
        data_.resize(n);
        for(int i = 0; i < n; ++i)
            cin >> data_[i];
    }

    void SiftDown(size_t i) {
        size_t size = data_.size();
        size_t minIndex = i;
        size_t child = LeftChild(i);
        if(child < size and data_[child] < data_[minIndex])
            minIndex = child;
        child = RightChild(i);
        if(child < size and data_[child] < data_[minIndex])
            minIndex = child;
        if(i != minIndex) {
            swap(data_[i], data_[minIndex]);
            swaps_.push_back(make_pair(i, minIndex));
            SiftDown(minIndex);
        }
            
    }
    
    void GenerateSwaps() {
        size_t n = data_.size();
        for (int i = n / 2 - 1; i >= 0; --i) {
            SiftDown(i);
        }
    }

 public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}

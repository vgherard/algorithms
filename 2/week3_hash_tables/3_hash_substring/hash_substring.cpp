#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

using std::string;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

size_t hash(const string& s, size_t p, size_t x) {
    unsigned long long hash = 0;
    for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
        hash = (hash * x + s[i]) % p;
    return hash;
} // Compute polynomial hash of a string

std::vector<size_t> PrecomputeHashes(const string& t,
                                     size_t len, size_t p, size_t x) {
    std::vector<size_t> H(t.size() - len + 1);
    string s = t.substr(t.size() - len, len);
    H[t.size() - len] = hash(s, p, x);
    size_t y = 1;
    for (size_t i = 0; i < len; ++i) y = (y * x) % p;
    for (int i = t.size() - len - 1; i >= 0; --i) {
        H[i] = (x * H[i + 1] + t[i] - y * t[i + len]) % p;
    }
    return H;
} // Precompute hashes of text

std::vector<int> get_occurrences (const Data& input) {
    const size_t p = 1000000007;
    // Sample multiplier from integer uniform distribution in [0, p - 1]
    const size_t x = rand() % (p - 1);
    const string& s = input.pattern, t = input.text;
    size_t pattern_hash = hash(s, p, x);
    std::vector<size_t> text_hashes = PrecomputeHashes(t, s.size(), p, x);
    std::vector<int> ans;
    for (size_t i = 0; i + s.size() <= t.size(); ++i) {
        if (text_hashes[i] != pattern_hash) continue;
        if (t.substr(i, s.size()) == s) ans.push_back(i);
    }
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}

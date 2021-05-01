#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class CompareSuffix {
	const string& text_;
	size_t len_;
public:
	CompareSuffix (const string& text) : text_(text), len_(text.length()) {}
	bool operator() (size_t l, size_t r) {
		if (l == r)
			return false;
		while(text_[l] == text_[r]) {
			l = (l + 1) % len_; r = (r + 1) % len_;
		}
		if (text_[l] == '$') return true;
		if (text_[r] == '$') return false;
		return text_[l] < text_[r];
	}
};

std::string BWT(const std::string& text) {
	std::string result = "";

	// Construct sorted suffix array of 'text'
	vector<size_t> a(text.size());
	for (size_t i = 0; i < text.size(); ++i) {
		a[i] = i;
	}
	std::sort(a.begin(), a.end(), CompareSuffix(text));
	for (size_t pos : a) {
		pos = (pos == 0) ? text.size() - 1 : pos - 1;
		result.push_back(text[pos]);
	}

	return result;
}

int main() {
	string text;
	cin >> text;
	cout << BWT(text) << endl;
	return 0;
}

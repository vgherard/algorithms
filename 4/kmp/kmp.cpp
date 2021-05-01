#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

vector<size_t> prefix_function(const string& pattern) {
	size_t len = pattern.length();
	vector<size_t> s(len, 0);
	size_t border = 0;
	for (size_t i = 1; i < len; ++i) {
		while (border > 0 and pattern[i] != pattern[border])
			border = s[border - 1];
		if (pattern[i] == pattern[border])
			++border;
		else
			border = 0;
		s[i] = border;
	}
	return s;
}

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where
// the pattern starts in the text.
vector<size_t> find_pattern(const string& pattern, const string& text) {
	string str = pattern + "$" + text;
	vector<size_t> s = prefix_function(str);

	vector<size_t> res;
	size_t pat_len = pattern.length(), str_len = str.length();
	for (size_t i = pat_len + 1; i < str_len; ++i)
		if (s[i] == pat_len)
			res.push_back(i - 2 * pat_len);

	return res;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<size_t> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}

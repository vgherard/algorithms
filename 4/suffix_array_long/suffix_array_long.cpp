#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

const size_t ALPHABET_SIZE = 5;
const std::unordered_map<char, size_t> char_to_int
	{{'$', 0}, {'A', 1}, {'C', 2}, {'G', 3}, {'T', 4}};

vector<size_t> SortCharacters(const string& text)
{
	size_t n = text.size();
	vector<size_t> res(n), count(ALPHABET_SIZE);

	for (size_t i = 0; i < n; ++i)
		++count[char_to_int.at(text[i])];
	for (size_t j = 1; j < ALPHABET_SIZE; ++j)
		count[j] += count[j - 1];
	for (int i = n - 1; i >= 0; --i) {
		size_t c = char_to_int.at(text[i]);
		--count[c];
		res[count[c]] = i;
	}

	return res;
}

vector<size_t> ComputeCharClasses(const string &text, vector<size_t> order) {
	size_t n = text.length();
	vector<size_t> classes(n);
	classes[order[0]] = 0;
	for (size_t i = 1; i < n; ++i) {
		classes[order[i]] = classes[order[i - 1]];
		if (text[order[i]] != text[order[i - 1]])
			++classes[order[i]];
	}
	return classes;
}


vector<size_t> SortDoubled(
		const string& text,
		size_t cur_len,
		vector<size_t> order,
		vector<size_t> classes
	)
{
	size_t n = text.size();
	vector<size_t> count(n), res(n);

	for (size_t i = 0; i < n; ++i)
		count[classes[i]] = count[classes[i]] + 1;
	for (size_t j = 1; j < n; ++j)
		count[j] += count[j - 1];
	for (int i = n - 1; i >= 0; --i) {
		size_t start = (order[i] - cur_len + n) % n;
		size_t cl = classes[start];
		--count[cl];
		res[count[cl]] = start;
	}

	return res;
}

vector<size_t> UpdateClasses(
		vector<size_t> order, vector<size_t> classes, size_t cur_len
	)
{
	size_t n = order.size();
	vector<size_t> res(n);
	res[order[0]] = 0;

	for (size_t i = 1; i < n; ++i) {
		size_t cur = order[i], prev = order[i - 1];
		size_t mid = (cur + cur_len) % n;
		size_t mid_prev = (prev + cur_len) % n;

		res[cur] = res[prev];
		if ( classes[cur] != classes[prev] or classes[mid] != classes[mid_prev] )
			++res[cur];
	}
	return res;
}

vector<size_t> BuildSuffixArray(const string& text) {
	vector<size_t> order = SortCharacters(text);
	vector<size_t> classes = ComputeCharClasses(text, order);

	size_t cur_len = 1, len = text.length();
	while (cur_len < len) {
		order = SortDoubled(text, cur_len, order, classes);
		classes = UpdateClasses(order, classes, cur_len);
		cur_len *= 2;
	}

	return order;
}

int main() {
	string text;
	cin >> text;
	vector<size_t> suffix_array = BuildSuffixArray(text);
	for (int i = 0; i < suffix_array.size(); ++i) {
		cout << suffix_array[i] << ' ';
	}
	cout << endl;
	return 0;
}

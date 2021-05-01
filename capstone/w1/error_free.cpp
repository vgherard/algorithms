#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using std::vector;
using std::string;

bool suff_pref_match(const string & l, const string & r, size_t offset) {
	size_t len = l.length();
	for (size_t i = offset; i < len; ++i)
		if (l[i] != r[i - offset])
			return false;
	return true;
}


int overlap(const string &  l, const string & r) {
	size_t len = l.length();
	if (r.length() != len) throw;

	size_t offset = 0;
	for (; offset < len; ++offset)
		if (suff_pref_match(l, r, offset))
			break;

	return len - offset;
}

// std::pair<size_t, size_t> max_overlap(string l, vector<string> r) {
// 	size_t len = l.length();
// 	size_t overlap = 0;
// 	while (true) {
// 		for (size_t i = 0; i < r.size(); ++i) {
//
// 		}
// 	}
// 		if (suff_pref_match(l, r, offset))
// 			break;
//
// 		return len - offset;
// }

string assemble(const vector<string>& reads)
{
	size_t start = 0;

	size_t cur = start;
	string res = reads[cur];
	std::unordered_set<size_t> used = {cur};

	size_t n = reads.size();
	while (used.size() < n) {
		std::pair<size_t, int> next = {cur, -1};
		for (size_t i = 0; i < n; ++i) {
			if (used.find(i) != used.end()) continue;
			int overlap_i = overlap(reads[cur], reads[i]);
			if (overlap_i > next.second)
				next = {i, overlap_i};
		}
		res += reads[next.first].substr(next.second);
		cur = next.first;
		used.insert(cur);
	}

	size_t end = cur;
	res = res.substr(overlap(reads[end], reads[start]));

	return res;
}

int main()
{
	vector<string> reads;
	std::unordered_set<string> seen;

	string input;
	while(std::cin >> input) {
		if (seen.find(input) != seen.end()) continue;
		reads.push_back(input);
		seen.insert(input);
	}


	std::cout <<  assemble(reads) << '\n';

	return 0;
}

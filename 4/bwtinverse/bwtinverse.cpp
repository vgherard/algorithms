#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

std::string CHARS = "$ACGT";

string InverseBWT(const string& bwt) {
	size_t len = bwt.length();
	string text(len, 'X');

	std::unordered_map<char, int> nucleotide_counts;
	std::vector<size_t> index(len);
	for (size_t i = 0; i < len; ++i) {
		char c = bwt[i];
		index[i] = nucleotide_counts[c]++;
	}

	// Position where runs start in sorted sequence of nucleotides
	std::unordered_map<char, int> runs_positions;
	size_t tmp_sum = 0;
	for (auto c : CHARS) {
		runs_positions[c] = tmp_sum;
		tmp_sum += nucleotide_counts[c];
	}

	size_t cur_pos = 0;
	char cur_char = '$';
	for (size_t i = 1; i <= len; ++i) {
		text[len - i] = cur_char;
		cur_char = bwt[cur_pos];
		cur_pos = runs_positions[cur_char] + index[cur_pos];
	}

	return text;
}

int main() {
	string bwt;
	cin >> bwt;
	cout << InverseBWT(bwt) << endl;
	return 0;
}

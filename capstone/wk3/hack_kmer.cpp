#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using std::cin;
using std::string;
using std::vector;
using std::unordered_map;
using std::unordered_set;

bool is_balanced(const vector<string>& reads, size_t k) {

	class Status {
		int s_;
	public:
		Status () : s_(0) {}
		bool is_balanced () const { return s_ == 0; }
		void operator++() { if (s_ != 1) s_++; }
		void operator--() { if (s_ != -1) s_--; }
	};

	size_t len = reads[0].length();
	unordered_set<string> processed;
	unordered_map<string, Status> balances;
	
	for (string read : reads) {
		for (size_t i = 0; i < len - k; ++i) {
			string kp1mer = read.substr(i, k + 1);
			if (processed.find(kp1mer) != processed.end())
				continue;
			processed.insert(kp1mer);
			++balances[read.substr(i, k)];
			--balances[read.substr(i + 1, k)];
		}
	}

	for (auto pair : balances)
		if (not pair.second.is_balanced())
			return false;

	return true;
}

int main()
{
	string input;
	vector<string> reads;

	while(std::cin >> input)
		reads.push_back(input);

	size_t k = reads[0].length() - 1;
	for (; k > 1; --k) {
		if (is_balanced(reads, k))
			break;
	}

	std::cout << k + 1 << '\n';

	return 0;
}

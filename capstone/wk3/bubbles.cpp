#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using std::string;
using std::vector;
using std::unordered_map;
using std::unordered_set;

class Graph {
	vector<vector<size_t> > adj_;
	size_t common_vertices(unordered_set<size_t> p, unordered_set<size_t>q)
	{
		size_t res = 0;
		auto pend = p.end();
		for (auto v : q)
			if (p.find(v) != p.end())
				++res;
		return res;
	}
public:
	Graph(vector<string> reads, size_t k) {
		unordered_set<string> processed;
		unordered_map<string, size_t> kmers;
		for (string read : reads) {
			size_t len = read.length();
			for (size_t i = 0; i < len - k; ++i) {
				string kp1mer = read.substr(i, k + 1);
				if (processed.find(kp1mer) != processed.end())
					continue;
				processed.insert(kp1mer);
				string prefix = read.substr(i, k);
				if (kmers.find(prefix) == kmers.end()) {
					kmers[prefix] = adj_.size();
					adj_.push_back(vector<size_t>());
				}

				string suffix = read.substr(i + 1, k);
				if (kmers.find(suffix) == kmers.end()) {
					kmers[suffix] = adj_.size();
					adj_.push_back(vector<size_t>());
				}
				adj_[kmers[prefix]].push_back(kmers[suffix]);
			}
		}
	}

	size_t n_bubbles(size_t thresh) {
		size_t res = 0;
		for (size_t v = 0; v < adj_.size(); ++v) {
			if(adj_[v].size() < 2) continue;
			res += count_bubbles(v, thresh);
		}
		return res;
	}

	void LDFS(
		size_t from,
		size_t steps_left,
		unordered_set<size_t>& visited,
		unordered_map<size_t, vector<unordered_set<size_t> > >& paths,
		unordered_set<size_t> this_path = {}
		)
	{
		if (visited.find(from) != visited.end())
			return;
		visited.insert(from);
		this_path.insert(from);
		paths[from].push_back(this_path);
		if (steps_left == 0)
			return;
		for (size_t v : adj_[from])
			LDFS(v, steps_left - 1, visited, paths, this_path);

		visited.erase(visited.find(from));
	}

	size_t count_bubbles(size_t from, size_t thresh) {
		size_t res = 0;
		unordered_set<size_t> visited;
		unordered_map<size_t, vector<unordered_set<size_t> > > paths;
		unordered_set<size_t> this_path;
		LDFS(from, thresh, visited, paths);
		for (size_t to = 0; to < adj_.size(); ++to) {
			if (to == from)
				continue;
			size_t n_paths = paths[to].size();
			for (size_t i = 0; i < n_paths; ++i) {
				for (size_t j = i + 1; j < n_paths; ++j)
					if (common_vertices(paths[to][i], paths[to][j]) == 2)
						++res;
				}
		}
		return res;
	}
};

int main()
{
	size_t k, thresh;
	std::cin >> k >> thresh;

	vector<string> reads;
	string input;
	while(std::cin >> input)
		reads.push_back(input);

	Graph g(reads, k - 1);

	std::cout << g.n_bubbles(thresh + 1) << '\n';

	return 0;
}

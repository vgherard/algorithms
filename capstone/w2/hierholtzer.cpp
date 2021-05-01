#include <vector>
#include <string>
#include <deque>
#include <iostream>

using std::vector;
using std::deque;

class Graph {
	using AdjList = vector<vector<size_t> >;
	size_t V_;
	size_t E_;
	AdjList adj_;
	bool is_balanced_;
public:
	Graph() {
		std::cin >> V_ >> E_;
		adj_.resize(V_);
		vector<int> balances(V_);

		for (int i = 0; i < E_; ++i) {
			size_t from, to;
			std::cin >> from >> to;
			adj_[from - 1].push_back(to - 1);
			++balances[from - 1];
			--balances[to - 1];
		}

		is_balanced_ = true;
		for (int i = 0; i < V_; ++i)
			if (balances[i] != 0)
				is_balanced_ = false;

		return;
	}

	deque<size_t> EulerianPath() const
	{
		if (not is_balanced_)
			return deque<size_t>();

		vector<size_t> used(V_);
		deque<size_t> p;
		p.push_back(0);
		while (p.size() < E_ + 1) {
			size_t pos = p.back();
			if (pos != p.front() or used[pos] < adj_[pos].size()) // we can continue normally
				p.push_back(adj_[pos][used[pos]++]);
			else
			{
				p.pop_front(); p.push_back(p.front());
			}
		}

		return p;
	}

};


int main() {
	Graph g;
	deque<size_t> p = g.EulerianPath();

	if (p.empty())
		std::cout << 0 << std::endl;
	else
	{
		std::cout << 1 << std::endl;
		while (p.size() > 1) {
			std::cout << p.front() + 1 << " ";
			p.pop_front();
		}

		std::cout << std::endl;
	}

	return 0;
}


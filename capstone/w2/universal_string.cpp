#include <iostream>
#include <vector>
#include <string>
#include <deque>

std::string UniversalString(size_t k)
{
	size_t V = 1 << (k - 1); // n. vertices of De Bruijn graph
	size_t E = 1 << k; // n. edges of De Bruijn graph
	// Each vertex corresponds to a number from 0 to 2^(k - 1) - 1;
	// Each vertex v has two edges, corresponding to the numbers
	// 2 * v and 2 * v + 1, which end in the vertices
	// (2 * v) % 2 ^ (k - 1) and (2 * v + 1) % 2 ^ (k - 1)
	// respectively.
	// The universal string is given by an Eulerian path in this
	// graph.

	std::deque<int> p;
	std::vector<int> used(V);
	p.push_back(0);
	while (p.size() < E + 1) {
		int pos = p.back();
		if (pos != p.front() or used[pos] < 2) {
			pos = (pos << 1) + used[pos]++;
			pos &= ~(1 << k - 1);
			p.push_back(pos);
		} else {
			p.pop_front(); p.push_back(p.front());
		}
	}

	// At this point, the deque should contain the vertices of the
	// Eulerian path in the De Bruijn graph.

	// To construct the universal string, it is enough to append
	// the parity of all vertices in the Eulerian PATH (cycle
	// excluding the duplicated vertex)
	std::string res = "";
	p.pop_front();
	while (not p.empty()) {
		res += (p.front() % 2 == 0) ? "0": "1";
		p.pop_front();
	}

	return res;
}


int main() {
	size_t k;
	std::cin >> k;
	std::cout << UniversalString(k) << '\n';
	return 0;
}

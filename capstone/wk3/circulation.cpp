#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#define MAX_CAPACITY 1e6

using std::vector;
using std::cin;
using std::cout;

#include <queue>
#include <unordered_map>

class FlowGraph {
public:
	struct Edge {
		int from, to, capacity, flow, lower;
	};

private:
	/* List of all - forward and backward - edges */
	vector<Edge> edges;
	vector<int> lower_bounds;

	/* These adjacency lists store only indices of edges in the edges list */
	vector<vector<size_t> > graph;
	struct NoPath {};
public:
	FlowGraph()
	{
		int vertex_count, edge_count;
		std::cin >> vertex_count >> edge_count;
		graph.resize(vertex_count + 2);
		lower_bounds.resize(edge_count);

		// demands[0] never accessed
		vector<int> demands(vertex_count + 1);

		for (int i = 0; i < edge_count; ++i) {
			int u, v, l, c;
			std::cin >> u >> v >> l >> c;
			add_edge(u, v, c - l);
			lower_bounds[i] = l;
			demands[u] += l;
			demands[v] -= l;
		}

		for (int v = 1; v <= vertex_count; ++v) {
			if (demands[v] < 0)
				add_edge(0, v, -demands[v]);
			else
				add_edge(v, vertex_count + 1, demands[v]);
		}


		return;

	}

	void add_edge(int from, int to, int capacity) {
		/* Note that we first append a forward edge and then a backward edge,
		 * so all forward edges are stored at even indices (starting from 0),
		 * whereas backward edges are stored at odd indices in the list edges */
		Edge forward_edge = {from, to, capacity, 0};
		Edge backward_edge = {to, from, 0, 0};
		graph[from].push_back(edges.size());
		edges.push_back(forward_edge);
		graph[to].push_back(edges.size());
		edges.push_back(backward_edge);
	}

	size_t size() const {
		return graph.size();
	}

	const vector<size_t>& get_ids(int from) const {
		return graph[from];
	}

	const Edge& get_edge(size_t id) const {
		return edges[id];
	}

	void add_flow(size_t id, int flow) {
		/* To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
		 * due to the described above scheme. On the other hand, when we have to get a "backward"
		 * edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
		 * should be taken.
		 *
		 * It turns out that id ^ 1 works for both cases. Think this through! */
		edges[id].flow += flow;
		edges[id ^ 1].flow -= flow;
	}

	void EdmondsKarpStep(int from, int to) {
		// Queue of vertices to be processed in breadth-first-search
		std::queue<int> H; H.push(0);
		// Map of vertices visited so far, storing as value a pair containing:
		// 1. The index of the previous edge in BFS
		// 2. The maximum flow affordable along the shortest path pointed by the
		// former elements.
		std::unordered_map<size_t, std::pair<int, int> > M;
		// The first zero is never accessed
		M[0] = {0, MAX_CAPACITY};

		// Current vertex being explored in Breadth-First-Search
		int v, f_v;
		int u, f_vu;
		while (not H.empty()) {
			v = H.front(); H.pop();
			f_v = M[v].second;
			for (size_t id : graph[v]) {
				f_vu = edges[id].capacity - edges[id].flow;
				u = edges[id].to;
				if (f_vu > 0 and M.find(u) == M.end())
				{
					M[u] = {id, std::min(f_vu, f_v)};
					H.push(u);
					if (u == to) goto backward_pass;
				}
			}
		}
		throw NoPath();

		backward_pass:
			int f = M[to].second;
		v = to;
		while (v != from) {
			add_flow(M[v].first, f);
			v = edges[M[v].first].from;
		}
		return;
	}

	int SaturateFlow(int from, int to) {
		while (true) {
			try {
				EdmondsKarpStep(from, to);
			} catch (NoPath cnd) {
				break;
			}
		}
		int f = 0;
		for (size_t id : graph[from])
			if (id % 2 == 0)
				f += edges[id].flow;
			return f;
	}

	void PrintSolution() {
		int f = SaturateFlow(0, size() - 1);

		int target = 0;
		for (size_t edge_id : graph[0]) {
			if (edge_id % 2 == 0)
				target += edges[edge_id].capacity;
		}

		if (f < target) {
			std::cout << "NO" << '\n';
			return;
		}

		std::cout << "YES" << '\n';
		for (size_t i = 0; i < lower_bounds.size(); ++i) {
			std::cout << lower_bounds[i] + edges[2 * i].flow << '\n';
		}

		return;
	}
};

int main() {
	FlowGraph g;
	g.PrintSolution();
	return 0;
}


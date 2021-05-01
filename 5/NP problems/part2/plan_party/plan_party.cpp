#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

struct Vertex {
	int weight;
	std::vector <int> children;
};
typedef std::vector<Vertex> Graph;

Graph ReadTree() {
	int vertices_count;
	std::cin >> vertices_count;

	Graph tree(vertices_count);

	for (int i = 0; i < vertices_count; ++i)
		std::cin >> tree[i].weight;
	for (int i = 1; i < vertices_count; ++i) {
		int from, to, weight;
		std::cin >> from >> to;
		tree[from - 1].children.push_back(to - 1);
		tree[to - 1].children.push_back(from - 1);
	}

	return tree;
}

int FunFactor(const Graph &tree, int vertex, int parent, std::vector<int>& ffs)
{
	if (ffs[vertex] == -1) {
		int p = tree[vertex].weight, q = 0;
		for (int child : tree[vertex].children) {
			if (child == parent)
				continue;
			q += FunFactor(tree, child, vertex, ffs);
			for (int grandchild : tree[child].children) {
				if (grandchild == vertex)
					continue;
				p += FunFactor(tree, grandchild, child, ffs);
			}

		}
		ffs[vertex] = std::max(p, q);
	}
	return ffs[vertex];
}

int MaxWeightIndependentTreeSubset(const Graph &tree) {
	std::vector<int> ffs(tree.size(), -1);
	size_t size = tree.size();
	if (size == 0)
		return 0;
	return FunFactor(tree, 0, -1, ffs);
}

int main() {
#if defined(__unix__) || defined(__APPLE__)
	// This code is here to increase the stack size to avoid stack overflow
	// in depth-first search.
	const rlim_t kStackSize = 64L * 1024L * 1024L;  // min stack size = 64 Mb
	struct rlimit rl;
	int result;
	result = getrlimit(RLIMIT_STACK, &rl);
	if (result == 0)
	{
		if (rl.rlim_cur < kStackSize)
		{
			rl.rlim_cur = kStackSize;
			result = setrlimit(RLIMIT_STACK, &rl);
			if (result != 0)
			{
				fprintf(stderr, "setrlimit returned result = %d\n", result);
			}
		}
	}
#endif

	// Here begins the solution
	Graph tree = ReadTree();
	int weight = MaxWeightIndependentTreeSubset(tree);
	std::cout << weight << std::endl;
	return 0;
}

#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>

using std::vector;
typedef vector<vector<int> > Matrix;

const int INF = 1e9;

Matrix read_data() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    Matrix graph(vertex_count, vector<int>(vertex_count, INF));
    for (int i = 0; i < edge_count; ++i) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        --from, --to;
        graph[from][to] = graph[to][from] = weight;
    }
    return graph;
}

int subset_size(uint32_t i)
{
	// Java: use int, and use >>> instead of >>
	// C or C++: use uint32_t
	i = i - ((i >> 1) & 0x55555555);
	i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
	return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

std::pair<int, vector<int> > optimal_path(const Matrix& graph) {
	// This solution tries all the possible sequences of stops.
	// It is too slow to pass the problem.
	// Implement a more efficient algorithm here.
	size_t n = graph.size();
	size_t n_subsets = 1 << n;
	size_t dp_table_size = n * n_subsets;
	vector<int> C(dp_table_size, INF); // usage: C(S + n_paths * vertex)
	vector<int> B(dp_table_size, -1);
	C[0] = C[1] = 0;

	// Prepare ordered list of subsets
	std::vector<size_t> subsets(n_subsets);
	for (size_t k = 0; k < subsets.size(); ++k) {
		subsets[k] = k;
	}
	std::sort(subsets.begin(), subsets.end(),
           [](size_t & l, size_t & r)
           {return subset_size(l) < subset_size(r);}
           );

	for (auto subset : subsets) {
		if (subset == 0 or subset == 1)
			continue;
		if (not (subset & (1 << 0)))
			continue;
		C[subset + n_subsets * 0] = INF;
		for (size_t i = 1; i < n; ++i) {
			C[subset + n_subsets * i] = INF;
			if (not (subset & (1 << i)))
				continue;
			for (size_t j = 0; j < n; ++j) {
				if (not (subset & (1 << j)))
					continue;
				if (j == i)
					continue;
				size_t tmp_subset = subset ^ (1 << i);
				int C_temp = C[tmp_subset + j * n_subsets] + graph[i][j];
				if (C_temp < C[subset + n_subsets * i]) {
					C[subset + n_subsets * i] = C_temp;
					B[subset + n_subsets * i] = j;
				}
			}
		}
	}

	int res_weight = INF;
	int first_step;

	for (size_t i = 1; i < n; ++i){
		int tmp_res_weight = C[subsets.back() + i * n_subsets] + graph[i][0]; 
		if (tmp_res_weight < res_weight) {
			res_weight = tmp_res_weight;
			first_step = i; 
		}
	}

	if (res_weight == INF)
		return std::make_pair(-1, std::vector<int>(0));

	std::vector<int> res_path(n);
	res_path[0] = 0 + 1;
	res_path[1] = first_step + 1;
	int subset = subsets.back();
	for (size_t i = 2; i < n; ++i) {
		size_t prev_pos = res_path[i - 1] - 1;
		res_path[i] = B[subset + prev_pos * n_subsets] + 1;
		subset = subset ^ (1 << prev_pos);
	}
	
	return std::make_pair(res_weight, res_path);
}

void print_answer(const std::pair<int, vector<int> >& answer) {
    std::cout << answer.first << "\n";
    if (answer.first == -1)
        return;
    const vector<int>& path = answer.second;
    for (size_t i = 0; i < path.size(); ++i)
        std::cout << path[i] << " ";
    std::cout << "\n";
}

int main() {
    print_answer(optimal_path(read_data()));
    return 0;
}

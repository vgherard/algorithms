#include <ios>
#include <iostream>
#include <vector>

#define N_COLORS 3

using namespace std;

class SATProblem {
	using Clause = vector<int>;

	size_t V_;
	vector<Clause> clauses_;

public:
	SATProblem (size_t V) : V_(V), clauses_(0) {}
	void add_clause(Clause clause) {
		clauses_.push_back(clause);
	}
	void print_SAT() {
		std::cout << clauses_.size() << " " << V_ << std::endl;
		for (const Clause & clause : clauses_) {
			for (int x : clause)
				std::cout << x << " ";
			std::cout << 0 << std::endl;
		}
	}
};

// We use num_vertices * num_col boolean variables
//	x_ic = 'color of vertex 'i' is 'c'
// to which we enforce the constraints:
//
// 1. For all vertices i = 1...num_vertices:
//	x_ir OR x_ig OR x_ib,
// i.e. vertex 'i' has at least one color.
//
// 2. For all vertices i = 1...num_vertices:
//	!x_ir OR !x_ig
//	!x_ir OR !x_ib
//	!x_ig OR !x_ib
// i.e. vertex 'i' has at most one color.
//
// 3. For all edges {i, i'}:
//	!x_ir OR !x_i'r
//	!x_ig OR !x_i'g
//	!x_ib OR !x_i'b
// i.e. two vertexes cannot be of the same color.
//
// This is a total of
//	tot_clauses =
//		num_vertices +
//		binom(num_col, 2) * num_vertices +
//		num_edges * num_col
// for num_col * num_vertices variables.

class ConvertGSMNetworkProblemToSat {


private:
	struct Edge {
		int from;
		int to;
	};

	// Return the index of the boolean variable associated to vertex 'i'
	// and color 'c'. N.B.: boolean variables indexes are one-based.
	int bool_index(int i, int c) {
		return i + c * numVertices;
	}
public:
	int numVertices;
	vector<Edge> edges;

	ConvertGSMNetworkProblemToSat(int n, int m) :
        numVertices(n),
        edges(m)
    {  }

    void printEquisatisfiableSatFormula() {
        SATProblem sat(N_COLORS * numVertices);

    	// Enforce conditions of type 1
    	for (int i = 1; i <= numVertices; ++i) {
    		vector<int> clause(0);
    		for (int c = 0; c < N_COLORS; c++) {
    			clause.push_back(bool_index(i, c));
    		}
    		sat.add_clause(clause);
    	}

    	// Enforce conditions of type 2
    	for (int i = 1; i <= numVertices; ++i) {
    		for (int c = 0; c < N_COLORS; c++) {
    			for (int c1 = c1 + 1; c1 < N_COLORS; c1++)
    				sat.add_clause(
    					{-bool_index(i, c), -bool_index(i, c1)}
    			);
    		}
    	}

    	// Enforce conditions of type 3
    	for (const Edge & edge : edges) {
    		for (int c = 0; c < N_COLORS; c++) {
    			sat.add_clause(
    			{-bool_index(edge.from, c), -bool_index(edge.to, c)}
    			);
    		}
    	}

	sat.print_SAT();
    }

};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertGSMNetworkProblemToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> converter.edges[i].from >> converter.edges[i].to;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}

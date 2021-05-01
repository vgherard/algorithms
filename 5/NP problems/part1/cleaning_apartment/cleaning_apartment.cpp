#include <bits/stdc++.h>
using namespace std;

// We n_vertices ^ 2 boolean variables:
//	x_ij = 'i' is at position 'j' of path
// to which we enforce the constraints:
//
// 1. Each vertex belongs to the path:
//	<x_i1 OR x_i2 OR ... OR x_iV> for all i = 1...V
//
// 2. Each position in the path is occupied by some vertex:
//	<x_1j OR x_2j OR ... OR x_Vj> for all j = 1...V
//
// 3. Each vertex appears just once in a path:
//	<!x_ip OR !x_iq> for all i = 1...V and 1 <= p < q <= V
//
// 4. No two vertices occupy the same position in a path (redundant, but helps
//    the SAT solver):
//	<!x_pj OR !x_qj> for all j = 1...V and 1 <= p < q <= V
//
// 5. Two successive vertices on a path must be connected by an edge:
//	<!x_ij OR !x_i'j+1> if {i, j} is not an edge.

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


struct Edge {
    int from;
    int to;
};

struct ConvertHampathToSat {
    int numVertices;
    unordered_set<string> edges;

    ConvertHampathToSat(int n, int m) :
        numVertices(n),
        edges()
    {  }

    // Return the index of the boolean variable associated to vertex 'i'
    // at position 'j'
    int x(int i, int j) {
    	return i + (j - 1) * numVertices;
    }

    void printEquisatisfiableSatFormula() {
    	SATProblem sat(numVertices * numVertices);

    	// Each vertex belongs to the path
    	for (int i = 1; i <= numVertices; ++i) {
    		vector<int> clause(0);
    		for (int j = 1; j <= numVertices; j++) {
    			clause.push_back(x(i, j));
    		}
    		sat.add_clause(clause);
    	}

    	// Two successive vertices on a path must be connected by an edge
    	for (int j = 1; j <= numVertices; ++j) {
    		vector<int> clause(0);
    		for (int i = 1; i <= numVertices; i++) {
    			clause.push_back(x(i, j));
    		}
    		sat.add_clause(clause);
    	}

    	// Each vertex appears just once in a path
    	for (int i = 1; i <= numVertices; ++i)
    		for (int p = 1; p <= numVertices; ++p)
    			for (int q = p + 1; q <= numVertices; ++q)
    				sat.add_clause({-x(i,p), -x(i,q)});

    	// Each position contains at most one vertex
    	for (int j = 1; j <= numVertices; ++j)
    		for (int p = 1; p <= numVertices; ++p)
    			for (int q = p + 1; q <= numVertices; ++q)
    				sat.add_clause({-x(p,j), -x(q,j)});

	// Two successive vertices on a path must be connected by an edge
	for (int p = 1; p <= numVertices; ++p)
		for (int q = p + 1; q <= numVertices; ++q)
			if(edges.find(to_string(p) + to_string(q)) == edges.end()) {
				for (int j = 1; j <= numVertices - 1; j++) {
					sat.add_clause({-x(p,j), -x(q,j + 1)});
					sat.add_clause({-x(q,j), -x(p,j + 1)});
				}
			}

    	sat.print_SAT();
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    int from, to;
    ConvertHampathToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> from >> to;
    	 converter.edges.insert(to_string(from) + to_string(to));
    	 converter.edges.insert(to_string(to) + to_string(from));
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}

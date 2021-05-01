#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

using std::vector;
const double EPS = 1e-3;
const double INF = 1e10;
typedef std::vector<double> Column;
typedef std::vector<double> Row;
typedef vector<Row> Matrix;

// Return all subsets of size m of the indexes 1:...:n
std::vector<std::vector<size_t> > subsets(size_t n, size_t m) {
	if (m < 1 or n < m) throw;
	std::vector<std::vector<size_t> > res;
	for (size_t i = 0; i < n; ++i) {
		res.push_back(vector<size_t>{i});
	}
	size_t current_size = 1;
	while(current_size < m) {
		std::vector<std::vector<size_t> > tmp;
		for (auto it = res.begin(); it != res.end(); ++it) {
			for (size_t j = (*it).back() + 1; j < n; j++)
			{
				tmp.push_back(*it);
				tmp.back().push_back(j);
			}
		}
		res = tmp;
		current_size++;
	}
	return res;
}

struct GaussErr {};

Column solve(Matrix &a_full, Column &b_full, vector<size_t> subsets) {
	int size = subsets.size();
	Matrix a(size); Column b(size);
	for (size_t i = 0; i < size; ++i) {
		a[i] = a_full[subsets[i]];
		b[i] = b_full[subsets[i]];
	}

	// Forward pass
	for (int step = 0; step < size; ++step) {
		// Find pivot row
		int pivot_row = step;
		while (std::abs(a[pivot_row][step]) < EPS) {
			pivot_row++;
			if (pivot_row == size) throw GaussErr();
		}
		// Swap pivot to row 'step'
		std::swap(a[pivot_row], a[step]);
		std::swap(b[pivot_row], b[step]);

		// Normalize pivot row
		double pivot = a[step][step];
		for (int j = step; j < size; ++j) {
			a[step][j] /= pivot;
		}
		b[step] /= pivot;

		// Reduce other rows
		for (int i = step + 1; i < size; ++i) {
			double mult = a[i][step];
			for (int j = step; j < size; ++j) {
				a[i][j] += -mult * a[step][j];
			}
			b[i] += - mult * b[step];
		}
		// PrintSystem(a, b);
	}

	// Backward pass
	// Forward pass
	for (int step = size - 1; step >= 0; --step) {
		for (int i = step - 1; i >= 0; --i) {
			double mult = a[i][step];
			a[i][step] = 0;
			b[i] += -mult * b[step];
		}
		// PrintSystem(a, b);
	}

	return b;
}


pair<int, vector<double>> solve_diet_problem(
		int n,
		int m,
		Matrix A,
		vector<double> b,
		vector<double> c) {

	std::vector<std::vector<size_t> > subsets_eqs = subsets(n + 1 + m, m);
	bool has_solution = false;
	bool max_at_inf = true;
	double max = 0;
	vector<double> argmax(m, 0);
	for (const auto & subset_eqs : subsets_eqs) {
		vector<double> temp_argmax;
		double temp_max = 0;

		try {
			temp_argmax = solve(A, b, subset_eqs);
		} catch(GaussErr cnd) {
			goto skip;
		}

		for(size_t j = 0; j < m; j++)
			if (temp_argmax[j] < -EPS) goto skip;

		for (size_t i = 0; i < n; ++i) {
			double dot = 0;
			for(size_t j = 0; j < m; j++)
				dot += temp_argmax[j] * A[i][j];
			if (dot > b[i] + EPS)
				goto skip;
		}

		for (size_t j = 0; j < m; ++j)
			temp_max += temp_argmax[j] * c[j];
		if (not has_solution or temp_max > max - EPS) {
			has_solution = true;
			double sum = 0;
			for (size_t i = 0; i < m; ++i)
				sum += temp_argmax[i];
			bool this_max_at_inf = sum > INF / 2;
			if ((not max_at_inf) and this_max_at_inf and max + EPS > temp_max)
				continue;
			max_at_inf = this_max_at_inf;
			max = temp_max;
			argmax = temp_argmax;
		}

		skip:
		continue;
	}
	if (not has_solution)
		return {-1, argmax};

	if (max_at_inf)
		return {1, argmax};

	return {0, argmax};
}

int main(){
	int n, m;
	cin >> n >> m;
	Matrix A(n + m + 1, Row(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> A[i][j];
		}
	}
	for (int j = 0; j < m; j++)
		A[n][j] = 1.;
	for (int i = n + 1; i < n + m + 1; i++)
		A[i][i - n - 1] = 1.;

	Column b(n + m + 1);
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}
	b[n] = INF;

	vector<double> c(m);
	for (int i = 0; i < m; i++) {
		cin >> c[i];
	}

	pair<int, vector<double>> ans = solve_diet_problem(n, m, A, b, c);

	switch (ans.first) {
	case -1:
		printf("No solution\n");
		break;
	case 0:
		printf("Bounded solution\n");
		for (int i = 0; i < m; i++) {
			printf("%.18f%c", ans.second[i], " \n"[i + 1 == m]);
		}
		break;
	case 1:
		printf("Infinity\n");
		break;
	}
	return 0;
}

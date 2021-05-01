#include <cmath>
#include <iostream>
#include <vector>

const double EPS = 1e-6;
const int PRECISION = 20;

typedef std::vector<double> Column;
typedef std::vector<double> Row;
typedef std::vector<Row> Matrix;

void PrintSystem (Matrix & a, Column & b) {
	int size = a.size();
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			std::cout << a[i][j] << " ";
		}
		std::cout << "|" << b[i] << "\n";
	}
	std::cout << "\n";
}

struct Equation {
    Equation(const Matrix &a, const Column &b):
        a(a),
        b(b)
    {}

    Matrix a;
    Column b;
};

struct Position {
    Position(int column, int row):
        column(column),
        row(row)
    {}

    int column;
    int row;
};

Equation ReadEquation() {
    int size;
    std::cin >> size;
    Matrix a(size, std::vector <double> (size, 0.0));
    Column b(size, 0.0);
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column)
            std::cin >> a[row][column];
        std::cin >> b[row];
    }
    return Equation(a, b);
}

Position SelectPivotElement(
  const Matrix &a,
  std::vector <bool> &used_rows,
  std::vector <bool> &used_columns) {
    // This algorithm selects the first free element.
    // You'll need to improve it to pass the problem.
    Position pivot_element(0, 0);
    while (used_rows[pivot_element.row])
        ++pivot_element.row;
    while (used_columns[pivot_element.column])
        ++pivot_element.column;
    return pivot_element;
}

void SwapLines(Matrix &a, Column &b, std::vector <bool> &used_rows, Position &pivot_element) {
    std::swap(a[pivot_element.column], a[pivot_element.row]);
    std::swap(b[pivot_element.column], b[pivot_element.row]);
    std::swap(used_rows[pivot_element.column], used_rows[pivot_element.row]);
    pivot_element.row = pivot_element.column;
}

void ProcessPivotElement(Matrix &a, Column &b, const Position &pivot_element) {
    // Write your code here
}

void MarkPivotElementUsed(const Position &pivot_element, std::vector <bool> &used_rows, std::vector <bool> &used_columns) {
    used_rows[pivot_element.row] = true;
    used_columns[pivot_element.column] = true;
}

Column SolveEquation(Equation equation) {
    Matrix &a = equation.a;
    Column &b = equation.b;
    int size = a.size();

    // Forward pass
    for (int step = 0; step < size; ++step) {
    	// Find pivot row
    	int pivot_row = step;
	while (std::abs(a[pivot_row][step]) < EPS) {
		pivot_row++;
		if (pivot_row == size) throw;
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

void PrintColumn(const Column &column) {
    int size = column.size();
    std::cout.precision(PRECISION);
    for (int row = 0; row < size; ++row)
        std::cout << column[row] << std::endl;
}

int main() {
    Equation equation = ReadEquation();
    Column solution = SolveEquation(equation);
    PrintColumn(solution);
    return 0;
}

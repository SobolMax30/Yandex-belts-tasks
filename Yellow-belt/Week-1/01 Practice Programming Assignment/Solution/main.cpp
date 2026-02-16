#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
private:
    int rows;
    int cols;
    vector<vector<int>> elements;
public:
    Matrix() {
        rows = 0;
        cols = 0;
    }
    Matrix(int num_rows, int num_cols) {
        Reset(num_rows, num_cols);
    }

    void Reset(int num_rows, int num_cols) {
        if (num_rows < 0) {
            throw out_of_range("Number of rows must be >= 0");
        }
        if (num_cols < 0) {
            throw out_of_range("Number of columns must be >= 0");
        }
        if (num_rows == 0 | num_cols == 0) {
            num_rows = 0;
            num_cols = 0;
        }

        rows = num_rows;
        cols = num_cols;
        elements.assign(num_rows, vector<int>(num_cols));
    }
    int At(int row_num, int col_num) const {
        return elements.at(row_num).at(col_num);
    }
    int& At(int row_num, int col_num) {
        return elements.at(row_num).at(col_num);
    }
    int GetNumRows() const {
        return rows;
    }
    int GetNumColumns() const {
        return cols;
    }
};

bool operator == (const Matrix& m1, const Matrix& m2) {
    if (m1.GetNumRows() != m2.GetNumRows()) {
        return false;
    }
    if (m1.GetNumColumns() != m2.GetNumColumns()) {
        return false;
    }

    for (int row = 0; row < m1.GetNumRows(); ++row) {
        for (int col = 0; col < m1.GetNumColumns(); ++col) {
            if (m1.At(row, col) != m2.At(row, col)) {
                return false;
            }
        }
    }

    return true;
}

Matrix operator + (const Matrix& m1, const Matrix& m2) {
    if (m1.GetNumRows() != m2.GetNumRows()) {
        throw invalid_argument("Invalid number of rows");
    }

    if (m1.GetNumColumns() != m2.GetNumColumns()) {
        throw invalid_argument("Invalid number of columns");
    }

    Matrix result(m1.GetNumRows(), m1.GetNumColumns());
    for (int row = 0; row < result.GetNumRows(); ++row) {
        for (int col = 0; col < result.GetNumColumns(); ++col) {
            result.At(row, col) = m1.At(row, col) + m2.At(row, col);
        }
    }

    return result;
}

istream& operator << (istream& in, Matrix& matrix) {
    int num_rows, num_cols;
    in >> num_rows >> num_cols;

    matrix.Reset(num_rows, num_cols);
    for (int row = 0; row < matrix.GetNumRows(); ++row) {
        for (int col = 0; col < matrix.GetNumColumns(); ++col) {
            in >> matrix.At(row, col);
        }
    }

    return in;
}

ostream& operator << (ostream& out, Matrix& matrix) {
    out << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
    for (int row = 0; row < matrix.GetNumRows(); ++row) {
        for (int column = 0; column < matrix.GetNumColumns(); ++column) {
            if (column > 0) {
                out << " ";
            }
            out << matrix.At(row, column);
        }
        out << endl;
    }

    return out;
}

int main() {
    Matrix one;
    Matrix two;

    cin >> one >> two;
    cout << one + two << endl;
    return 0;
}

// https://codeforces.com/gym/102644/problem/A
#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Matrix {
  size_t rows, columns;
  vector<vector<T>> matrix;

  // Initializes a new zero matrix M_{r x c}
  // or square identity matrix I_r if identity=true.
  Matrix(size_t r, size_t c, bool identity = false)
    : rows(r), columns(c), matrix(r, vector<T>(c, T(0))) {
    if (identity) {
      assert(r == c);
      for (int i = 0; i < r; i++) matrix[i][i] = T(1);
    }
  }
  vector<T>& operator[](size_t i) { return matrix[i]; }
  const vector<T>& operator[](size_t i) const { return matrix[i]; }

  // Returns matrix multiplication Q_{r x p} = M_{r x c} * N_{c x p}.
  // Time complexity: O(r*c*p)
  Matrix operator*(const Matrix& other) const {
    assert(columns == other.rows);
    Matrix result(rows, other.columns);
    for (int i = 0; i < rows; i++)
      for (int k = 0; k < columns; k++)
        for (int j = 0; j < other.columns; j++)
          result[i][j] += matrix[i][k] * other[k][j];
    return result;
  }
  // Returns matrix-vector multiplication v'=M*v.
  // Useful for applying transition matrix to recurrence states.
  // Time complexity: O(r*c)
  vector<T> operator*(const vector<T>& v) const {
    assert(columns == v.size());
    vector<T> result(rows, T(0));
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < columns; j++)
        result[i] += matrix[i][j] * v[j];
    return result;
  }
};

// Computes M^n via binary exponentiation.
// Time complexity: O(r^3 lg n)
template <typename T>
Matrix<T> pow(Matrix<T> M, long long n) {
  assert(M.rows == M.columns);
  Matrix<T> result(M.rows, M.rows, true);
  for (; n > 0; n >>= 1, M = M * M)
    if (n & 1) result = result * M;
  return result;
}

int main(void) {
    long long n;
    long double p;
    cin >> n >> p;
    vector base{1.0L, 0.0L};
    Matrix<long double> t(2, 2);
    t[0][0] = t[1][1] = 1.0L - p;
    t[0][1] = t[1][0] = p;
    vector<long double> result = pow(t, n) * base;
    cout << fixed << setprecision(10) << result[0] << endl;
    return 0;
}
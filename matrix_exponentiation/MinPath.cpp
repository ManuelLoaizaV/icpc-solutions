// https://codeforces.com/gym/102644/problem/F
#include <bits/stdc++.h>
using namespace std;

const long long UPPER_BOUND = 1e18;
const long long INF = 2e18;

template <typename T>
struct Matrix {
  size_t rows, columns;
  vector<vector<T>> matrix;

  // Initializes a new zero matrix M_{r x c}
  // or square identity matrix I_r if identity=true.
  Matrix(size_t r, size_t c, bool identity = false)
    : rows(r), columns(c), matrix(r, vector<T>(c, T(INF))) {
    if (identity) {
      assert(r == c);
      for (int i = 0; i < r; i++) matrix[i][i] = T(0);
    }
  }
  vector<T>& operator[](size_t i) { return matrix[i]; }
  const vector<T>& operator[](size_t i) const { return matrix[i]; }

  // Returns matrix multiplication Q_{r x p} = M_{r x c} * N_{c x p}.
  // Time complexity: O(r*c*p).
  Matrix operator*(const Matrix& other) const {
    assert(columns == other.rows);
    Matrix result(rows, other.columns);
    for (int i = 0; i < rows; i++) {
      for (int k = 0; k < columns; k++) {
        for (int j = 0; j < other.columns; j++) {
          result[i][j] = std::min(result[i][j], matrix[i][k] + other[k][j]);
        }
      }
    }

    return result;
  }

  // Computes M^n via binary exponentiation.
  // Time complexity: O(r^3 lg n).
  friend Matrix<T> pow(Matrix<T> M, long long n) {
    assert(M.rows == M.columns);
    Matrix<T> result(M.rows, M.rows, true);
    for (; n > 0; n >>= 1, M = M * M)
      if (n & 1) result = result * M;
    return result;
  }
};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    long long N, M, K;
    cin >> N >> M >> K;
    Matrix<long long> t(N, N, true);
    for (int i = 0; i < N; i++) t[i][i] = INF;

    while (M--) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        u--; v--;
        t[u][v] = std::min(t[u][v], w);
    }

    auto result = pow(t, K);
    long long min_path{INF};
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            min_path = std::min(min_path, result[i][j]);
        }
    }

    if (min_path > UPPER_BOUND) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << min_path << endl;
    }
    return 0;
}
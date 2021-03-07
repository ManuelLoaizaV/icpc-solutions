//https://open.kattis.com/problems/cheeseifyouplease
#include <bits/stdc++.h>
using namespace std;
// Two-phase simplex algorithm for solving linear programs of the form
// Maximize {c^T x} subject to
// A x <= b
// x >= 0
// Input:
// A: m x n matrix
// b: m-dimensional vector
// c: n-dimensional vector
// x: n-dimensional vector where the optimal solution will be stored
// Output:
// Value of the optimal solution.
// Infinity if unbounded above, nan if infeasible.
// Usage:
// LPSolver solver(A, b, c);
// Double value = solver.Solve(x);
typedef long double Double;
const Double EPS = 1e-9;
struct LPSolver {
  int m, n;
  vector<int> B, N;
  vector<vector<Double>> D;
  LPSolver(const vector<vector<Double>>& A, const vector<Double>& b, const vector<Double>& c) :
    m(b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, vector<Double>(n + 2)) {
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) D[i][j] = A[i][j];
    for (int i = 0; i < m; i++) { B[i] = n + i; D[i][n] = -1; D[i][n + 1] = b[i]; }
    for (int j = 0; j < n; j++) { N[j] = j; D[m][j] = -c[j]; }
    N[n] = -1;
    D[m + 1][n] = 1;
  }
  void Pivot(int r, int s) {
    Double inv = 1.0 / D[r][s];
    for (int i = 0; i < m + 2; i++) if (i != r)
      for (int j = 0; j < n + 2; j++) if (j != s)
        D[i][j] -= D[r][j] * D[i][s] * inv;
    for (int j = 0; j < n + 2; j++) if (j != s) D[r][j] *= inv;
    for (int i = 0; i < m + 2; i++) if (i != r) D[i][s] *= -inv;
    D[r][s] = inv;
    swap(B[r], N[s]);
  }
  bool Simplex(int phase) {
    int x = phase == 1 ? m + 1 : m;
    while (true) {
      int s = -1;
      for (int j = 0; j <= n; j++) {
        if (phase == 2 && N[j] == -1) continue;
        if (s == -1 || D[x][j] < D[x][s] || D[x][j] == D[x][s] && N[j] < N[s]) s = j;
      }
      if (D[x][s] > -EPS) return true;
      int r = -1;
      for (int i = 0; i < m; i++) {
        if (D[i][s] < EPS) continue;
        if (r == -1 || D[i][n + 1] / D[i][s] < D[r][n + 1] / D[r][s] ||
          D[i][n + 1] / D[i][s] == D[r][n + 1] / D[r][s] && B[i] < B[r]) r = i;
      }
      if (r == -1) return false;
      Pivot(r, s);
    }
  }
  Double Solve(vector<Double>& x) {
    int r = 0;
    for (int i = 1; i < m; i++) if (D[i][n + 1] < D[r][n + 1]) r = i;
    if (D[r][n + 1] < -EPS) {
      Pivot(r, n);
      if (!Simplex(1) || D[m + 1][n + 1] < -EPS) return -numeric_limits<Double>::infinity();
      for (int i = 0; i < m; i++) if (B[i] == -1) {
        int s = -1;
        for (int j = 0; j <= n; j++)
          if (s == -1 || D[i][j] < D[i][s] || D[i][j] == D[i][s] && N[j] < N[s]) s = j;
        Pivot(i, s);
      }
    }
    if (!Simplex(2)) return numeric_limits<Double>::infinity();
    x = vector<Double>(n);
    for (int i = 0; i < m; i++) if (B[i] < n) x[B[i]] = D[i][n + 1];
    return D[m][n + 1];
  }
};

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int m, n;
  cin >> m >> n;
  vector<vector<Double>> _A(m, vector<Double>(n));
  vector<Double> _b(m);
  vector<Double> _c(n);
  for (int i = 0; i < m; i++) cin >> _b[i];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> _A[j][i];
      _A[j][i] /= (Double) 100;
    }
    cin >> _c[i];
  }
  vector<vector<Double>> A(m);
  vector<Double> b(_b.begin(), _b.end());
  vector<Double> c(_c.begin(), _c.end());
  for (int i = 0; i < m; i++) A[i] = vector<Double>(_A[i].begin(), _A[i].end());
  LPSolver solver(A, b, c);
  vector<Double> x;
  Double value = solver.Solve(x);
  cout << fixed << setprecision(2) << value << '\n';
  return 0;
}
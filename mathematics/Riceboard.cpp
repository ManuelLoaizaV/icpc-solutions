#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef vector<vector<Long>> Matrix;

Long MOD = 1e9 + 7;

Long Add(Long a, Long b) {
  return ((a % MOD) + (b % MOD)) % MOD;
}
Long Sub(Long a, Long b) {
  return ((a % MOD) - (b % MOD) + MOD) % MOD;
}
Long Mul(Long a, Long b) {
  if (a * b < 0) return Sub(0, abs(a * b) % MOD);
  return (a * b) % MOD;
}
Matrix GetMatrix(int n, int m, bool is_identity) {
  Matrix matrix = Matrix(n, vector<Long> (m, 0));
  if (is_identity) {
    assert(n == m);
    for (int i = 0; i < n; i++) matrix[i][i] = 1LL;
  }
  return matrix;
}
Matrix operator + (const Matrix& a, const Matrix& b) {
  Long n = a.size();
  Long m = a[0].size();
  assert(a.size() == b.size());
  assert(a[0].size() == b[0].size());
  Matrix c = GetMatrix(n, m, false);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      c[i][j] = Add(a[i][j], b[i][j]);
  return c;
}
Matrix operator * (const Matrix& a, const Matrix& b) {
  assert(a[0].size() == b.size());
  int n = a.size();
  int m = a[0].size();
  int p = b[0].size();
  Matrix c = GetMatrix(n, p, false);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < p; j++)
      for (int k = 0; k < m; k++)
        c[i][j] = Add(c[i][j], Mul(a[i][k], b[k][j]));
  return c;
}
Matrix FastPow(Matrix a, Long b) {
  assert(a.size() == a[0].size());
  Matrix ans = GetMatrix(a.size(), a.size(), true);
  while (b > 0) {
    if (b & 1) ans = ans * a;
    a = a * a;
    b >>= 1;
  }
  return ans;
}

void Solve(int test_case) {
  Long r, n, m;
  cin >> r >> n >> m;
  MOD = m;
  Long e = n * n - 1;
  Matrix t = GetMatrix(2, 2, true);
  t[0][0] = r % MOD;
  t[1][0] = 1 % MOD;
  Matrix s = GetMatrix(2, 1, false);
  s[0][0] = r % MOD;
  s[1][0] = 1 % MOD;
  Matrix ans = FastPow(t, e) * s;
  printf("Case #%d: %lld\n", test_case, ans[1][0]);
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) Solve(i);
  return 0;
}

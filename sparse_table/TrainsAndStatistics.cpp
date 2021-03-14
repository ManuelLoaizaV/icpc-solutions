//https://codeforces.com/contest/675/problem/E
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> Pair;
typedef long long Long;

const int N = 1e5;
const int LG = 32 - __builtin_clz(N);

struct SparseTable {
  Pair st[N][LG];
  Pair Merge(int x, int i) { return {x, i}; }
  Pair Merge(const Pair& x, const Pair& y) { return max(x, y); }
  void Build(vector<int>& a, int n) {
    for (int i = 0; i < n; i++) st[i][0] = Merge(a[i], i);
    for (int j = 1; j < LG; j++)
      for (int i = 0; i + (1 << j) <= n; i++)
        st[i][j] = Merge(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
  }
  // O(1). Solo funciona con operadores idempotentes.
  Pair Query(int l, int r) {
    int range = r - l + 1;
    int lg = 31 - __builtin_clz(range);
    return Merge(st[l][lg], st[r - (1 << lg) + 1][lg]);
  }
} st;


int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n - 1; i++) {
    cin >> a[i];
    a[i]--;
  }
  a[n - 1] = n - 1;
  st.Build(a, n);
  // DP(i): \sum_{j = i + 1} ^ {n - 1} p(i, j)
  vector<Long> dp(n, 0);
  dp[n - 1] = 0;
  for (int i = n - 2; i >= 0; i--) {
    Pair farthest = st.Query(i + 1, a[i]);
    int nxt = farthest.second;
    dp[i] = (Long) (a[i] - i) + (Long) (n - 1 - a[i]) + dp[nxt] - (Long) (a[i] - nxt);
  }
  Long ans = 0;
  for (int i = 0; i < n; i++) ans += dp[i];
  cout << ans << '\n';
  return 0;
}

//https://www.spoj.com/problems/TNVFC1M/
#include <bits/stdc++.h>

using namespace std;

const int N = 1e4;
const int LG = 32 - __builtin_clz(N);

struct SparseTable {
  pair<int, int> st[N][LG];
  pair<int, int> f(const pair<int, int>& x, const pair<int, int>& y) {
    if (x.first < y.first) return x;
    if (y.first < x.first) return y;
    if (x.second > y.second) return x;
    return y;
  }
  void Build(vector<int>& a, int n) {
    for (int i = 0; i < n; i++) st[i][0] = {a[i], i};
    for (int j = 1; j < LG; j++)
      for (int i = 0; i + (1 << j) <= n; i++)
        st[i][j] = f(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
  }
  // O(1). Solo funciona con operadores idempotentes.
  pair<int, int> Query(int l, int r) {
    int range = r - l + 1;
    int lg = 31 - __builtin_clz(range);
    return f(st[l][lg], st[r - (1 << lg) + 1][lg]);
  }
} st;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, h, e, b;
  while (cin >> n >> h >> e >> b) {
    --e;
    --b;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    st.Build(a, n);
    vector<int> cnt(n, 0);
    for (int i = 0; i < n; i++) {
      int l = max(0, i - h + 1);
      int r = i;
      pair<int, int> mn = st.Query(l, r);
      cnt[mn.second]++;
    }
    for (int i = e; i <= b; i++) {
      if (i > e) cout << " ";
      cout << cnt[i];
    }
    cout << '\n';
  }
  return 0;
}
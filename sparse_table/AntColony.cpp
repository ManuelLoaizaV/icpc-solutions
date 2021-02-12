//https://codeforces.com/problemset/problem/474/F
#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
using namespace std;

const int N = 1e5;
const int LG = 32 - __builtin_clz(N);

struct SparseTable {
  int st[N][LG];
  int f(int x) { return x; }
  int f(int x, int y) { return __gcd(x, y); }
  void Build(vector<int>& a, int n) {
    for (int i = 0; i < n; i++) st[i][0] = f(a[i]);
    for (int j = 1; j < LG; j++)
      for (int i = 0; i + (1 << j) <= n; i++)
        st[i][j] = f(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
  }
  // O(1). Solo funciona con operadores idempotentes.
  int Query(int l, int r) {
    int range = r - l + 1;
    int lg = 31 - __builtin_clz(range);
    return f(st[l][lg], st[r - (1 << lg) + 1][lg]);
  }
} st;


int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  st.Build(a, n);
  map<int, vector<int>> pos;
  for (int i = 0; i < n; i++) pos[a[i]].push_back(i);
  int q;
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    l--;
    r--;
    int g = st.Query(l, r);
    int freed = (pos.count(g) > 0) ? upper_bound(all(pos[g]), r) - lower_bound(all(pos[g]), l) : 0;
    int ans = r - l + 1 - freed;
    cout << ans << '\n';
  }
  return 0;
}

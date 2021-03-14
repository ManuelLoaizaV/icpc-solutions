//https://www.codechef.com/problems/MSTICK
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> Pair;
typedef long double Double;

const int N = 1e5;
const int LG = 32 - __builtin_clz(N);

struct SparseTable {
  Pair st[N][LG];
  Pair f(int x) { return {x, x}; }
  Pair f(const Pair& x, const Pair& y) {
    return {min(x.first, y.first), max(x.second, y.second)};
  }
  void Build(vector<int>& a, int n) {
    for (int i = 0; i < n; i++) st[i][0] = f(a[i]);
    for (int j = 1; j < LG; j++)
      for (int i = 0; i + (1 << j) <= n; i++)
        st[i][j] = f(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
  }
  // O(1). Solo funciona con operadores idempotentes.
  Pair Query(int l, int r) {
    int range = r - l + 1;
    int lg = 31 - __builtin_clz(range);
    return f(st[l][lg], st[r - (1 << lg) + 1][lg]);
  }
} st;


int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  st.Build(a, n);
  int q;
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    Pair p = st.Query(l, r);
    Double ans = p.first + (p.second - p.first) / 2.0;
    if (l > 0) ans = max(ans, (Double) (p.first + st.Query(0, l - 1).second));
    if (r < n - 1) ans = max(ans, (Double) (p.first + st.Query(r + 1, n - 1).second));
    cout << fixed << setprecision(1) << ans << '\n';
  }
  return 0;
}

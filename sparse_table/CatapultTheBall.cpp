//https://www.spoj.com/problems/THRBL/en/
#include <iostream>
#include <vector>
using namespace std;

const int N = 5e4;
const int LG = 32 - __builtin_clz(N);

struct SparseTable {
  int st[N][LG];
  int f(int x) { return x; }
  int f(int x, int y) { return max(x, y); }
  void Build(vector<int>& a, int n) {
    for (int i = 0; i < n; i++) st[i][0] = f(a[i]);
    for (int j = 1; j < LG; j++)
      for (int i = 0; i + (1 << j) <= n; i++)
        st[i][j] = f(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
  }
  int Query(int l, int r) {
    int range = r - l + 1;
    int lg = 31 - __builtin_clz(range);
    return f(st[l][lg], st[r - (1 << lg) + 1][lg]);
  }
} st;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n, m;
  while (cin >> n >> m) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    st.Build(a, n);
    int ans = 0;
    while (m--) {
      int l, r;
      cin >> l >> r;
      l--;
      r--;
      int mx = st.Query(l, r - 1);
      if (mx <= a[l]) ans++;
    }
    cout << ans << '\n';
  }
  return 0;
}

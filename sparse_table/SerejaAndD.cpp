//https://www.codechef.com/problems/SEAD
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
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
  // O(1). Solo funciona con operadores idempotentes.
  int Query(int l, int r) {
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
  vector<int> d(n - 1);
  for (int i = 0; i < n - 1; i++) d[i] = a[i + 1] - a[i];
  st.Build(d, n - 1);
  int m;
  cin >> m;
  while (m--) {
    int t, d;
    cin >> t >> d;
    int k = upper_bound(a.begin(), a.end(), t) - a.begin();
    k--;
    if (k == 0) {
      cout << 1 << '\n';
      continue;
    }
    if (st.Query(0, k - 1) <= d) {
      cout << 1 << '\n';
      continue;
    }
    if (st.Query(k - 1, k - 1) > d) {
      cout << k + 1 << '\n';
      continue;
    }
    int l = 0;
    int r = k - 1;
    while (r - l > 1) {
      int mid = (l + r) / 2;
      if (st.Query(mid, k - 1) <= d) {
        r = mid;
      } else {
        l = mid;
      }
    }
    cout << r + 1 << '\n';
  }
  return 0;
}

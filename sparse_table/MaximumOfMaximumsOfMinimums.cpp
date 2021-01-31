//https://codeforces.com/problemset/problem/872/B
#include <iostream>
#include <vector>
using namespace std;

const int N = 1e5;
const int LG = 32 - __builtin_clz(N);

struct SparseTable {
  int st[N][LG];
  int f(int x) { return x; }
  int f(int x, int y) { return min(x, y); }
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
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  st.Build(a, n);
  if (k == 1) {
    cout << st.Query(0, n - 1) << '\n';
    return 0;
  }
  if (k == 2) {
    int mx = max(a[0], st.Query(1, n - 1));
    for (int i = 1; i < n - 1; i++) mx = max(mx, max(st.Query(0, i), st.Query(i + 1, n - 1)));
    cout << mx << '\n';
    return 0;
  }
  int mx = a[0];
  for (int i = 1; i < n; i++) mx = max(mx, a[i]);
  cout << mx << '\n';
  return 0;
}

//https://codeforces.com/problemset/problem/578/B
#include <iostream>
#include <vector>
using namespace std;

typedef long long Long;

const int N = 2e5 + 2;
const int LG = 32 - __builtin_clz(N);

struct SparseTable {
  int st[N][LG];
  int f(int x) { return x; }
  int f(int x, int y) { return x | y; }
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
  int n, k, x;
  cin >> n >> k >> x;
  vector<int> a(n + 2, 0);
  for (int i = 1; i <= n; i++) cin >> a[i];
  st.Build(a, n + 2);
  Long ans = 0;
  Long mul = 1;
  for (int i = 0; i < k; i++) mul *= x;
  for (int i = 1; i <= n; i++) {
    Long tmp = st.Query(0, i - 1) | (a[i] * mul) | st.Query(i + 1, n + 1);
    ans = max(ans, tmp);
  }
  cout << ans << '\n';
  return 0;
}

//https://codeforces.com/problemset/problem/514/D
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
const int LG = 32 - __builtin_clz(N);

struct SparseTable {
  int st[N][LG];
  int f(int x) { return x; }
  int f(int x, int y) { return max(x, y); }
  void Build(const vector<int>& a, int n) {
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
};

vector<SparseTable> st;

bool Check(int len, int n, int m, int k, vector<int>& ans) {
  for (int i = 0; i < n - len + 1; i++) {
    int sum = 0;
    for (int j = 0; j < m; j++) {
      ans[j] = st[j].Query(i, i + len - 1);
      sum += ans[j];
    }
    if (sum <= k) return true;
  }
  return false;
}

void Print(const vector<int>& ans) {
  int n = (int) ans.size();
  for (int i = 0; i < n; i++) {
    if (i > 0) cout << " ";
    cout << ans[i];
  }
  cout << '\n';
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<int>> a(m, vector<int>(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m ; j++)
      cin >> a[j][i];
  st.resize(m);
  for (int i = 0; i < m; i++) st[i].Build(a[i], n);
  vector<int> ans(m, 0);
  int l = 0;
  int r = n;
  if (Check(n, n, m, k, ans)) {
    Print(ans);
    return 0;
  }
  while (r - l > 1) {
    int mid = (l + r) / 2;
    if (Check(mid, n, m, k, ans)) {
      l = mid;
    } else {
      r = mid;
    }
  }
  if (l == 0) {
    ans = vector<int>(m, 0);
  } else {
    Check(l, n, m, k, ans);
  }
  Print(ans);
  return 0;
}

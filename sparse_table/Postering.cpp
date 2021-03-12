//https://www.spoj.com/problems/POSTERIN/en/
#include <bits/stdc++.h>
using namespace std;

const int N = 250000;
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
  // O(1). Solo funciona con operadores idempotentes.
  int Query(int l, int r) {
    int range = r - l + 1;
    int lg = 31 - __builtin_clz(range);
    return f(st[l][lg], st[r - (1 << lg) + 1][lg]);
  }
} st;

int Compress(vector<int>& a) {
  int n = a.size();
  vector<pair<int, int>> pairs;
  for (int i = 0; i < n; i++) pairs.push_back({a[i], i});
  sort(pairs.begin(), pairs.end());
  int nxt = 0;
  for (int i = 0; i < n; i++) {
    if (i > 0 && pairs[i].first != pairs[i - 1].first) nxt++;
    a[pairs[i].second] = nxt;
  }
  return nxt + 1;
}

vector<vector<int>> pos;

int Solve(int l, int r) {
  if (l > r) return 0;
  int ans = 1;
  int mn = st.Query(l, r);
  int left = lower_bound(pos[mn].begin(), pos[mn].end(), l) - pos[mn].begin();
  int right = upper_bound(pos[mn].begin(), pos[mn].end(), r) - pos[mn].begin();
  right--;
  ans += Solve(l, pos[mn][left] - 1);
  for (int i = left; i < right; i++) ans += Solve(pos[mn][i] + 1, pos[mn][i + 1] - 1);
  ans += Solve(pos[mn][right] + 1, r);
  return ans;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) for (int j = 0; j < 2; j++) cin >> a[i];
  pos = vector<vector<int>>(Compress(a));
  for (int i = 0; i < n; i++) pos[a[i]].push_back(i);
  st.Build(a, n);
  cout << Solve(0, n - 1) << '\n';
  return 0;
}

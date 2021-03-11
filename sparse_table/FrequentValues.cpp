//https://www.spoj.com/problems/FREQUENT/
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 1;
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

int Compress(vector<int>& a) {
  int n = a.size();
  vector<pair<int, int>> pairs;
  for (int i = 0; i < n; i++) pairs.emplace_back(a[i], i);
  sort(pairs.begin(), pairs.end());
  int nxt = 0;
  for (int i = 0; i < n; i++) {
    if (i > 0 && pairs[i].first != pairs[i - 1].first) nxt++;
    a[pairs[i].second] = nxt;
  }
  return nxt + 1;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, q;
  while (cin >> n) {
    if (n == 0) break;
    cin >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int sz = Compress(a);
    vector<int> pos[sz];
    for (int i = 0; i < n; i++) pos[a[i]].push_back(i);
    vector<int> cnt(sz, 0);
    for (int i = 0; i < n; i++) cnt[a[i]]++;
    st.Build(cnt, sz);
    while (q--) {
      int l, r;
      cin >> l >> r;
      --l;
      --r;
      int ans = 0;
      if (a[l] == a[r]) {
        ans = r - l + 1;
      } else {
        if (a[l] + 1 != a[r]) ans = st.Query(a[l] + 1, a[r] - 1);
        int left = min(r, pos[a[l]].end()[-1]) - l + 1;
        int right = r - max(l, pos[a[r]][0]) + 1;
        ans = max(ans, max(left, right));
      }
      cout << ans << '\n';
    }
  }
  return 0;
}
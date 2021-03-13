//https://codeforces.com/problemset/problem/863/E
#include <bits/stdc++.h>
using namespace std;

const int N = 6e5 + 1;
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


int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<pair<int, int>> pairs(n);
  set<int> uni;
  for (int i = 0; i < n; i++) {
    cin >> pairs[i].first >> pairs[i].second;
    uni.insert(pairs[i].first - 1);
    uni.insert(pairs[i].first);
    uni.insert(pairs[i].second);
  }
  int sz = 0;
  map<int, int> h;
  for (int pucp : uni) h[pucp] = sz++;
  for (int i = 0; i < n; i++) {
    pairs[i].first = h[pairs[i].first];
    pairs[i].second = h[pairs[i].second];
  }
  sz++;
  vector<int> acc(sz, 0);
  for (int i = 0; i < n; i++) {
    acc[pairs[i].first]++;
    acc[pairs[i].second + 1]--;
  }
  for (int i = 1; i < sz; i++) {
    acc[i] += acc[i - 1];
  }
  st.Build(acc, sz);
  for (int i = 0; i < n; i++) {
    int mn = st.Query(pairs[i].first, pairs[i].second);
    if (mn == 1) continue;
    cout << i + 1 << '\n';
    return 0;
  }
  cout << -1 << '\n';
  return 0;
}

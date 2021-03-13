//https://www.spoj.com/problems/DIFERENC/
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> Pair;
typedef long long Long;

const int N = 3e5;
const int LG = 32 - __builtin_clz(N);

struct SparseTable {
  pair<Pair, Pair> st[N][LG];
  pair<Pair, Pair> f(int x, int i) {
    return {{x, i}, {x, i}};
  }
  pair<Pair, Pair> f(const pair<Pair, Pair>& x, const pair<Pair, Pair>& y) {
    return {min(x.first, y.first), max(x.second, y.second)};
  }
  void Build(vector<int>& a, int n) {
    for (int i = 0; i < n; i++) st[i][0] = f(a[i], i);
    for (int j = 1; j < LG; j++)
      for (int i = 0; i + (1 << j) <= n; i++)
        st[i][j] = f(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
  }
  // O(1). Solo funciona con operadores idempotentes.
  Pair GetMin(int l, int r) {
    int range = r - l + 1;
    int lg = 31 - __builtin_clz(range);
    return f(st[l][lg], st[r - (1 << lg) + 1][lg]).first;
  }
  Pair GetMax(int l, int r) {
    int range = r - l + 1;
    int lg = 31 - __builtin_clz(range);
    return f(st[l][lg], st[r - (1 << lg) + 1][lg]).second;
  }
} st;

Long GetMaxSum(int l, int r) {
  if (l > r) return 0;
  Pair mx = st.GetMax(l, r);
  Long pos = (Long) mx.second;
  Long left = pos - l + 1;
  Long right = r - pos + 1;
  return mx.first * left * right + GetMaxSum(l, pos - 1) + GetMaxSum(pos + 1, r);
}

Long GetMinSum(int l, int r) {
  if (l > r) return 0;
  Pair mn = st.GetMin(l, r);
  Long pos = (Long) mn.second;
  Long left = pos - l + 1;
  Long right = r - pos + 1;
  return mn.first * left * right + GetMinSum(l, pos - 1) + GetMinSum(pos + 1, r);
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  st.Build(a, n);
  Long ans = GetMaxSum(0, n - 1) - GetMinSum(0, n - 1);
  cout << ans << '\n';
  return 0;
}

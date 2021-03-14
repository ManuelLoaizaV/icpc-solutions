//https://codeforces.com/problemset/problem/5/C
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

int GetChar(char c) {
  return ((c == '(') ? 1 : -1);
}

const int N = 1e6;
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

int GetMin(int l, int r, int pref) {
  return st.Query(l, r) - pref;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  int n = (int) s.size();
  vector<int> acc(n, 0);
  acc[0] = GetChar(s[0]);
  for (int i = 1; i < n; i++) acc[i] = acc[i - 1] + GetChar(s[i]);
  st.Build(acc, n);
  int mx = 0;
  int cnt = 1;
  for (int i = 0; i < n; i++) {
    int pref = (i == 0) ? 0 : acc[i - 1];
    if (GetMin(i, i, pref) < 0) continue;
    int last;
    if (GetMin(i, n - 1, pref) >= 0) {
      last = n - 1;
    } else {
      int l = i;
      int r = n - 1;
      while (r - l > 1) {
        int m = (l + r) / 2;
        if (GetMin(i, m, pref) >= 0) {
          l = m;
        } else {
          r = m;
        }
      }
      last = l;
    }
    int l = i;
    int r = last;
    if (GetMin(l, last, pref) > 0) continue;
    int len;
    if (GetMin(r, last, pref) == 0) {
      len = r - i + 1;
    } else {
      while (r - l > 1) {
        int m = (l + r) / 2;
        if (GetMin(m, last, pref) == 0) {
          l = m;
        } else {
          r = m;
        }
      }
      len = l - i + 1;
    }
    if (len > mx) {
      mx = len;
      cnt = 1;
    } else if (len == mx) {
      cnt++;
    }
  }
  cout << mx << " " << cnt << '\n';
  return 0;
}

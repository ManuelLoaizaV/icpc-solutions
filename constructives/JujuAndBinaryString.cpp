// https://codeforces.com/contest/1658/problem/F
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

void PrintRange(int l, int r) {
  cout << l << " " << r << '\n';
}

void Solve(void) {
  Long n, m;
  cin >> n >> m;
  string s;
  cin >> s;
  vector<int> cnt(2 * n + 1, 0);
  for (int i = 1; i <= 2 * n; i++) {
    cnt[i] = cnt[i - 1];
    int j = (i - 1) % n;
    if (s[j] == '1') {
      cnt[i]++;
    }
  }
  if (cnt[n] * m % n != 0) {
    cout << -1 << '\n';
    return;
  }
  Long ones = cnt[n] * m / n;
  for (int i = m; i <= n; i++) {
    if (cnt[i] - cnt[i - m] == ones) {
      cout << 1 << '\n';
      int l = i - m + 1;
      int r = i;
      PrintRange(l, r);
      return;
    }
  }
  for (int i = n + 1; i <= 2 * n; i++) {
    if (cnt[i] - cnt[i - m] == ones) {
      cout << 2 << '\n';
      int l = i - m + 1;
      int r = i;
      PrintRange(1, r - n);
      PrintRange(l, n);
      return;
    }
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}

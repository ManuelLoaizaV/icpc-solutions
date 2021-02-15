//https://codeforces.com/problemset/problem/1234/D
#include <bits/stdc++.h>
using namespace std;

const int A = 26;
const int N = 1e5;

struct FenwickTree {
  int tree[N + 1];
  void Update(int i, int delta) {
    while (i <= N) {
      tree[i] += delta;
      i += (i & -i);
    }
  }
  int Query(int i) {
    int sum = 0;
    while (i > 0) {
      sum += tree[i];
      i -= (i & -i);
    }
    return sum;
  }
} ft[A];

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  string s;
  cin >> s;
  int q;
  cin >> q;
  for (int i = 0; i < s.size(); i++) ft[s[i] - 'a'].Update(i + 1, 1);
  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int pos;
      char c;
      cin >> pos >> c;
      ft[s[pos - 1] - 'a'].Update(pos, -1);
      ft[c - 'a'].Update(pos, 1);
      s[pos - 1] = c;
    } else {
      int l, r;
      cin >> l >> r;
      int ans = 0;
      for (int i = 0; i < A; i++) if (ft[i].Query(r) - ft[i].Query(l - 1) > 0) ans++;
      cout << ans << '\n';
    }
  }
  return 0;
}

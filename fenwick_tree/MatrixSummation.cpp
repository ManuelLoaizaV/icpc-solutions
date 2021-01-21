//https://www.spoj.com/problems/MATSUM/en/
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 1025;

struct FenwickTree {
  Long tree[N + 1][N + 1];

  void Build(int n) {
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= n; j++) {
        tree[i][j] = 0;
      }
    }
  }

  void Update(int i, int y, Long delta) {
    while (i <= N) {
      int j = y;
      while (j <= N) {
        tree[i][j] += delta;
        j += (j & -j);
      }
      i += (i & -i);
    }
  }

  Long Query(int i, int y) {
    Long ans = 0;
    while (i > 0) {
      int j = y;
      while (j > 0) {
        ans += tree[i][j];
        j -= (j & -j);
      }
      i -= (i & -i);
    }
    return ans;
  }

  Long GetSum(int i, int j, int x, int y) {
    return Query(x, y) - Query(x, j - 1) - Query(i - 1, y) + Query(i - 1, j - 1);
  }
} ft;

void Solve(void) {
  Long n;
  cin >> n;
  string s;
  ft.Build(n);
  while (true) {
    cin >> s;
    if (s[0] == 'E') break;
    if (s[1] == 'E') {
      int x, y;
      Long num;
      cin >> x >> y >> num;
      Long delta = num - ft.GetSum(x + 1, y + 1, x + 1, y + 1);
      ft.Update(x + 1, y + 1, delta);
    } else {
      int i, j, x, y;
      cin >> i >> j >> x >> y;
      cout << ft.GetSum(i + 1, j + 1, x + 1, y + 1) << '\n';
    }
  }
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}

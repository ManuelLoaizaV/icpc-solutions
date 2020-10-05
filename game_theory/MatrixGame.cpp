#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(0)
using namespace std;

const int N = 50;

int a[N][N];

void Solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> a[i][j];
  int ans = 0;
  for (int row = 0; row < n; row++) {
    int cur = 0;
    for (int col = m - 1; col >= 0; col--) {
      if (col == m - 1) {
        cur = a[row][col];
      } else {
        if (cur == 0) {
          cur = a[row][col];
        } else {
          if (a[row][col] <= cur) cur = a[row][col] - 1;
          else cur = a[row][col];
        }
      }
    }
    ans ^= cur;
  }
  if (ans) cout << "FIRST" << '\n';
  else cout << "SECOND" << '\n';
}

int main() {
  FAST_IO;
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}

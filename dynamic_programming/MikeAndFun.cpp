#include <iostream>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

const int N = 5e2;
bool bears[N][N];
int dp[N];

int Calculate(int row, int m) {
  int ans = 0;
  int cur = 1;
  for (int col = 1; col < m; col++) {
    if (bears[row][col] == bears[row][col - 1]) {
      cur++;
    } else {
      if (bears[row][col - 1]) ans = max(ans, cur);
      cur = 1;
    }
  }
  if (bears[row][m - 1]) ans = max(ans, cur);
  return ans;
}

int main(void) {
  FAST_IO;
  int n, m, q;
  cin >> n >> m >> q;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> bears[i][j];
    }
  }
  for (int i = 0; i < n; i++) dp[i] = Calculate(i, m);
  while (q--) {
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    bears[x][y] = !bears[x][y];
    dp[x] = Calculate(x, m);
    int ans = 0;
    for (int i = 0; i < n; i++) ans = max(ans, dp[i]);
    cout << ans << '\n';
  }
  return 0;
}

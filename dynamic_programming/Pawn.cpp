//https://codeforces.com/problemset/problem/41/D
#include <iostream>
using namespace std;

const int N = 100;
const int K = 11;
const int INF = 1e3;

string square[N];
bool is_done[N][N][K];
int dp[N][N][K];
int n, m, k;

// DP(i, j, r): maxima suma comenzando en la casilla (i, j)
// habiendo llegado con un residuo r
int DP(int i, int j, int r) {
  if (i < 0) return (r == 0) ? 0 : -INF;
  if (is_done[i][j][r]) return dp[i][j][r];
  dp[i][j][r] = -INF;
  int value = square[i][j] - '0';
  int new_r = (r + value) % k;
  for (int dx = -1; dx <= 1; dx += 2) {
    int new_j = j + dx;
    if ((0 <= new_j) && (new_j < m)) dp[i][j][r] = max(dp[i][j][r], value + DP(i - 1, new_j, new_r));
  }
  is_done[i][j][r] = true;
  return dp[i][j][r];
}

void Reconstruct(int i, int j, int r) {
  if (i == 0) return;
  int value = square[i][j] - '0';
  int new_r = (r + value) % k;
  for (int dx = -1; dx <= 1; dx += 2) {
    int new_j = j + dx;
    if ((0 <= new_j) && (new_j < m)) {
      if (DP(i, j, r) == value + DP(i - 1, new_j, new_r)) {
        char chr = (dx == -1) ? 'L' : 'R';
        cout << chr;
        Reconstruct(i - 1, new_j, new_r);
        return;
      }
    }
  }
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  cin >> n >> m >> k;
  k++;
  for (int i = 0; i < n; i++) cin >> square[i];
  int mx = -INF;
  for (int i = 0; i < m; i++) mx = max(mx, DP(n - 1, i, 0));
  if (mx < 0) {
    cout << -1 << '\n';
  } else {
    cout << mx << '\n';
    for (int i = 0; i < m; i++) {
      if (mx == DP(n - 1, i, 0)) {
        cout << i + 1 << '\n';
        Reconstruct(n - 1, i, 0);
        cout << '\n';
        break;
      }
    }
  }
  return 0;
}

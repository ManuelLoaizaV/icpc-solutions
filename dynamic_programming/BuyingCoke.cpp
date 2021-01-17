//https://open.kattis.com/problems/coke
#include <iostream>
using namespace std;

const int C = 150;
const int N_5 = 250;
const int N_10 = 50;
const int INF = 1e4;

int c, n[3];
bool is_done[C + 1][N_5 + 1][N_10 + 1];
int dp[C + 1][N_5 + 1][N_10 + 1];

void Initialize(void) {
  for (int i = 0; i <= c; i++) {
    for (int j = 0; j <= N_5; j++) {
      for (int k = 0; k <= n[2]; k++) {
        is_done[i][j][k] = false;
      }
    }
  }
}

int DP(int cokes, int n_5, int n_10) {
  if (cokes == 0) return 0;
  if (is_done[cokes][n_5][n_10]) return dp[cokes][n_5][n_10];
  int n_1 = n[0] + 5 * (n[1] - n_5) + 10 * (n[2] - n_10) + 8 * (cokes - c);
  dp[cokes][n_5][n_10] = INF;
  if (n_1 >= 8) dp[cokes][n_5][n_10] = min(dp[cokes][n_5][n_10], 8 + DP(cokes - 1, n_5, n_10));
  if (n_1 >= 3 && n_5 >= 1) dp[cokes][n_5][n_10] = min(dp[cokes][n_5][n_10], 4 + DP(cokes - 1, n_5 - 1, n_10));
  if (n_5 >= 2) dp[cokes][n_5][n_10] = min(dp[cokes][n_5][n_10], 2 + DP(cokes - 1, n_5 - 2, n_10));
  if (n_10 >= 1) dp[cokes][n_5][n_10] = min(dp[cokes][n_5][n_10], 1 + DP(cokes - 1, n_5, n_10 - 1));
  if (n_1 >= 3 & n_10 >= 1) dp[cokes][n_5][n_10] = min(dp[cokes][n_5][n_10], 4 + DP(cokes - 1, n_5 + 1, n_10 - 1));
  is_done[cokes][n_5][n_10] = true;
  return dp[cokes][n_5][n_10];
}

void Solve(void) {
  cin >> c;
  for (int i = 0; i < 3; i++) cin >> n[i];
  Initialize();
  cout << DP(c, n[1], n[2]) << '\n';
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}

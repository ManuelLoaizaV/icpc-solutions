//https://www.spoj.com/problems/ABA12C/
#include <iostream>
using namespace std;

const int INF = 1e6;
const int N = 102;

int price[N], dp[N][N][N];
bool is_done[N][N][N];

// DP(i, r, t): minimo costo para conseguir exactamente t de peso con los productos
// [0 .. i] y a lo mas r productos por utilizar.
int DP(int i, int rem, int tar) {
  if (tar == 0) return 0;
  if (rem == 0) return INF;
  if (i < 0) return INF;
  if (is_done[i][rem][tar]) return dp[i][rem][tar];
  dp[i][rem][tar] = DP(i - 1, rem, tar);
  if (price[i] != -1 && (i + 1 <= tar)) {
    dp[i][rem][tar] = min(dp[i][rem][tar], price[i] + DP(i - 1, rem - 1, tar - i - 1));
    dp[i][rem][tar] = min(dp[i][rem][tar], price[i] + DP(i, rem - 1, tar - i - 1));
  }
  is_done[i][rem][tar];
  return dp[i][rem][tar];
}

void Solve(void) {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i <= k; i++)
    for (int j = 0; j <= n; j++)
      for (int l = 0; l <= k; l++)
        is_done[i][j][l] = false;
  for (int i = 0; i < k; i++) cin >> price[i];
  if (DP(k - 1, n, k) < INF) {
    cout << DP(k - 1, n, k) << '\n';
  } else {
    cout << -1 << '\n';
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

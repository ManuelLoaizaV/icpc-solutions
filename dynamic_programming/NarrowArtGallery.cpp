#include <iostream>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;

const Long N = 205;
const Long INF = 1e6;

Long v[N][2];

bool is_done[N][N][3];
Long dp[N][N][3];

Long DP(int pos, int rem, int pre) {
  if (rem == 0) return 0;
  if (pos < 0) return INF;
  if (is_done[pos][rem][pre]) return dp[pos][rem][pre];
  dp[pos][rem][pre] = DP(pos - 1, rem, 2);
  if (pre < 2) dp[pos][rem][pre] = min(dp[pos][rem][pre], v[pos][pre] + DP(pos - 1, rem - 1, pre));
  if (pre == 2) for (int i = 0; i < 2; i++) dp[pos][rem][pre] = min(dp[pos][rem][pre], v[pos][i] + DP(pos - 1, rem - 1, i));
  is_done[pos][rem][pre] = true;
  return dp[pos][rem][pre];
}

void Solve(int n, int k) {
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= n; j++)
      for (int l = 0; l < 3; l++)
        is_done[i][j][l] = false;
  Long sum = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 2; j++) {
      cin >> v[i][j];
      sum += v[i][j];
    }
  }
  Long ans = sum - DP(n - 1, k, 2);
  cout << ans << '\n';
}

int main(void) {
  FAST_IO;
  int n, k;
  while (cin >> n >> k) {
    if (n == 0 && k == 0) break;
    Solve(n, k);
  }
  return 0;
}

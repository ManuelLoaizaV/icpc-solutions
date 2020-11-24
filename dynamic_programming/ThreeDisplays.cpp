#include <iostream>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

const int N = 3e3 + 5;
const int INF = 1e9;

int s[N], c[N], n;
int dp[N][N][3];
bool is_done[N][N][3];

int DP(int pos, int prev, int rem) {
  if (rem == 0) return 0;
  if (pos == n) return INF;
  if (is_done[pos][prev][rem]) return dp[pos][prev][rem];
  dp[pos][prev][rem] = DP(pos + 1, prev, rem);
  if (rem == 3 || (rem < 3 && s[prev] < s[pos]))
    dp[pos][prev][rem] = min(dp[pos][prev][rem], c[pos] + DP(pos + 1, pos, rem - 1));
  is_done[pos][prev][rem] = true;
  return dp[pos][prev][rem];
}

int main(void) {
  FAST_IO;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> s[i];
  for (int i = 0; i < n; i++) cin >> c[i];
  int ans = DP(0, 0, 3);
  if (ans == INF) {
    cout << -1 << '\n';
  } else {
    cout << ans << '\n';
  }
  return 0;
}

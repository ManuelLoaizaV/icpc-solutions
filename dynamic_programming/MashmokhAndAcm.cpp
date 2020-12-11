#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;

const Long MOD = 1e9 + 7;
const int N = 2e3 + 5;

int n, k;
bool is_done[N][N];
Long dp[N][N];

Long Sum(Long a, Long b) {
  return (a + b) % MOD;
}

Long DP(int pos, int prev) {
  if (pos == k) return 1LL;
  if (is_done[pos][prev]) return dp[pos][prev];
  dp[pos][prev] = 0LL;
  int x = 1;
  while (prev * x <= n) {
    dp[pos][prev] = Sum(dp[pos][prev], DP(pos + 1, x * prev));
    x++;
  }
  is_done[pos][prev] = true;
  return dp[pos][prev];
}

int main(void) {
  FAST_IO;
  cin >> n >> k;
  Long ans = 0;
  for (int i = 1; i <= n; i++) ans = Sum(ans, DP(1, i));
  cout << ans << '\n';
  return 0;
}

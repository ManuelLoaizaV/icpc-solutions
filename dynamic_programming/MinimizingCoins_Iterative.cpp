// https://cses.fi/problemset/task/1634/
#include <bits/stdc++.h>
using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, x;
  cin >> n >> x;
  vector<int> coins(n);
  for (int i = 0; i < n; i++) {
    cin >> coins[i];
  }
  sort(coins.begin(), coins.end());
  vector<int> dp(x + 1, x + 1);
  dp[0] = 0;
  for (int i = 1; i <= x; i++) {
    for (int j = 0; j < n; j++) {
      int y = i - coins[j];
      if (y < 0) break;
      dp[i] = min(dp[i], 1 + dp[y]);
    }
  }
  if (dp[x] <= x) {
    cout << dp[x] << endl;
  } else {
    cout << -1 << endl;
  }
  return 0;
}

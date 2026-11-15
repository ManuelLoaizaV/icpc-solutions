// https://cses.fi/problemset/task/1634/
#include <bits/stdc++.h>
using namespace std;

const int N = 100;
const int X = 1000000;

int n;
int coins[N];
int dp[X + 1];
bool done[X + 1];

int DP(int x) {
  if (x == 0) return 0;
  if (done[x]) return dp[x];
  dp[x] = X + 1;
  for (int i = 0; i < n; i++) {
    int y = x - coins[i];
    if (y < 0) break;
    dp[x] = min(dp[x], 1 + DP(y));
  }
  done[x] = true;
  return dp[x];
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int x;
  cin >> n >> x;
  for (int i = 0; i < n; i++) {
    cin >> coins[i];
  }
  sort(coins, coins + n);
  if (DP(x) <= x) {
    cout << DP(x) << endl;
  } else {
    cout << -1 << endl;
  }
  return 0;
}

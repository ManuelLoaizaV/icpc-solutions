// https://atcoder.jp/contests/dp/tasks/dp_e
#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#define debug(x) cerr << "[" << #x << "]: " << x << endl
#else
#define debug(x) 69
#endif

using namespace std;

typedef long long Long;
typedef long double Double;
typedef pair<Long, Long> Pair;

const int N = 1e6;
const Long MOD = 998244353LL;
const int INF = 1e9 + 5;
const Double PI = acos(-1);
const Double EPS = 1e-9;

const char A = 'a';
const char ZERO = '0';
const char ENDL = '\n';

const string YES = "YES";
const string NO = "NO";

void Solve(void) {
  int n;
  int W;
  cin >> n >> W;
  vector<int> weights(n), values(n);

  int total_value = 0;
  for (int i = 0; i < n; i++) {
    cin >> weights[i] >> values[i];
    total_value += values[i];
  }

  // dp(i, v) = min weight using elements in [i, n) to achieve capacity v
  vector<vector<int>> dp(n + 1, vector<int>(total_value + 1));

  // Base cases
  for (int i = 0; i <= n; i++) dp[i][0] = 0;
  for (int v = 1; v <= total_value; v++) dp[n][v] = INF;

  // Topo order
  for (int i = n - 1; i >= 0; i--) {
    for (int v = 1; v <= total_value; v++) {
      int rem = v - values[i];
      dp[i][v] = dp[i + 1][v];
      if (rem >= 0) dp[i][v] = min(dp[i][v], weights[i] + dp[i + 1][rem]);
    }
  }

  // Original
  for (int v = total_value; v >= 0; v--) {
    if (dp[0][v] <= W) {
      cout << v << ENDL;
      return;
    }
  }
}
int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  // cin >> t;
  while (t--) Solve();
  return 0;
}

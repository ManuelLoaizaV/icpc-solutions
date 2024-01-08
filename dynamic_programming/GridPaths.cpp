// https://cses.fi/problemset/task/1638
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
const Long MOD = 1e9 + 7;
const Long INF = 1e18;
const Double PI = acos(-1);
const Double EPS = 1e-9;

const char A = 'a';
const char ZERO = '0';
const char ENDL = '\n';
const char OBSTACLE = '*';

const string YES = "YES";
const string NO = "NO";

void Solve(void) {
  int n;
  cin >> n;
  vector<string> g(n);
  for (int i = 0; i < n; i++) cin >> g[i];

  vector<vector<Long>> dp(n, vector<Long>(n, 0LL));
  dp[0][0] = (g[0][0] != OBSTACLE);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == 0 && j == 0) continue;
      if (g[i][j] == OBSTACLE) continue;
      if (j > 0) dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
      if (i > 0) dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
    }
  }
  cout << dp[n - 1][n - 1] << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  // cin >> t;
  while (t--) Solve();
  return 0;
}

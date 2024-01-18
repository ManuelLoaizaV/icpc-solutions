// https://codeforces.com/problemset/problem/1132/F
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
const Long INF = 1e18;
const Double PI = acos(-1);
const Double EPS = 1e-9;

const char A = 'a';
const char ZERO = '0';
const char ENDL = '\n';

const string YES = "YES";
const string NO = "NO";

void Solve(void) {
  int n;
  cin >> n;
  string s;
  cin >> s;
  // dp(i, j) = min number of operations to delete s[i..j]
  vector<vector<int>> dp(n, vector<int>(n));
  // Topo order: Increasing length of substring
  for (int i = 0; i < n; i++) dp[i][i] = 1;
  for (int len = 2; len <= n; len++) {
    for (int i = 0; i + len - 1 < n; i++) {
      int j = i + len - 1;
      dp[i][j] = 1 + dp[i + 1][j];
      for (int k = i + 1; k <= j; k++) {
        if (s[k] != s[i]) continue;
        int tmp = dp[k][j];
        if (i + 1 <= k - 1) tmp += dp[i + 1][k - 1];
        dp[i][j] = min(dp[i][j], tmp);
      }
    }
  }
  cout << dp[0][n - 1] << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  // cin >> t;
  while (t--) Solve();
  return 0;
}

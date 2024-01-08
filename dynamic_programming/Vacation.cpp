// https://atcoder.jp/contests/dp/tasks/dp_c
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
  vector<vector<int>> v(n, vector<int>(3));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 3; j++) {
       cin >> v[i][j];
    }
  }

  // dp(i, j): max happiness starting at day i doing activity j
  vector<vector<int>> dp(n, vector<int>(3, 0));
  // Base cases: Last day depends on the choice of that day
  for (int j = 0; j < 3; j++) {
    dp[n - 1][j] = v[n - 1][j];
  }

  for (int i = n - 2; i >= 0; i--) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        if (k == j) continue;
        dp[i][j] = max(dp[i][j], v[i][j] + dp[i + 1][k]);
      }
    }
  }

  int max_happiness = 0;
  for (int j = 0; j < 3; j++) {
    max_happiness = max(max_happiness, dp[0][j]);
  }
  cout << max_happiness << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  // cin >> t;
  while (t--) Solve();
  return 0;
}

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
const int INF = 1e5;
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
  vector<int> lenghts(3);
  for (int i = 0; i < 3; i++) {
    cin >> lenghts[i];
  }
  vector<int> dp(n + 1, -INF);
  dp[0] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 3; j++) {
      int rem = i - lenghts[j];
      if (rem >= 0) {
        dp[i] = max(dp[i], 1 + dp[rem]);
      }
    }
  }
  cout << dp[n] << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  // cin >> t;
  while (t--) Solve();
  return 0;
}

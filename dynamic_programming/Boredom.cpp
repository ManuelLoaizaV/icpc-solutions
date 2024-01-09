// https://codeforces.com/contest/455/problem/A
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

const int N = 1e5;
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
  vector<Long> cnt(N + 1, 0LL);
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    cnt[x]++;
  }

  // dp(i) = max points with values >= i
  vector<Long> dp(N + 3);
  dp[N + 1] = dp[N + 2] = 0LL;
  for (Long i = N; i >= 1; i--) {
    dp[i] = max(dp[i + 1], cnt[i] * i + dp[i + 2]);
  }

  cout << dp[1] << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  // cin >> t;
  while (t--) Solve();
  return 0;
}

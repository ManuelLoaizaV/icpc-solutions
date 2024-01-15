// https://atcoder.jp/contests/dp/tasks/dp_f
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

const int N = 3e3;
const Long MOD = 998244353LL;
const Long INF = 1e18;
const Double PI = acos(-1);
const Double EPS = 1e-9;

const char A = 'a';
const char ZERO = '0';
const char ENDL = '\n';

const string YES = "YES";
const string NO = "NO";

string s, t;
bool done[N][N];
int dp[N][N];

// dp(i, j) = lcs(s[i, n), t[j, m))
int DP(int i, int j) {
  if (i == (int)s.size()) return 0;
  if (j == (int)t.size()) return 0;
  if (done[i][j]) return dp[i][j];
  dp[i][j] = max(DP(i + 1, j), DP(i, j + 1));
  if (s[i] == t[j]) {
    dp[i][j] = max(dp[i][j], 1 + DP(i + 1, j + 1));
  }
  done[i][j] = true;
  return dp[i][j];
}

string lcs;

// Reconstruct lcs(s[i, n), t[j, m))
void Reconstruct(int i, int j) {
  if (i == (int)s.size()) return;
  if (j == (int)t.size()) return;
  if (DP(i, j) == DP(i + 1, j)) {
    Reconstruct(i + 1, j);
  } else if (DP(i, j) == DP(i, j + 1)) {
    Reconstruct(i, j + 1);
  } else if (s[i] == t[j] && DP(i, j) == 1 + DP(i + 1, j + 1)) {
    lcs += s[i];
    Reconstruct(i + 1, j + 1);
  }
}

void Solve(void) {
  cin >> s >> t;
  Reconstruct(0, 0);
  cout << lcs << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  // cin >> t;
  while (t--) Solve();
  return 0;
}

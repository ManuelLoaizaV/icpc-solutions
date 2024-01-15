// https://codeforces.com/contest/1433/problem/F
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

const int N = 70;
const Long MOD = 998244353LL;
const int INF = 350000;
const Double PI = acos(-1);
const Double EPS = 1e-9;

const char A = 'a';
const char ZERO = '0';
const char ENDL = '\n';

const string YES = "YES";
const string NO = "NO";

int n, m, k;
int grid[N][N];
bool done[N][N][N][N / 2 + 1];
int dp[N][N][N][N / 2 + 1];

int DP(int row, int col, int mod, int n_used) {
  if (row == n) {
    if (mod == 0) return 0;
    return -INF;
  }
  if (done[row][col][mod][n_used]) return dp[row][col][mod][n_used];

  int next_row = row;
  int next_col = col + 1;
  if (next_col == m) {
    next_row++;
    next_col = 0;
  }

  dp[row][col][mod][n_used] = DP(next_row, next_col, mod, ((next_col == 0) ? 0 : n_used));

  if ((n_used + 1) <= m / 2) {
    dp[row][col][mod][n_used] = max(
      dp[row][col][mod][n_used],
      grid[row][col] + DP(
        next_row,
        next_col,
        (mod + grid[row][col]) % k,
        ((next_col == 0) ? 0 : (n_used + 1))
      )
    );
  }

  done[row][col][mod][n_used] = true;
  return dp[row][col][mod][n_used];
}

void Solve(void) {
  cin >> n >> m >> k;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> grid[i][j];
  cout << DP(0, 0, 0, 0) << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  // cin >> t;
  while (t--) Solve();
  return 0;
}

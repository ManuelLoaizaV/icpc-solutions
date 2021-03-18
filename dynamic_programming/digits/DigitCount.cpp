//https://lightoj.com/problem/digit-count
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

typedef long long Long;

const int N = 10;

bool found[N];
bool done[N][N];
Long dp[N][N];
int len;

Long DP(int pos, int last) {
  if (pos == len) return 1LL;
  if (done[pos][last]) return dp[pos][last];
  dp[pos][last] = 0;
  if (pos == 0) {
    for (int d = 0; d <= 9; d++) if (found[d]) dp[pos][last] += DP(pos + 1, d);
  } else {
    int inf = max(0, last - 2);
    int sup = min(9, last + 2);
    for (int d = inf; d <= sup; d++) if (found[d]) dp[pos][last] += DP(pos + 1, d);
  }
  done[pos][last] = true;
  return dp[pos][last];
}

Long Solve(Long n) {
  if (n <= 0) return 0;
  len = n;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < N; j++)
        done[i][j] = false;
  return DP(0, 0);
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  for (int t = 1; t <= tt; t++) {
    int m, n;
    cin >> m >> n;
    for (int i = 0; i < N; i++) found[i] = false;
    for (int i = 0; i < m; i++) {
      int x;
      cin >> x;
      found[x] = true;
    }
    Long ans = Solve(n);
    cout << "Case " << t << ": " << ans << '\n';
  }
  return 0;
}

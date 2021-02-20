//https://atcoder.jp/contests/abc192/tasks/abc192_f
#include <bits/stdc++.h>
#include <unistd.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define all(v) (v).begin(),(v).end()
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 101;
const Long INF = 1e16;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

int Sub(int a, int b, int m) {
  return (a - (b % m) + m) % m;
}

Long a[N];
// DP(i, k, r): maxima sum con elementos [0 .. i] cuando tengo tengo k elementos
// pendientes por escoger y quiero conseguir residuo r
bool is_done[N][N][N][N];
Long dp[N][N][N][N];
Long DP(int i, int k, int r, int sz) {
  //debug(i, k, r);
  if (k == 0) {
    if (r == 0) return 0;
    return -INF;
  }
  if (i < 0) return -INF;
  if (is_done[i][k][r][sz]) return dp[i][k][r][sz];
  dp[i][k][r][sz] = DP(i - 1, k, r, sz);
  dp[i][k][r][sz] = max(dp[i][k][r][sz], a[i] + DP(i - 1, k - 1, Sub(r, a[i], sz), sz));
  is_done[i][k][r][sz] = true;
  return dp[i][k][r][sz];
}

void Solve(void) {
  Long n, x;
  cin >> n >> x;
  for (int i = 0; i < n; i++) cin >> a[i];
  Long ans = LLONG_MAX;
  for (int k = 1; k <= n; k++) {
    Long mx = DP(n - 1, k, x % k, k);
    if (mx <= 0) continue;
    Long delta = x - mx;
    Long tmp = delta / k;
    ans = min(ans, tmp);
  }
  cout << ans << '\n';
}

int main(void) {
  FAST_IO;
  int t = 1;
  //cin >> t;
  while (t--) Solve();
  return 0;
}


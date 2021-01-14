//https://codeforces.com/problemset/problem/1389/B
#include <iostream>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;

const int N = 1e5;
const int Z = 6;

Long n, k, z;
Long a[N];

Long dp[N][Z];
bool is_done[N][Z];

Long DP(int pos, int used) {
  int cnt = pos + 2 * used;
  if (cnt == k) return 0;
  if (is_done[pos][used]) return dp[pos][used];
  dp[pos][used] = a[pos + 1] + DP(pos + 1, used);
  if (used < z) {
    if (cnt + 1 == k) {
      dp[pos][used] = max(dp[pos][used], a[pos - 1]);
    } else {
      dp[pos][used] = max(dp[pos][used], a[pos - 1] + a[pos] + DP(pos, used + 1));
    }
  }
  is_done[pos][used] = true;
  return dp[pos][used];
}

void Initialize(void) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < Z; j++) {
      is_done[i][j] = false;
    }
  }
}

void Solve(void) {
  cin >> n >> k >> z;
  Initialize();
  for (int i = 0; i < n; i++) cin >> a[i];
  Long ans = a[0] + a[1] + DP(1, 0);
  cout << ans << '\n';
}

int main(void) {
  FAST_IO;
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}

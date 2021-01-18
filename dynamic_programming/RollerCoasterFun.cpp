//https://open.kattis.com/problems/rollercoasterfun
#include <iostream>
#include <vector>
using namespace std;

const int N = 100;
const int T = 25000;
const int MAX_N = 3400;

struct RollerCoaster {
  int v, w;
  bool zero;
};

/*
int DP(int pos, int rem) {
  if (pos == rc.size() || rem == 0) return 0;
  if (is_done[pos][rem]) return dp[pos][rem];
  int v = rc[pos].v;
  int w = rc[pos].w;
  bool is_zero = rc[pos].zero;
  dp[pos][rem] = DP(pos + 1, rem);
  if (rem - w >= 0) dp[pos][rem] = max(dp[pos][rem], v + DP(pos + 1 - is_zero, rem - w));
  is_done[pos][rem] = true;
  return dp[pos][rem];
}
*/
int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<RollerCoaster> rc;
  for (int i = 0; i < n; i++) {
    int a, b, t;
    cin >> a >> b >> t;
    if (a == 0) continue;
    if (b == 0) {
      rc.push_back({a, t, true});
      continue;
    }
    int k = 1;
    while (true) {
      int val = a - (k - 1) * (k - 1) * b;
      if (val <= 0) break;
      rc.push_back({val, t, false});
      k++;
    }
  }
  int dp[MAX_N][T + 1];
  for (int i = 0; i < MAX_N; i++)
    for (int j = 0; j <= T; j++)
      dp[i][j] = 0;
  for (int pos = 1; pos <= rc.size(); pos++) {
    int who = pos - 1;
    int v = rc[who].v;
    int w = rc[who].w;
    bool is_zero = rc[who].zero;
    for (int t = 1; t <= T; t++) {
      dp[pos][t] = dp[pos - 1][t];
      if (is_zero) {
        if (w <= t) dp[pos][t] = max(dp[pos][t], v + dp[pos][t - w]);
      } else {
        if (w <= t) dp[pos][t] = max(dp[pos][t], v + dp[pos - 1][t - w]);
      }
    }
  }
  int q;
  cin >> q;
  while (q--) {
    int t;
    cin >> t;
    cout << dp[rc.size()][t] << '\n';
  }
  return 0;
}

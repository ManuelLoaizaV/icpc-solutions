//https://codeforces.com/problemset/problem/730/J
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#define a second
#define b first
using namespace std;

const int INF = 1e6;
const int N = 100;
const int M = N * N;
pair<int, int> bottles[N];

int dp[M + 1][N + 1][N], sum;

// DP(v, r, p): maxima cantidad de soda que puedo obtener con v de volumen hasta ahora,
// con r botellas por utilizar en la posicion [0 .. p].
int DP(int vol, int rem, int pos) {
  if (rem == 0) return (vol < sum) ? -INF : 0;
  if (pos < 0) return -INF;
  if (dp[vol][rem][pos] != INF) return dp[vol][rem][pos];
  dp[vol][rem][pos] = DP(vol, rem, pos - 1);
  dp[vol][rem][pos] = max(dp[vol][rem][pos], bottles[pos].a + DP(bottles[pos].b + vol, rem - 1, pos - 1));
  return dp[vol][rem][pos];
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> bottles[i].a;
  for (int i = 0; i < n; i++) cin >> bottles[i].b;
  sum = 0;
  for (int i = 0; i < n; i++) sum += bottles[i].a;
  sort(bottles, bottles + n);
  int mn = 1;
  int acc = 0;
  for (int i = n - 1; i >= 0; i--) {
    acc += bottles[i].b;
    if (acc >= sum) break;
    mn++;
  }
  for (int i = 0; i <= M; i++)
    for (int j = 0; j <= mn; j++)
      for (int k = 0; k < n; k++)
        dp[i][j][k] = INF;
  int mx = DP(0, mn, n - 1);
  int ans = sum - mx;
  cout << mn << " " << ans << '\n';
  return 0;
}

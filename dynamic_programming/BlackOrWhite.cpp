//https://www.spoj.com/problems/BORW/
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

const int N = 205;

int n, a[N];

void Compress(void) {
  vector<pair<int, int>> pairs;
  for (int i = 0; i < n; i++) pairs.push_back({a[i], i});
  sort(pairs.begin(), pairs.end());
  int nxt = 1;
  for (int i = 0; i < n; i++) {
    if (i > 0 && pairs[i].first != pairs[i - 1].first) nxt++;
    a[pairs[i].second] = nxt;
  }
}

int dp[N][N][N];
bool is_done[N][N][N];

int DP(int i, int j, int k) {
  if (k == n) return 0;
  if (is_done[i][j][k]) return dp[i][j][k];
  dp[i][j][k] = DP(i, j, k + 1);
  if (a[k] < i) dp[i][j][k] = max(dp[i][j][k], 1 + DP(a[k], j, k + 1));
  if (a[k] > j) dp[i][j][k] = max(dp[i][j][k], 1 + DP(i, a[k], k + 1));
  is_done[i][j][k] = true;
  return dp[i][j][k];
}

void Solve(void) {
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i <= n + 3; i++)
    for (int j = 0; j <= n + 3; j++)
      for (int k = 0; k <= n + 3; k++)
        is_done[i][j][k] = false;
  Compress();
  cout << n - DP(n + 1, 0, 0) << '\n';
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  while (cin >> n) {
    if (n == -1) break;
    Solve();
  }
  return 0;
}

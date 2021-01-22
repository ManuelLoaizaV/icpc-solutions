//https://codeforces.com/problemset/problem/1005/D
#include <iostream>
#include <string>
using namespace std;

const int N = 2e5;

bool is_done[N][3];
int a[N], dp[N][3];

// DP(i, r): maximo numero de bloques multiplos de tres que puedo obtener con los
// bloques [0 .. i] llegando con un residuo r.
int DP(int i, int r) {
  if (i < 0) return 0;
  if (is_done[i][r]) return dp[i][r];
  if (r == 0) {
    if (a[i] == 0) {
      dp[i][r] = 1 + DP(i - 1, 0);
    } else {
      dp[i][r] = DP(i - 1, a[i]);
    }
  } else {
    if (a[i] == 0) {
      dp[i][r] = 1 + DP(i - 1, 0);
    } else {
      int sum = (a[i] + r) % 3;
      if (sum == 0) {
        dp[i][r] = 1 + DP(i - 1, 0);
      } else {
        dp[i][r] = DP(i - 1, 0);
        dp[i][r] = max(dp[i][r], DP(i - 1, sum));
        dp[i][r] = max(dp[i][r], DP(i - 1, a[i]));
      }
    }
  }
  is_done[i][r] = true;
  return dp[i][r];
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  string s;
  cin >> s;
  int n = s.size();
  for (int i = 0; i < n; i++) a[i] = (s[i] - '0') % 3;
  cout << DP(n - 1, 0) << '\n';
  return 0;
}

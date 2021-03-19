//https://www.hackerrank.com/contests/projecteuler/challenges/euler162/problem
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const Long MOD = 1e9 + 7;
const int N = 105;
const int D = 16;

Long Add(Long a, Long b) {
  return (a + b) % MOD;
}

Long dp[N][2][8];
bool done[N][2][8];

Long DP(int pos, bool all_zeroes, int mask) {
  if (pos == 0) return (!all_zeroes && mask == 7) ? 1 : 0;
  if (done[pos][all_zeroes][mask]) return dp[pos][all_zeroes][mask];
  done[pos][all_zeroes][mask] = true;
  dp[pos][all_zeroes][mask] = 0;
  for (int d = 0; d < D; d++) {
    int next_mask = mask;
    if (0 < d && d < 3 || !all_zeroes && d == 0) next_mask = next_mask | (1 << d);
    dp[pos][all_zeroes][mask] = Add(dp[pos][all_zeroes][mask], DP(pos - 1, all_zeroes && d == 0, next_mask));
  }
  done[pos][all_zeroes][mask] = true;
  return dp[pos][all_zeroes][mask];
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  cout << DP(n, true, 0) << '\n';
  return 0;
}

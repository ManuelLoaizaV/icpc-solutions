//https://www.hackerrank.com/contests/projecteuler/challenges/euler113/problem
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 1e5;
const int D = 10;
const Long MOD = 1e9 + 7;

Long Add(Long a, Long b) {
  return (a + b) % MOD;
}

Long Sub(Long a, Long b) {
  return (a - b + MOD) % MOD;
}

Long Mul(Long a, Long b) {
  return (a * b) % MOD;
}

Long dp[N][D][2][2];
bool done[N][D][2][2];

Long DP(int pos, int last, bool all_zeroes, bool increasing) {
  if (pos == N) return 1LL;
  if (done[pos][last][all_zeroes][increasing]) return dp[pos][last][all_zeroes][increasing];
  dp[pos][last][all_zeroes][increasing] = 0;
  if (all_zeroes) {
    for (int d = 0; d <= 9; d++)
      dp[pos][last][all_zeroes][increasing] = Add(dp[pos][last][all_zeroes][increasing], DP(pos + 1, d, all_zeroes && d == 0, increasing));
  } else {
    int inf = (increasing) ? last : 0;
    int sup = (increasing) ? 9 : last;
    for (int d = inf; d <= sup; d++)
      dp[pos][last][all_zeroes][increasing] = Add(dp[pos][last][all_zeroes][increasing], DP(pos + 1, d, all_zeroes && d == 0, increasing));
  }
  done[pos][last][all_zeroes][increasing] = true;
  return dp[pos][last][all_zeroes][increasing];
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    int k;
    cin >> k;
    Long ans = Add(DP(N - k, 0, true, true), DP(N - k, 0, true, false));
    ans = Sub(ans, Mul(9LL, k));
    ans = Sub(ans, 2LL);
    cout << ans << '\n';
  }
  return 0;
}

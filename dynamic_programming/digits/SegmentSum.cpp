//https://codeforces.com/problemset/problem/1073/E
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

const int N = 18;
const int K = 10;
const int M = 1 << K;
const Long MOD = 998244353;

vector<int> s;
Long k;
Long pot[N];
bool done[N][2][2][M];
Pair dp[N][2][2][M];

Long Add(Long a, Long b) {
  return (a + b) % MOD;
}

Long Sub(Long a, Long b) {
  return (a - b + MOD) % MOD;
}

Long Mul(Long a, Long b) {
  return (a * b) % MOD;
}

void TurnOn(int& mask, int bit) {
  mask = mask | (1 << bit);
}

Pair DP(int pos, bool lower, bool all_zeroes, int mask) {
  if (__builtin_popcount(mask) > k) return {0LL, 0LL};
  if (pos == N) return {1LL, 0LL};
  if (done[pos][lower][all_zeroes][mask]) return dp[pos][lower][all_zeroes][mask];
  dp[pos][lower][all_zeroes][mask] = {0, 0};
  int lim = (lower) ? 9 : s[pos];
  for (Long d = 0; d <= lim; d++) {
    int nxt_mask = mask;
    if (!all_zeroes || all_zeroes && d != 0) TurnOn(nxt_mask, d);
    Pair nxt = DP(pos + 1, lower || d < lim, all_zeroes && d == 0, nxt_mask);
    dp[pos][lower][all_zeroes][mask].first = Add(dp[pos][lower][all_zeroes][mask].first, nxt.first);
    dp[pos][lower][all_zeroes][mask].second = Add(dp[pos][lower][all_zeroes][mask].second, nxt.second);
    dp[pos][lower][all_zeroes][mask].second = Add(dp[pos][lower][all_zeroes][mask].second, Mul(Mul(d, pot[N - 1 - pos]), nxt.first));
  }
  done[pos][lower][all_zeroes][mask] = true;
  return dp[pos][lower][all_zeroes][mask];
}

Long Solve(Long n) {
  if (n <= 0) return 0LL;
  s.clear();
  for (int i = 0; i < N; i++) {
    s.push_back(n % 10);
    n /= 10;
  }
  reverse(s.begin(), s.end());
  for (int i = 0; i < N; i++)
    for (int j = 0; j < 2; j++)
      for (int l = 0; l < 2; l++)
        for (int m = 0; m < M; m++)
         done[i][j][l][m] = false; 
  return DP(0, false, true, 0).second;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  pot[0] = 1LL;
  for (int i = 1; i < N; i++) pot[i] = Mul(pot[i - 1], 10LL);
  Long l, r;
  cin >> l >> r >> k;
  Long ans = Sub(Solve(r), Solve(l - 1));
  cout << ans << '\n';
  return 0;
}

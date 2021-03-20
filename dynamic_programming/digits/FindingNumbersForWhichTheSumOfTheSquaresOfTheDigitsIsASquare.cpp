//https://www.hackerrank.com/contests/projecteuler/challenges/euler171/problem
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

const int N = 105;
const int M = 8190;
const Long MOD = 1e9 + 7;

vector<int> s;
bool found[M];
bool done[N][M][2];
Pair dp[N][M][2];
Long pot[N];

Long Add(Long a, Long b) {
  return (a + b) % MOD;
}

Long Mul(Long a, Long b) {
  return (a * b) % MOD;
}

Pair DP(int pos, int sum, bool lower) {
  if (pos == (int) s.size()) return {((found[sum]) ? 1 : 0), 0};
  if (done[pos][sum][lower]) return dp[pos][sum][lower];
  dp[pos][sum][lower] = {0, 0};
  int lim = (lower) ? 9 : s[pos];
  for (int d = 0; d <= lim; d++) {
    Pair nxt = DP(pos + 1, sum + d * d, lower || d < s[pos]);
    dp[pos][sum][lower].first = Add(dp[pos][sum][lower].first, nxt.first);
    dp[pos][sum][lower].second = Add(dp[pos][sum][lower].second, nxt.second);
    dp[pos][sum][lower].second = Add(dp[pos][sum][lower].second, Mul(Mul((Long) d, pot[(int) s.size() - 1 - pos]), nxt.first));
  }
  done[pos][sum][lower] = true;
  return dp[pos][sum][lower];
}

Long Solve(const string& n) {
  s.clear();
  int len = (int) n.size();
  for (int i = 0; i < len; i++) s.push_back(n[i] - '0');
  return DP(0, 0, false).second;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  pot[0] = 1LL;
  for (int i = 1; i < N; i++) pot[i] = Mul(pot[i - 1], 10LL);
  for (int i = 1; i * i < M; i++) found[i * i] = true;
  string n;
  cin >> n;
  cout << Solve(n) << '\n';
  return 0;
}

//https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=4408
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

const int N = 64;

vector<int> s;
Pair dp[N][2];
bool done[N][2];

Pair DP(int pos, bool lower) {
  if (pos == (int) s.size()) return {1, 0};
  if (done[pos][lower]) return dp[pos][lower];
  dp[pos][lower] = {0, 0};
  int lim = (lower) ? 1 : s[pos];
  for (int d = 0; d <= lim; d++) {
    Pair nxt = DP(pos + 1, lower || d < lim);
    dp[pos][lower].first += nxt.first;
    dp[pos][lower].second += nxt.second;
    dp[pos][lower].second += (Long) d * nxt.first;
  }
  done[pos][lower] = true;
  return dp[pos][lower];
}

Long Solve(Long n) {
  if (n <= 0) return 0;
  s.clear();
  while (n > 0) {
    s.push_back(n & 1);
    n >>= 1;
  }
  for (int i = 0; i < (int) s.size(); i++)
    for (int j = 0; j < 2; j++)
      done[i][j] = false;
  reverse(s.begin(), s.end());
  return DP(0, false).second;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Long a, b;
  while (cin >> a >> b) {
    Long ans = Solve(b) - Solve(a - 1);
    cout << ans << '\n';
  }
  return 0;
}

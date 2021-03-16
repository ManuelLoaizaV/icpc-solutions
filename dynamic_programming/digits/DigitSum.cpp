//https://www.spoj.com/problems/PR003004/
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

const int N = 16;
const int S = 137;

bool done[N][2][S];
Pair dp[N][2][S];
deque<Long> s;

Pair DP(int pos, bool lower, Long sum) {
  if (pos == (int) s.size()) return {1, 0};
  if (done[pos][lower][sum]) return dp[pos][lower][sum];
  dp[pos][lower][sum] = {0, 0};
  Long lim = (lower) ? 9LL : s[pos];
  for (Long d = 0; d <= lim; d++) {
    Pair nxt = DP(pos + 1, lower || d < lim, sum + d);
    dp[pos][lower][sum].first += nxt.first;
    dp[pos][lower][sum].second += (d * nxt.first + nxt.second);
  }
  done[pos][lower][sum] = true;
  return dp[pos][lower][sum];
}

Long Solve(Long n) {
  if (n <= 0) return 0LL;
  s.clear();
  for (int i = 0; i < N; i++) {
    s.push_front(n % 10);
    n /= 10;
  }
  for (int i = 0; i < N; i++)
    for (int j = 0; j < 2; j++)
      for (int k = 0; k < S; k++)
        done[i][j][k] = false;
  return DP(0, false, 0).second;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    Long l, r;
    cin >> l >> r;
    Long ans = Solve(r) - Solve(l - 1);
    cout << ans << '\n';
  }
  return 0;
}

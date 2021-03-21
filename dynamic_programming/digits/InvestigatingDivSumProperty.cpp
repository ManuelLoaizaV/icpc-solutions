//https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=2346
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 12;
const int S = 95;

Long k;
vector<int> s;
bool done[N][S][S][2];
Long dp[N][S][S][2];
Long pot[N];

Long Add(Long a, Long b) {
  return ((a % k) + (b % k)) % k;
}

Long Mul(Long a, Long b) {
  return ((a % k) * (b % k)) % k;
}

Long DP(int pos, Long current_sum, Long digit_sum, bool lower) {
  if (pos == (int) s.size()) return ((current_sum == 0 && digit_sum == 0) ? 1LL : 0LL);
  if (done[pos][current_sum][digit_sum][lower]) return dp[pos][current_sum][digit_sum][lower];
  dp[pos][current_sum][digit_sum][lower] = 0;
  Long lim = (lower) ? 9 : s[pos];
  for (Long d = 0; d <= lim; d++)
    dp[pos][current_sum][digit_sum][lower] += DP(pos + 1, Add(current_sum, Mul(d, pot[(int) s.size() - 1 - pos])), Add(digit_sum, d), lower || d < lim);
  done[pos][current_sum][digit_sum][lower] = true;
  return dp[pos][current_sum][digit_sum][lower];
}

Long Solve(Long n) {
  if (n == 0) return 1;
  s.clear();
  while (n > 0) {
    s.push_back(n % 10);
    n /= 10;
  }
  reverse(s.begin(), s.end());
  pot[0] = 1 % k;
  for (int i = 1; i < (int) s.size(); i++) pot[i] = Mul(pot[i - 1], 10LL);
  for (int i = 0; i < (int) s.size(); i++)
    for (int j = 0; j < k; j++)
      for (int l = 0; l < k; l++)
        for (int m = 0; m < 2; m++)
          done[i][j][l][m] = false;
  return DP(0, 0, 0, false);
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    Long a, b;
    cin >> a >> b >> k;
    if (k >= S) {
      cout << 0 << '\n';
      continue;
    }
    Long ans = Solve(b) - Solve(a - 1);
    cout << ans << '\n';
  }
  return 0;
}

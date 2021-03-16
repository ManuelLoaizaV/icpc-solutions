//https://www.spoj.com/problems/NUMTSN/
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const Long MOD = 1e9 + 7;

const int N = 51;
const int S = 36;

Long Add(Long a, Long b) {
  return (a + b) % MOD;
}

Long Sub(Long a, Long b) {
  return (a - b + MOD) % MOD;
}

Long Mul(Long a, Long b) {
  return (a * b) % MOD;
}

bool Check(const string& s) {
  int three, six, nine;
  three = six = nine = 0;
  for (char c : s) {
    if (c == '3') {
      three++;
    } else if (c == '6') {
      six++;
    } else if (c == '9') {
      nine++;
    }
  }
  if (three == 0) return false;
  return (three == six && six == nine);
}

int C, L;
vector<Long> s;
bool done[N][2][2][S][S];
Long dp[N][2][2][S][S];

Long DP(int pos, bool lower, bool has_three, int d_3_6, int d_6_9) {
  if (d_3_6 < 0 || d_3_6 >= C || d_6_9 < 0 || d_6_9 >= C) return 0;
  if (pos == (int) s.size()) {
    if (!has_three) return 0;
    return (d_3_6 == L && d_6_9 == L) ? 1LL : 0LL;
  }
  if (done[pos][lower][has_three][d_3_6][d_6_9]) return dp[pos][lower][has_three][d_3_6][d_6_9];
  dp[pos][lower][has_three][d_3_6][d_6_9] = 0;
  Long lim = (lower) ? 9LL : s[pos];
  for (Long d = 0; d <= lim; d++) dp[pos][lower][has_three][d_3_6][d_6_9] = Add(dp[pos][lower][has_three][d_3_6][d_6_9], DP(pos + 1, lower || d < lim, has_three || d == 3, d_3_6 + ((d == 3) ? 1 : 0) + ((d == 6) ? -1 : 0), d_6_9 + ((d == 6) ? 1 : 0) + ((d == 9) ? -1 : 0)));
  done[pos][lower][has_three][d_3_6][d_6_9] = true;
  return dp[pos][lower][has_three][d_3_6][d_6_9];
}

Long Solve(const string& n) {
  int len = (int) n.size();
  L = len / 3;
  C = 2 * L + 1;
  s.clear();
  for (int i = 0; i < len; i++) s.push_back(n[i] - '0');
  for (int i = 0; i < len; i++)
    for (int j = 0; j < 2; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < C; l++)
          for (int m = 0; m < C; m++)
            done[i][j][k][l][m] = false;
  return DP(0, false, false, L, L);
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    string l, r;
    cin >> l >> r;
    Long ans = Sub(Solve(r), Solve(l));
    if (Check(l)) ans = Add(ans, 1LL);
    cout << ans << '\n';
  }
  return 0;
}

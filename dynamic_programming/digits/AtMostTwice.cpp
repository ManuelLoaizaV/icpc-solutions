//https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=4892
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 19;
const int D = 10;
const int M = 59049;

int pot[N];
bool dp[N][M][2][2];
bool done[N][M][2][2];
vector<int> s;

vector<int> ans;

bool DP(int pos, int mask, bool all_zeroes, bool lower) {
  vector<int> cnt(D, 0);
  int copy = mask;
  for (int i = 0; i < D; i++) {
    cnt[i] = copy % 3;
    copy /= 3;
  }
  if (pos == (int) s.size()) return !all_zeroes;
  if (done[pos][mask][all_zeroes][lower]) return dp[pos][mask][all_zeroes][lower];
  done[pos][mask][all_zeroes][lower] = true;
  dp[pos][mask][all_zeroes][lower] = false;
  int lim = (lower) ? 9 : s[pos];
  for (int d = lim; d >= 0; d--) {
    if (cnt[d] == 2) continue;
    int nxt_mask = mask;
    if (all_zeroes && d != 0 || !all_zeroes) nxt_mask += pot[d];
    bool nxt = DP(pos + 1, nxt_mask, all_zeroes && d == 0, lower || d < lim);
    dp[pos][mask][all_zeroes][lower] |= nxt;
    if (nxt) {
      if (!all_zeroes || all_zeroes && d != 0) ans.push_back(d);
      break;
    }
  }
  return dp[pos][mask][all_zeroes][lower];
}

void Solve(Long n) {
  ans.clear();
  s.clear();
  while (n > 0) {
    s.push_back(n % D);
    n /= D;
  }
  reverse(s.begin(), s.end());
  for (int i = 0; i < (int) s.size(); i++)
    for (int j = 0; j < M; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 2; l++)
          done[i][j][k][l] = false;
  DP(0, 0, true, false);
  reverse(ans.begin(), ans.end());
  for (int c : ans) cout << c;
  cout << '\n';
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  pot[0] = 1;
  for (int i = 1; i < D; i++) pot[i] = pot[i - 1] * 3;
  Long n;
  while (cin >> n) Solve(n);
  return 0;
}

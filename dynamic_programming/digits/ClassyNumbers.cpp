//https://codeforces.com/problemset/problem/1036/C
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 19;

vector<int> s;
Long dp[N][2][4];
bool done[N][2][4];

Long DP(int pos, bool lower, int cnt) {
  if (cnt == 4) return 0;
  if (pos == (int) s.size()) return 1;
  if (done[pos][lower][cnt]) return dp[pos][lower][cnt];
  dp[pos][lower][cnt] = 0;
  int lim = (lower) ? 9 : s[pos];
  for (int d = 0; d <= lim; d++)
    dp[pos][lower][cnt] += DP(pos + 1, lower || d < lim, cnt + ((d != 0) ? 1 : 0));
  done[pos][lower][cnt] = true;
  return dp[pos][lower][cnt];
}


Long Solve(Long n) {
  s.clear();
  for (int i = 0; i < N; i++) {
    s.push_back(n % 10);
    n /= 10;
  }
  reverse(s.begin(), s.end());
  for (int i = 0; i < N; i++)
    for (int j = 0; j < 2; j++)
      for (int k = 0; k < 4; k++)
        done[i][j][k] = false;
  return DP(0, false, 0);
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

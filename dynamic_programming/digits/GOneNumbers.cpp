//https://www.spoj.com/problems/GONE/en/
#include <bits/stdc++.h>
using namespace std;

const int N = 9;
const int S = 75;
const vector<int> p = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73};

bool prime[S];
bool done[N][2][S];
int dp[N][2][S];
deque<int> s;

int DP(int pos, bool lower, int sum) {
  if (pos == (int) s.size()) return (prime[sum]) ? 1 : 0;
  if (done[pos][lower][sum]) return dp[pos][lower][sum];
  dp[pos][lower][sum] = 0;
  int limit = (lower) ? 9 : s[pos];
  for (int d = 0; d <= limit; d++) {
    dp[pos][lower][sum] += DP(pos + 1, lower || d < limit, sum + d);
  }
  done[pos][lower][sum] = true;
  return dp[pos][lower][sum];
}

int Solve(int n) {
  if (n <= 0) return 0;
  s.clear();
  for (int i = 0; i < N; i++) {
    s.push_front(n % 10);
    n /= 10;
  }
  for (int i = 0; i < N; i++)
    for (int j = 0; j < 2; j++)
      for (int k = 0; k < S; k++)
        done[i][j][k] = false;
  return DP(0, false, 0);
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  for (int i = 0; i < S; i++) prime[i] = false;
  for (int x : p) prime[x] = true;
  int tt;
  cin >> tt;
  while (tt--) {
    int l, r;
    cin >> l >> r;
    int ans = Solve(r) - Solve(l - 1);
    cout << ans << '\n';
  }
  return 0;
}

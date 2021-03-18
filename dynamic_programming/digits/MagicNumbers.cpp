//https://codeforces.com/problemset/problem/628/D
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl 
using namespace std;

typedef long long Long;

const Long MOD = 1e9 + 7;
const int N = 2e3 + 5;

Long Add(Long a, Long b) {
  return (a + b) % MOD;
}

Long Sub(Long a, Long b) {
  return (a - b + MOD) % MOD;
}

Long Mul(Long a, Long b) {
  return (a * b) % MOD;
}

vector<int> s;
int m, d;
int pot[N];

bool Check(const string& n) {
  int len = (int) n.size();
  int dist = 2;
  int mod = 0;
  for (int pos = 0; pos < len; pos++) {
    int digit = n[pos] - '0';
    if (dist == 2) {
      if (digit == 0) continue;
      if (digit == d) return false;
      mod = (mod + digit * pot[len - 1 - pos]) % m;
      dist = 0;
    } else {
      if (dist == 0 && digit == d) return false;
      if (dist == 1 && digit != d) return false;
      mod = (mod + digit * pot[len - 1 - pos]) % m;
    }
    if (dist != 2) dist ^= 1;
  }
  return (dist != 2 && mod == 0);
}

bool done[N][N][3][2];
Long dp[N][N][3][2];

Long DP(int pos, int mod, int dist, bool lower) {
  if (pos == (int) s.size()) return ((mod == 0 && dist != 2) ? 1LL : 0LL);
  if (done[pos][mod][dist][lower]) return dp[pos][mod][dist][lower];
  int lim = (lower) ? 9 : s[pos];
  dp[pos][mod][dist][lower] = 0LL;
  for (int digit = 0; digit <= lim; digit++) {
    int p = (int) s.size() - pos - 1;
    int nxt_mod = (mod + digit * pot[p]) % m;
    if (dist == 2) {
      if (digit == 0) {
        dp[pos][mod][dist][lower] = Add(dp[pos][mod][dist][lower], DP(pos + 1, mod, 2, lower || digit < lim));
      } else if (digit == d) {
        continue;
      } else {
        dp[pos][mod][dist][lower] = Add(dp[pos][mod][dist][lower], DP(pos + 1, nxt_mod, 1, lower || digit < lim));
      }
    } else {
      if (dist == 0 && digit == d || dist == 1 && digit != d) continue;
      dp[pos][mod][dist][lower] = Add(dp[pos][mod][dist][lower], DP(pos + 1, nxt_mod, dist ^ 1, lower || digit < lim));
    }
  }
  done[pos][mod][dist][lower] = true;
  return dp[pos][mod][dist][lower];
}

Long Solve(const string& n) {
  s.clear();
  int len = (int) n.size();
  for (int i = 0; i < len; i++) s.push_back(n[i] - '0');
  for (int i = 0; i < len; i++)
    for (int j = 0; j < m; j++)
      for (int k = 0; k < 3; k++)
        for (int l = 0; l < 2; l++)
          done[i][j][k][l] = false;
  Long x = DP(0, 0, 2, false);
  return x;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> m >> d;
  pot[0] = 1;
  for (int i = 1; i < N; i++) pot[i] = (pot[i - 1] * 10) % m;
  string a, b;
  cin >> a >> b;
  Long ans = Sub(Solve(b), Solve(a));
  if (Check(a)) ans = Add(ans, 1LL);
  cout << ans << '\n';
  return 0;
}

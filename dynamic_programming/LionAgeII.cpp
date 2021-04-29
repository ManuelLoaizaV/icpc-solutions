//https://codeforces.com/problemset/problem/73/C
//#pragma GCC optimize ("Ofast,unroll-loops")
//#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include <unistd.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 100;
const int A = 26;
const int C = (int) 'a';
const Long INF = 1e18;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

vector<vector<Long>> cost;
string s;

Long dp[N][A][N + 5];
bool done[N][A][N + 5];

// DP(i, j, k): maximum posisble euphony of the string s[pos .. n - 1]
// with s[pos - 1] = j and k remaining moves
Long DP(int pos, int prev, int rem) {
  if (pos == (int) s.size()) return 0;
  if (done[pos][prev][rem]) return dp[pos][prev][rem];
  int cur = (int)(s[pos] - C);
  dp[pos][prev][rem] = ((pos == 0) ? 0 : cost[prev][cur]) + DP(pos + 1, cur, rem);
  if (rem > 0) {
    for (int chr = 0; chr < A; chr++) {
      if (chr == cur) continue;
      dp[pos][prev][rem] = max(dp[pos][prev][rem], ((pos == 0) ? 0 : cost[prev][chr]) + DP(pos + 1, chr, rem - 1));
    }
  }
  done[pos][prev][rem] = true;
  return dp[pos][prev][rem];
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> s;
  int k;
  cin >> k;
  int m;
  cin >> m;
  cost = vector<vector<Long>>(A, vector<Long>(A, 0));
  for (int i = 0; i < m; i++) {
    char u, v;
    long w;
    cin >> u >> v >> w;
    cost[u - C][v - C] = w;
  }
  cout << DP(0, 0, k) << '\n';
  return 0;
}

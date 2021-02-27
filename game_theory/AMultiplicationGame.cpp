//https://open.kattis.com/problems/amultiplicationgame
#include <bits/stdc++.h>
#include <unistd.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define all(v) (v).begin(),(v).end()
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 1e6;
const Long INF = 1e18;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

Long n;
unordered_map<Long, bool> is_used, dp;

bool IsWinning(Long p) {
  if (p >= n) return false;
  if (is_used.count(p) > 0) return dp[p];
  is_used[p] = true;
  for (Long i = 2; i <= 9; i++) if (!IsWinning(p * i)) return dp[p] = true;
  return dp[p] = false;
}

void Solve(void) {
  is_used.clear();
  dp.clear();
  if (IsWinning(1LL)) {
    cout << "Stan wins." << '\n';
  } else {
    cout << "Ollie wins." << '\n';
  }
}

int main(void) {
  FAST_IO;
  while (cin >> n) Solve();
  return 0;
}


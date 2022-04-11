// https://codeforces.com/contest/1658/problem/B
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

const int MAX_N = 1000;
const int N = 1e6;
const Long INF = 1e18;
const Double EPS = 1e-9;
const Long MOD = 998244353;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long>(a, b)(rng); }

Long Mul(Long a, Long b) {
  return (a * b) % MOD;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  vector<Long> factorial(MAX_N + 1);
  factorial[0] = 1;
  for (int i = 1; i <= MAX_N; i++) {
    factorial[i] = Mul(factorial[i - 1], i);
  }
  int t;
  cin >> t;
  while (t--) {
    Long n;
    cin >> n;
    if (n & 1) {
      cout << 0 << '\n';
    } else {
      Long beatiful_permutations = Mul(factorial[n / 2], factorial[n / 2]);
      cout << beatiful_permutations << '\n';
    }
  }
  return 0;
}

// https://codeforces.com/contest/1658/problem/D1
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

const int N = 1e6;
const int BITS = 17;
const Long INF = 1e18;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long>(a, b)(rng); }

int GetBit(int n, int i) {
  return (n >> i) & 1;
}

void SetBit(int& n, int i) {
  n = n ^ (1 << i);
}

void Solve(void) {
  int l, r;
  cin >> l >> r;
  int n = r - l + 1;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  int secret = 0;
  for (int bit = 0; bit < BITS; bit++) {
    int zeroes = 0;
    for (int i = 0; i < n; i++) {
      if (GetBit(a[i], bit) == 0) {
        zeroes++;
      }
    }
    int ones = n - zeroes;
    if (ones > zeroes) {
      SetBit(secret, bit);
    }
  }
  cout << secret << '\n';
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}

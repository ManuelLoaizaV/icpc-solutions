// https://codeforces.com/contest/1658/problem/C
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
const Long INF = 1e18;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long>(a, b)(rng); }

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    deque<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];
    int ones = 0;
    for (int i = 0; i < n; i++) {
      if (c[i] == 1) {
        ones++;
      }
    }
    if (ones != 1) {
      cout << "NO" << '\n';
      continue;
    }
    while (c.front() != 1) {
      c.push_back(c.front());
      c.pop_front();
    }

    bool ok = true;
    for (int i = 0; i < n - 1; i++) {
      if (c[i + 1] - c[i] > 1) {
        ok = false;
        break;
      }
    }
    if (ok) {
      cout << "YES" << '\n';
    } else {
      cout << "NO" << '\n';
    }
  }
  return 0;
}

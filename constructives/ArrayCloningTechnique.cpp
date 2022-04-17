// https://codeforces.com/contest/1665/problem/B
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

void Solve(void) {
  unordered_map<Long, Long> frequencies;
  Long n;
  cin >> n;
  Long mx = 0;
  for (int i = 0; i < n; i++) {
    Long x;
    cin >> x;
    if (frequencies.count(x) > 0) {
      frequencies[x]++;
    } else {
      frequencies[x] = 1;
    }
    mx = max(mx, frequencies[x]);
  }
  Long cnt = mx;
  Long it = 0;
  Long rem = 0;
  while (cnt < n) {
    if (rem == 0) {
      it++;
      rem += cnt;
    } else {
      Long add = min(n - cnt, rem);
      cnt += add;
      rem -= add;
      it += add;
    }
  }
  cout << it << '\n';
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}
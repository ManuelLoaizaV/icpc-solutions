//https://codeforces.com/problemset/problem/670/D1
#include <bits/stdc++.h>
#include <unistd.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define all(v) (v).begin(),(v).end()
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 1e3;
const Long INF = 1e9;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

Long a[N], b[N];

bool Check(Long target, Long n, Long k) {
  Long needed = 0;
  for (int i = 0; i < n; i++) {
    Long cnt = a[i] * target;
    if (b[i] < cnt) needed += cnt - b[i];
  }
  return needed <= k;
}

void Solve(void) {
  Long n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i];
  Long l = 0;
  Long r = INF;
  if (!Check(l, n, k)) {
    cout << 0 << '\n';
    return;
  }
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (Check(m, n, k)) {
      l = m;
    } else {
      r = m;
    }
  }
  cout << l << '\n';
}

int main(void) {
  FAST_IO;
  int t = 1;
  //cin >> t;
  while (t--) Solve();
  return 0;
}

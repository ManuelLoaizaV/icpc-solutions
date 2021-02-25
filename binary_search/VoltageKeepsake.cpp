//https://codeforces.com/problemset/problem/772/A
#include <bits/stdc++.h>
#include <unistd.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define all(v) (v).begin(),(v).end()
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 1e5;
const Long INF = 1e14;
const Double EPS = 1e-6;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

Long a[N], b[N];

bool Check(Double t, Long n, Long p) {
  Double sum = 0;
  for (int i = 0; i < n; i++) {
    Double nxt = b[i] - t * a[i];
    if (nxt < 0) sum += abs(nxt) / p;
    if (sum > t) return false;
  }
  return true;
}

void Solve(void) {
  Long n, p;
  cin >> n >> p;
  for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
  Double l = 0;
  Double r = INF;
  if (Check(r, n, p)) {
    cout << -1 << '\n';
    return;
  }
  while (r - l > EPS) {
    Double m = (l + r) / 2;
    if (Check(m, n, p)) {
      l = m;
    } else {
      r = m;
    }
  }
  cout << fixed << setprecision(10) << l << '\n';
}

int main(void) {
  FAST_IO;
  int t = 1;
  //cin >> t;
  while (t--) Solve();
  return 0;
}


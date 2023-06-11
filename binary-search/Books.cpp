//https://codeforces.com/problemset/problem/279/B
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

int Search(int i, Long t, const vector<Long>& sum) {
  int l = i;
  int r = sum.size() - 1;
  Long prev = (l == 0) ? 0 : sum[l - 1];
  if (sum[l] - prev > t) return 0;
  if (sum[r] - prev <= t) return r - l + 1;
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (sum[m] - prev <= t) {
      l = m;
    } else {
      r = m;
    }
  }
  return l - i + 1;
}

void Solve(void) {
  Long n, t;
  cin >> n >> t;
  vector<Long> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  vector<Long> sum(n);
  sum[0] = a[0];
  for (int i = 1; i < n; i++) sum[i] = sum[i - 1] + a[i];
  int ans = 0;
  for (int i = 0; i < n; i++) ans = max(ans, Search(i, t, sum));
  cout << ans << '\n';
}

int main(void) {
  FAST_IO;
  int t = 1;
  //cin >> t;
  while (t--) Solve();
  return 0;
}


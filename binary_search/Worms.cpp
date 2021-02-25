//https://codeforces.com/problemset/problem/474/B
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

void Solve(void) {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  vector<int> sum(n);
  sum[0] = a[0];
  for (int i = 1; i < n; i++) sum[i] = sum[i - 1] + a[i];
  int q;
  cin >> q;
  while (q--) {
    int cnt;
    cin >> cnt;
    int pos = lower_bound(sum.begin(), sum.end(), cnt) - sum.begin();
    cout << pos + 1 << '\n';
  }
}

int main(void) {
  FAST_IO;
  int t = 1;
  //cin >> t;
  while (t--) Solve();
  return 0;
}


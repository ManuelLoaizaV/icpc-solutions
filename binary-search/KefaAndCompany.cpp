//https://codeforces.com/problemset/problem/580/B
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
  Long n, d;
  cin >> n >> d;
  vector<Pair> friends(n);
  for (int i = 0; i < n; i++) cin >> friends[i].first >> friends[i].second;
  sort(friends.begin(), friends.end());
  vector<Long> sum(n);
  sum[0] = friends[0].second;
  for (int i = 1; i < n; i++) sum[i] = sum[i - 1] + friends[i].second;
  Long ans = 0;
  for (int i = 0; i < n; i++) {
    Pair target = {friends[i].first + d, -INF};
    int pos = lower_bound(friends.begin(), friends.end(), target) - friends.begin();
    pos--;
    Long tmp = sum[pos] - ((i == 0) ? 0 : sum[i - 1]);
    ans = max(ans, tmp);
  }
  cout << ans << '\n';
}

int main(void) {
  FAST_IO;
  int t = 1;
  //cin >> t;
  while (t--) Solve();
  return 0;
}


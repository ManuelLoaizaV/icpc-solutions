// https://codeforces.com/contest/1909/problem/C
#include <bits/stdc++.h>

#define debug(x) cout << #x << " = " << x << endl

using namespace std;

typedef long long Long;

const int N = 1e6;
const Long INF = 1e18;
const char ENDL = '\n';

void Solve(void) {
  Long n;
  cin >> n;
  vector<Long> l(n), r(n), c(n);
  for (int i = 0; i < n; i++) cin >> l[i];
  for (int i = 0; i < n; i++) cin >> r[i];
  for (int i = 0; i < n; i++) cin >> c[i];

  sort(l.begin(), l.end());
  sort(c.begin(), c.end());
  set<Long> sorted_r;
  for (int i = 0; i < n; i++) sorted_r.insert(r[i]);

  vector<Long> lengths;
  for (int i = 0; i < n; i++) {
    auto it = sorted_r.upper_bound(l[n - 1 - i]);
    lengths.push_back(*it - l[n - 1 - i]);
    sorted_r.erase(it);
  }

  sort(lengths.begin(), lengths.end());
  Long min_sum = 0LL;
  for (int i = 0; i < n; i++) {
    min_sum += lengths[i] * c[n - 1 - i];
  }
  cout << min_sum << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}
// https://codeforces.com/contest/1909/problem/B
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
  vector<Long> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  Long k = 2LL;
  while (true) {
    set<Long> r;
    for (Long x : a) r.insert(x % k);
    if ((int)r.size() == 2) break;
    k <<= 1LL;
  }
  cout << k << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}
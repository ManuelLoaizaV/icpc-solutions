// https://codeforces.com/contest/1917/problem/C
#include <bits/stdc++.h>

#define debug(x) cout << #x << " = " << x << endl

using namespace std;

typedef long long Long;

const int N = 1e6;
const Long INF = 1e18;
const char ENDL = '\n';
const string YES = "YES";
const string NO = "NO";

void Solve(void) {
  Long n, k, d;
  cin >> n >> k >> d;
  vector<Long> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  vector<Long> b(k);
  for (int i = 0; i < k; i++) cin >> b[i];

  vector<Long> changes(n, 0LL);

  Long max_first_count = min(2LL * n, d);
  Long max_cnt = 0LL;
  for (Long first_count = 0; first_count < max_first_count; first_count++) {
    Long cnt = 0LL;
    for (Long i = 0; i < n; i++) {
      Long value = a[i] + changes[i];
      if (value == (i + 1)) cnt++;
    }
    Long rem = d - 1 - first_count;
    cnt += rem / 2LL;
    max_cnt = max(max_cnt, cnt);
    Long m = b[first_count % k];
    for (int i = 0; i < m; i++) changes[i]++;
  }
  cout << max_cnt << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}
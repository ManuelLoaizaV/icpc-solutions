// https://codeforces.com/contest/1665/problem/C
#include <bits/stdc++.h>
#include <unistd.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 2e5;
const Long INF = 1e18;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long>(a, b)(rng); }

void Solve(void) {
  int n;
  cin >> n;
  vector<int> children(n);
  for (int i = 1; i < n; i++) {
    int p;
    cin >> p;
    p--;
    children[p]++;
  }

  vector<Long> cnt;
  cnt.push_back(1LL);
  for (int i = 0; i < n; i++) {
    if (children[i] > 0) {
      cnt.push_back(children[i]);
    }
  }

  sort(cnt.begin(), cnt.end());
  reverse(cnt.begin(), cnt.end());

  Long n_cnt = (Long) cnt.size();
  Long ans = n_cnt;
  for (Long i = 0; i < n_cnt; i++) {
    cnt[i] = max(0LL, cnt[i] - ans + i);
  }

  vector<int> rem;
  Long sum = 0;
  for (int i = n_cnt - 1; i >= 0; i--) {
    if (cnt[i] > 0) {
      rem.push_back(cnt[i]);
      sum += cnt[i];
    }
  }

  if (rem.size() == 0) {
    cout << ans << '\n';
    return;
  }

  Long cur = 0;
  Long len = (Long) rem.size();
  for (Long days = 1; days <= n; days++) {
    while (cur < len && rem[cur] <= days) {
      sum -= rem[cur];
      cur++;
    }
    Long left = sum - days * (len - cur);
    if (days >= left) {
      ans += days;
      break;
    }
  }

  cout << ans << '\n';
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}
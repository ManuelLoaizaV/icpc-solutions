//https://atcoder.jp/contests/abc190/tasks/abc190_f
#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 3e5;
const Long INF = 1e18;

struct FenwickTree {
  Long tree[N + 1];
  void Clear(int n) {
    for (int i = 0; i <= n; i++) tree[i] = 0;
  }
  void Update(int i, Long delta) {
    while (i <= N) {
      tree[i] += delta;
      i += (i & -i);
    }
  }
  Long Query(int i) {
    Long sum = 0;
    while (i > 0) {
      sum += tree[i];
      i -= (i & -i);
    }
    return sum;
  }
} ft;


void Solve(void) {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i]++;
  }
  Long ans = 0;
  vector<Long> cnt(n + 1, 0);
  for (int i = n - 1; i >= 0; i--) {
    cnt[a[i]] = ft.Query(a[i]);
    ans += cnt[a[i]];
    ft.Update(a[i] + 1, 1);
  }

  ft.Clear(n);
  for (int i = 0; i < n; i++) {
    cout << ans << '\n';
    ans -= (cnt[a[i]] + ft.Query(a[i]));
    ans += (n - a[i]);
    ft.Update(a[i] + 1, 1);
  }
} 

int main(void) {
  FAST_IO;
  int t = 1;
  //cin >> t;
  while (t--) Solve();
  return 0;
}


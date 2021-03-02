//https://codeforces.com/problemset/problem/749/E
#include <bits/stdc++.h>

using namespace std;

typedef long long Long;
typedef long double Double;

const int N = 1e5;

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
    Long ans = 0;
    while (i > 0) {
      ans += tree[i];
      i -= (i & -i);
    }
    return ans;
  }
} ft;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> p(n);
  for (int i = 0; i < n; i++) cin >> p[i];
  if (n == 1) {
    cout << 0 << '\n';
    return 0;
  }
  Long inv = 0;
  for (int i = n - 1; i >= 0; i--) {
    inv += ft.Query(p[i]);
    ft.Update(p[i] + 1, 1LL);
  }
  Long delta = 0;
  for (int it = 0; it < 2; it++) {
    Long cur = 0;
    ft.Clear(n);
    for (int i = n - 1; i >= 0; i--) {
      cur += (i + 1) * ft.Query(n - p[i] + 1);
      ft.Update(n - p[i] + 1, (Long) n - i);
    }
    if (it == 0) {
      delta += cur;
    } else {
      delta -= cur;
    }
    if (it == 0) reverse(p.begin(), p.end());
  }
  Double ans = inv + (Double) delta / ((Long) n * (n + 1));
  cout << fixed << setprecision(18) << ans << '\n';
  return 0;
}
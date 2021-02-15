//https://codeforces.com/gym/316406/problem/B
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

struct Line {
  mutable Long m, b, p;
  bool operator < (const Line& other) const { return m < other.m; }
  bool operator < (Long x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
  //static const Double INF = 1/.0;
  static const Long INF = LLONG_MAX;
  //Double Div(Double a, Double b) { return a / b; }
  Long Div(Long a, Long b) { return a / b - ((a ^ b) < 0 && a % b); }
  bool Intersect(iterator x, iterator y) {
    if (y == end()) return x->p = INF, 0;
    if (x->m == y->m) {
      x->p = x->b > y->b ? INF : -INF;
    } else {
      x->p = Div(y->b - x->b, x->m - y->m);
    }
    return x->p >= y->p;
  }
  // Agregar recta de la forma mx + b
  void Add(Long m, Long b) {
    auto z = insert({m, b, 0});
    auto y = z++;
    auto x = y;
    while (Intersect(y, z)) z = erase(z);
    if (x != begin() && Intersect(--x, y)) Intersect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p) Intersect(x, erase(y));
  }
  // Obtener maximo valor en el punto x
  Long Query(Long x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.m * x + l.b;
  }
} cht;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  vector<Long> a(n), b(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i];
  vector<Long> dp(n, 0);
  vector<Long> prefix_sum(n, 0);
  prefix_sum[0] = a[0];
  for (int i = 1; i < n; i++) prefix_sum[i] = prefix_sum[i - 1] + a[i];
  cht.Add(0, 0);
  for (int i = 1; i < n; i++) {
    dp[i] = prefix_sum[i] * b[i] - cht.Query(b[i]);
    cht.Add(prefix_sum[i - 1], -dp[i]);
  }
  for (Long x : dp) cout << x << " ";
  cout << '\n';
  return 0;
}

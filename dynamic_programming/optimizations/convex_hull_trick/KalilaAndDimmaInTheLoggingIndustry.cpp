//https://codeforces.com/problemset/problem/319/C
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

// Si corto el arbol i, no tiene sentido cortar arboles anteriores por ahora
// puesto que me costaran mi valor actual y no reducire el costo de recarga.
// Sin embargo, me gustaria poder saber quien es el siguiente que me conviene
// cortar para poder eliminar todo lo anterior con el nuevo menor costo de recarga.
// Como siempre llegaremos al ultimo, todos los anteriores pendientes me costaran cero.
// De esta manera, el ultimo nos daria
// DP(n - 1) = min_{j < n - 1} (DP(j) + b_j * a_{n - 1})
// Caso base:
// DP(0) = 0
// Para cualquier otro arbol:
// DP(i) = min_{j < i} (DP(j) + b_j * a_i)
int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  vector<Long> dp(n, 0);
  vector<Long> a(n), b(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i];
  cht.Add(-b[0], 0);
  for (int i = 1; i < n; i++) {
    dp[i] = -cht.Query(a[i]);
    cht.Add(-b[i], -dp[i]);
  }
  cout << dp[n - 1] << '\n';
  return 0;
}

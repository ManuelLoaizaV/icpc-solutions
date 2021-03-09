//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=88
#include <bits/stdc++.h>
using namespace std;

typedef long long Double;

const Double INF = 1e18;
const Double N = 10;

struct Punto {
  // Para geometría 3D, añadir coordenada z, descomentar el producto cruz y comentar funciones 2D
  Double x, y, z;
  Punto(void) {}
  Punto(Double x, Double y, Double z) : x(x), y(y), z(z) {}
  Double Norm2(void) { return *this * *this; }
  Double Norm(void) { return sqrt(Norm2()); }
  bool operator == (const Punto& p) { return x == p.x && y == p.y && z == p.z; }
  bool operator != (const Punto& p) { return !(*this == p); }
  Punto operator + (const Punto& p) { return Punto(x + p.x, y + p.y, z + p.z); }
  Punto operator - (const Punto& p) { return Punto(x - p.x, y - p.y, z - p.z); }
  Punto operator * (Double k) { return Punto(x * k, y * k, z * k); }
  Punto operator / (Double k) { return Punto(x / k, y / k, z / k); }
  // Producto interno euclideano
  Double operator * (Punto p) { return x * p.x + y * p.y + z * p.z; }
//  Punto operator ^ (Punto p) { return Punto(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x); }
  Double Angle(Punto p) { return acos(*this * p / (Norm() * p.Norm())); }
  Punto Unit(void) { return *this / Norm(); }
};

const Punto BAN(0, 0, 0);

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  vector<Punto> p;
  Double x, y, z;
  while (scanf("%lld %lld %lld", &x, &y, &z) == 3) {
    Punto cur(x, y, z);
    if (cur == BAN) break;
    p.push_back(cur);
  }
  vector<int> ans(N, 0);
  int n = p.size();
  for (int i = 0; i < n; i++) {
    Double d2 = INF;
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      d2 = min(d2, (p[i] - p[j]).Norm2());
    }
    Double last = N;
    for (Double i = 0; i <= N; i++) {
      if (i * i <= d2) {
        last = i;
      } else {
        break;
      }
    }
    if (last < N) ans[last]++;
  }
  for (int i = 0; i < N; i++) printf("%4d", ans[i]);
  printf("\n");
  return 0;
}

//https://cses.fi/problemset/task/2191
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

struct Punto {
  Long x, y;

  void Read(void) {
    cin >> x >> y;
  }

  Punto operator - (const Punto& other) const {
    return Punto{x - other.x, y - other.y};
  }

  void operator -= (const Punto& other) {
    x -= other.x;
    y -= other.y;
  }

  Long operator * (const Punto& other) const {
    return (x * other.y - y * other.x);
  }

  Long Triangle(const Punto& p2, const Punto& p3) const {
    return (p2 - *this) * (p3 - *this);
  }
};

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<Punto> p(n);
  for (int i = 0; i < n; i++) p[i].Read();
  Long ans = 0;
  for (int i = 0; i < n; i++) ans += (p[i] * p[(i + 1) % n]);
  cout << abs(ans) << '\n';
  return 0;
}

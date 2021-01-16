//https://cses.fi/problemset/task/2190
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

void Solve(void) {
  Punto p[4];
  for (int i = 0; i < 4; i++) p[i].Read();
  if ((p[1] - p[0]) * (p[3] - p[2]) == 0) {
    if (p[0].Triangle(p[1], p[2]) != 0) {
      cout << "NO" << '\n';
      return;
    }
    for (int i = 0; i < 2; i++) {
      if (max(p[0].x, p[1].x) < min(p[2].x, p[3].x) || max(p[0].y, p[1].y) < min(p[2].y, p[3].y)) {
        cout << "NO" << '\n';
        return;
      }
      swap(p[0], p[2]);
      swap(p[1], p[3]);
    }
  } else {
    for (int i = 0; i < 2; i++) {
      Long cross_1 = p[0].Triangle(p[1], p[2]);
      Long cross_2 = p[0].Triangle(p[1], p[3]);
      if ((cross_1 < 0 && cross_2 < 0) || (cross_1 > 0 && cross_2 > 0)) {
        cout << "NO" << '\n';
        return;
      }
      swap(p[0], p[2]);
      swap(p[1], p[3]);
    }
  }
  cout << "YES" << '\n';
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}

//https://cses.fi/problemset/task/2192
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const Long INF = 2e9;

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

bool OnSegment(const Punto& p, const Punto& a, const Punto& b) {
  if (p.Triangle(a, b) != 0) return false;
  return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
    min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

bool Intersect(const Punto& a, const Punto& b, const Punto& c, const Punto& d) {
  Punto p[4] = {a, b, c, d};
  if ((p[1] - p[0]) * (p[3] - p[2]) == 0) {
    if (p[0].Triangle(p[1], p[2]) != 0) return false;
    for (int i = 0; i < 2; i++) {
      if (max(p[0].x, p[1].x) < min(p[2].x, p[3].x) ||
          max(p[0].y, p[1].y) < min(p[2].y, p[3].y)) {
        return false;
      }
      swap(p[0], p[2]);
      swap(p[1], p[3]);
    }
  } else {
    for (int i = 0; i < 2; i++) {
      Long cross_1 = p[0].Triangle(p[1], p[2]);
      Long cross_2 = p[0].Triangle(p[1], p[3]);
      if ((cross_1 < 0 && cross_2 < 0) ||
          (cross_1 > 0 && cross_2 > 0)) {
        return false;
      }
      swap(p[0], p[2]);
      swap(p[1], p[3]);
    }
  }
  return true;
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<Punto> points(n);
  for (int i = 0; i < n; i++) points[i].Read();
  while (m--) {
    Punto from;
    from.Read();
    Punto to;
    to.x = from.x + 1;
    to.y = INF;
    bool on_boundary = false;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
      if (OnSegment(from, points[i], points[(i + 1) % n])) {
        on_boundary = true;
        break;
      }
      if (Intersect(from, to, points[i], points[(i + 1) % n])) cnt++;
    }
    if (on_boundary) {
      cout << "BOUNDARY" << '\n';
    } else {
      if (cnt & 1) {
        cout << "INSIDE" << '\n';
      } else {
        cout << "OUTSIDE" << '\n';
      }
    }
  }
  return 0;
}

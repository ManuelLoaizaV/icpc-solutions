//https://cses.fi/problemset/task/2189
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
};

void Solve(void) {
  Punto p1, p2, p3;
  p1.Read();
  p2.Read();
  p3.Read();
  p3 -= p1;
  p2 -= p1;
  Long cross = p3 * p2;
  if (cross > 0) {
    cout << "RIGHT" << '\n';
  } else {
    if (cross < 0) {
      cout << "LEFT" << '\n';
    } else {
      cout << "TOUCH" << '\n';
    }
  }
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}

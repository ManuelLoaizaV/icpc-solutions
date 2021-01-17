//https://cses.fi/problemset/task/2193
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
    return x * other.y - y * other.x;
  }
};

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<Punto> p(n);
  for (int i = 0; i < n; i++) p[i].Read();
  Long border = 0;
  Long double_area = 0;
  for (int i = 0; i < n; i++) {
    Punto delta = p[(i + 1) % n] - p[i];
    Long intervals = __gcd(abs(delta.x), abs(delta.y));
    border += intervals;
    double_area += p[(i + 1) % n] * p[i];
  }
  double_area = abs(double_area);
  // Pick's theorem
  // A = i + b / 2 - 1
  // i = (2A - b + 2) / 2
  Long interior = (double_area - border + 2) / 2;
  cout << interior << " " << border << '\n';
  return 0;
}

#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

typedef long long Long;
typedef long double Double;

const Long INF = LLONG_MAX;

struct Punto {
  Long x, y;

  void Read(void) {
    cin >> x >> y;
  }

  void Print(void) {
    cout << x << " " << y << '\n';
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

  bool operator < (const Punto& other) const {
    if (x == other.x) return y < other.y;
    return x < other.x;
  }

  Long Triangle(const Punto& p2, const Punto& p3) const {
    return (p2 - *this) * (p3 - *this);
  }
};

Long Square(Long x) {
  return x * x;
}

Long SquareDistance(const Punto& p1, const Punto& p2) {
  return Square(p1.x - p2.x) + Square(p1.y - p2.y);
}

Long MinimumEuclideanDistance(const vector<Punto>& points) {
  int n = points.size();
  if (n == 1) return INF;
  vector<Punto> left = vector<Punto>(points.begin(), points.begin() + n / 2);
  vector<Punto> right = vector<Punto>(points.begin() + n / 2, points.end());
  Long left_distance = MinimumEuclideanDistance(left);
  Long right_distance = MinimumEuclideanDistance(right);
  Long minimum_distance = min(left_distance, right_distance);
  Long middle_x = left.back().x;
  vector<Punto> stripe;
  for (Punto p : left) if (Square(p.x - middle_x) < minimum_distance) stripe.push_back(p);
  for (Punto p : right) if (Square(p.x - middle_x) < minimum_distance) stripe.push_back(p);
  sort(stripe.begin(), stripe.end(), [&](const Punto& p1, const Punto& p2) {
      return p1.y < p2.y; });
  int len = stripe.size();
  for (int i = 0; i < len; i++) {
    for (int j = i + 1; j < len && Square(stripe[j].y - stripe[i].y) < minimum_distance; j++) {
      minimum_distance = min(minimum_distance, SquareDistance(stripe[j], stripe[i]));
    }
  }
  return minimum_distance;
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<Punto> points(n);
  for (int i = 0; i < n; i++) points[i].Read();
  sort(points.begin(), points.end());
  Long ans = MinimumEuclideanDistance(points);
  cout << ans << '\n';
  return 0;
}

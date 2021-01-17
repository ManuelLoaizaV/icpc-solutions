//https://cses.fi/problemset/task/2195
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

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

vector<Punto> ConvexHull(vector<Punto>& p) {
  int n = p.size();
  vector<Punto> ch;
  sort(p.begin(), p.end());
  for (int it = 0; it < 2; it++) {
    int sz = ch.size();
    for (int i = 0; i < n; i++) {
      while (ch.size() >= (sz + 2) &&
          ch.end()[-2].Triangle(ch.end()[-1], p[i]) > 0) {
        ch.pop_back();
      }
      ch.push_back(p[i]);
    }
    reverse(p.begin(), p.end());
    ch.pop_back();
  }
  return ch;
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<Punto> p(n);
  for (int i = 0; i < n; i++) p[i].Read();
  vector<Punto> ch = ConvexHull(p);
  int len = ch.size();
  cout << len << '\n';
  for (int i = 0; i < len; i++) ch[i].Print();
  return 0;
}

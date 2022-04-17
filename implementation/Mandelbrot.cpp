#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef long double Double;

const Double EPS = 1e-9;

struct Complex {
  Double x, y;
  Complex(Double _x, Double _y) : x(_x), y(_y) {}
  Complex operator+(const Complex& other) const {
    return Complex(x + other.x, y + other.y);
  }
  Complex operator*(const Complex& other) const {
    return Complex(x * other.x - y * other.y, x * other.y + y * other.x);
  }
  Double SquareNorm(void) {
    return x * x + y * y;
  }
};

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Double x, y;
  Long r;
  int test_case = 0;
  while (cin >> x >> y >> r) {
    test_case++;
    cout << "Case " << test_case << ": ";
    Complex c(x, y);
    Complex z(0, 0);
    bool diverges = false;
    for (int i = 0; i < r; i++) {
      z = z * z + c;
      Double square_norm = z.SquareNorm();
      if (square_norm > 4.0 + EPS) {
        diverges = true;
        break;
      }
    }
    if (diverges) {
      cout << "OUT" << '\n';
    } else {
      cout << "IN" << '\n';
    }
  }
  return 0;
}
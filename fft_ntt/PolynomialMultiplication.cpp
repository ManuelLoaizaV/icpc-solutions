//https://www.spoj.com/problems/POLYMUL/
#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;
typedef long double Double;
typedef complex<Double> Complex;
typedef vector<Long> Polynomial;

const Double PI = acos(-1);

vector<Complex> DFT(vector<Complex>& a, bool is_inverse) {
  int n = a.size();
  if (n == 1) return a;
  Double teta = 2 * PI / n;
  if (is_inverse) teta *= (-1);
  Complex w_n(cos(teta), sin(teta));
  Complex w = 1;
  vector<Complex> a_0(n / 2), a_1(n / 2);
  for (int i = 0; i < n / 2; i++) {
    a_0[i] = a[2 * i];
    a_1[i] = a[2 * i + 1];
  }
  vector<Complex> y_0 = DFT(a_0, is_inverse);
  vector<Complex> y_1 = DFT(a_1, is_inverse);
  vector<Complex> y(n);
  for (int i = 0; i < n / 2; i++) {
    y[i] = y_0[i] + w * y_1[i];
    y[i + n / 2] = y_0[i] - w * y_1[i];
    w *= w_n;
  }
  return y;
}

Polynomial operator * (Polynomial& a, Polynomial& b) {
  int n = a.size();
  int m = b.size();
  int mx = max(n, m);
  int len = 1;
  while (len < mx) len *= 2;
  vector<Complex> complex_a(2 * len, 0);
  for (int i = 0; i < n; i++) complex_a[i] = a[i];
  vector<Complex> complex_b(2 * len, 0);
  for (int i = 0; i < m; i++) complex_b[i] = b[i];
  // Evaluation in O(n lg(n))
  vector<Complex> dft_a = DFT(complex_a, false);
  vector<Complex> dft_b = DFT(complex_b, false);
  // Pointwise multiplication in O(n)
  vector<Complex> dft_c(2 * len);
  for (int i = 0; i < p; i++) dft_c[i] = dft_a[i] * dft_b[i];
  // Interpolation in O(n lg(n))
  vector<Complex> inverse = DFT(dft_c, true);
  Polynomial c(2 * len);
  for (int i = 0; i < 2 * len; i++) c[i] = round(inverse[i].real()) / p;
  return c;
}

void Solve(void) {
  int n;
  cin >> n;
  Polynomial a(n + 1), b(n + 1);
  for (int i = 0; i <= n; i++) cin >> a[i];
  for (int i = 0; i <= n; i++) cin >> b[i];
  Polynomial c = a * b;
  for (int i = 0; i <= 2 * n; i++) cout << c[i] << " ";
  cout << '\n';
}

int main(void) {
  FAST_IO;
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}

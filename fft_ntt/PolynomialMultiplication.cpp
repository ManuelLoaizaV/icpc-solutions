//https://www.spoj.com/problems/POLYMUL/en/
#include <bits/stdc++.h>

using namespace std;

typedef long long Long;
typedef long double Double;
typedef complex<Double> Complex;
typedef vector<Long> Polynomial;
const Double PI = acos(-1);

void FFT(vector<Complex>& a, bool is_inverse) {
  int n = a.size();
  if (n == 1) return;
  Double teta = 2 * PI / n;
  if (is_inverse) teta *= (-1);
  Complex w_n(cos(teta), sin(teta));
  Complex w = 1;
  vector<Complex> a_0(n / 2), a_1(n / 2);
  for (int i = 0; i < n / 2; i++) {
    a_0[i] = a[2 * i];
    a_1[i] = a[2 * i + 1];
  }
  FFT(a_0, is_inverse);
  FFT(a_1, is_inverse);
  for (int i = 0; i < n / 2; i++) {
    a[i] = a_0[i] + w * a_1[i];
    a[i + n / 2] = a_0[i] - w * a_1[i];
    w *= w_n;
  }
}

Polynomial operator * (Polynomial& a, Polynomial& b) {
  int n = a.size();
  int m = b.size();
  int mx = max(n, m);
  int len = 1;
  while (len < mx) len *= 2;
  vector<Complex> dft_a(2 * len, 0);
  for (int i = 0; i < n; i++) dft_a[i] = a[i];
  vector<Complex> dft_b(2 * len, 0);
  for (int i = 0; i < m; i++) dft_b[i] = b[i];
  // Evaluation in O(n lg(n))
  FFT(dft_a, false);
  FFT(dft_b, false);
  // Pointwise multiplication in O(n)
  vector<Complex> dft_c(2 * len);
  for (int i = 0; i < 2 * len; i++) dft_c[i] = dft_a[i] * dft_b[i];
  // Interpolation in O(n lg(n))
  FFT(dft_c, true);
  Polynomial c(2 * len);
  for (int i = 0; i < 2 * len; i++) c[i] = round(dft_c[i].real() / (2 * len));
  return c;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    Polynomial a(n + 1), b(n + 1);
    for (int i = 0; i <= n; i++) cin >> a[i];
    for (int i = 0; i <= n; i++) cin >> b[i];
    Polynomial c = a * b;
    for (int i = 0; i <= 2 * n; i++) {
      if (i > 0) cout << " ";
      cout << c[i];
    }
    cout << '\n';
  }
  return 0;
}
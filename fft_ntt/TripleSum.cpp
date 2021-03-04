//https://www.spoj.com/problems/TSUM/en/
#include <bits/stdc++.h>

using namespace std;

typedef long long Long;
typedef long double Double;
//typedef complex<Double> Complex;
typedef vector<Long> Polynomial;

const int MAX_N = (int) 2e4;
const int N = (int) 4e4;
const Double PI = acos(-1);

struct Complex {
  Double r, i;
  Complex(Double _r = 0, Double _i = 0) : r(_r), i(_i) {}
  Double real(void) const { return r; }
};

Complex operator + (const Complex& a, const Complex& b) {
  return Complex(a.r + b.r, a.i + b.i);
}

Complex operator - (const Complex& a, const Complex& b) {
  return Complex(a.r - b.r, a.i - b.i);
}

Complex operator * (const Complex& a, const Complex& b) {
  return Complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);
}

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
    w = w * w_n;
  }
}

Polynomial operator * (Polynomial& a, Polynomial& b) {
  int n = a.size();
  int m = b.size();
  int sum = n + m;
  int len = 1;
  while (len < sum) len *= 2;
  vector<Complex> dft_a(len, 0);
  for (int i = 0; i < n; i++) dft_a[i] = a[i];
  vector<Complex> dft_b(len, 0);
  for (int i = 0; i < m; i++) dft_b[i] = b[i];
  // Evaluation in O(n lg(n))
  FFT(dft_a, false);
  FFT(dft_b, false);
  // Pointwise multiplication in O(n)
  vector<Complex> dft_c(len);
  for (int i = 0; i < len; i++) dft_c[i] = dft_a[i] * dft_b[i];
  // Interpolation in O(n lg(n))
  FFT(dft_c, true);
  Polynomial c(sum - 1);
  for (int i = 0; i < sum - 1; i++) c[i] = round(dft_c[i].real() / len);
  return c;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> s(n);
  for (int i = 0; i < n; i++) cin >> s[i];
  for (int i = 0; i < n; i++) s[i] += MAX_N;
  Polynomial one_element(N + 1, 0LL);
  for (int i = 0; i < n; i++) one_element[s[i]]++;
  Polynomial two_elements = one_element * one_element;
  for (int i = 0; i < n; i++) two_elements[2 * s[i]]--;
  for (int i = 0; i <= 2 * N; i++) two_elements[i] /= 2;
  Polynomial three_elements = two_elements * one_element;
  Polynomial double_one_element(2 * N + 1, 0LL);
  for (int i = 0; i < n; i++) double_one_element[2 * s[i]]++;
  Polynomial two_cross_one = double_one_element * one_element;
  for (int i = 0; i < n; i++) {
    two_cross_one[3 * s[i]]--;
  }
  for (int i = 0; i <= 3 * N; i++) three_elements[i] -= two_cross_one[i];
  for (int i = 0; i <= 3 * N; i++) {
    if (three_elements[i] > 0) {
      int value = i - 3 * MAX_N;
      cout << value << " : " << three_elements[i] / 3 << '\n';
    }
  }
  return 0;
}
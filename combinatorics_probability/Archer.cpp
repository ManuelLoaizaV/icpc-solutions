#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;
typedef long double Double;

const int N = 1e6;

int main(void) {
  FAST_IO;
  Long a, b, c, d;
  cin >> a >> b >> c >> d;
  Double p = (Double) a / b;
  Double q = (Double) c / d;
  Double ans = 0.0;
  Double mul = 1.0;
  for (int i = 0; i < N; i++) {
    ans += p * mul;
    mul *= (1.0 - p) * (1.0 - q);
  }
  cout << fixed << setprecision(12) << ans << '\n';
  return 0;
}

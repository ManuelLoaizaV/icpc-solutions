#include <algorithm>
#include <iostream>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;

Long Phi(Long n) {
  Long ans = n;
  for (Long i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      while (n % i == 0) n /= i;
      ans -= ans / i;
    }
  }
  if (n > 1) ans -= ans / n;
  return ans;
}

void Solve(void) {
  Long a, m;
  cin >> a >> m;
  Long g = __gcd(a, m);
  cout << Phi(m / g) << '\n';
}

int main(void) {
  FAST_IO;
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}

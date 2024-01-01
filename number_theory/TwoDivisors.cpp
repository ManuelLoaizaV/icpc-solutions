// https://codeforces.com/contest/1916/problem/B
#include <bits/stdc++.h>

#define debug(x) cout << #x << " = " << x << endl

using namespace std;

typedef long long Long;
typedef long double Double;

const Long INF = 1e18;
const Long MOD = 998244353LL;
const char ENDL = '\n';
const string YES = "YES";
const string NO = "NO";

bool IsPrime(Long n) {
  if (n == 1) return false;
  if (n == 2) return true;
  if (n % 2 == 0) return false;
  for (Long d = 3; d * d <= n; d += 2LL) {
    if (n % d == 0) return false;
  }
  return true;
}

void Solve(void) {
  Long m, M;
  cin >> m >> M;
  if (m == 1LL) {
    cout << M * M << ENDL;
    return;
  }
  // If the smallest prime appears at least twice
  Long p = M / m;
  if (p * m == M && IsPrime(p)) {
    Long x = p * M;
    cout << x << ENDL;
    return;
  }
  Long g = __gcd(m, M);
  p = m / g;
  Long x = p * M;
  cout << x << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}

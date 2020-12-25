#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long Long;

const int N = 2e5;

int fact[N + 1];
vector<int> exponent[N + 1];

void Sieve(void) {
  for (int i = 0; i <= N; i++) fact[i] = i;
  for (int i = 2; i * i <= N; i++) {
    if (fact[i] == i) for (int j = i * i; j <= N; j += i) fact[j] = i;
  }
}

Long FastPow(Long a, Long b) {
  if (b == 0) return 1LL;
  Long ans = FastPow(a, b / 2);
  ans *= ans;
  if (b & 1) ans *= a;
  return ans;
}

int main(void) {
  Sieve();
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    if (a == 1) continue;
    while (a > 1) {
      int p = fact[a];
      int cnt = 0;
      while (a % p == 0) {
        a /= p;
        cnt++;
      }
      exponent[p].push_back(cnt);
    }
  }
  Long ans = 1LL;
  for (Long i = 2; i <= N; i++) {
    if (exponent[i].size() <= n - 2) continue;
    sort(exponent[i].begin(), exponent[i].end());
    if (exponent[i].size() == n - 1) {
      ans *= FastPow(i, exponent[i][0]);
    } else {
      ans *= FastPow(i, exponent[i][1]);
    }
  } 
  cout << ans << '\n';
  return 0;
}

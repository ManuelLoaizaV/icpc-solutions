#include <iostream>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

const int N = 1e6;
const Long MOD = 1e9 + 7;

Long fact[2 * N + 1];
Long factor[N + 1];

Long Sum(Long a, Long b) {
  return (a + b) % MOD;
}

Long Mul(Long a, Long b) {
  return (a * b) % MOD;
}

void Precalculate(void) {
  fact[0] = 1LL;
  for (Long i = 1; i <= 2 * N; i++) fact[i] = Mul(fact[i - 1], i);
}

void Sieve(void) {
  for (Long i = 0; i <= N; i++) factor[i] = i;
  for (Long i = 2; i * i <= N; i++) {
    if (factor[i] == i) {
      for (Long j = i * i; j <= N; j += i) {
        factor[j] = i;
      }
    }
  }
}

Long FastPow(Long a, Long b) {
  if (b == 0) return 1LL;
  Long ans = FastPow(a, b / 2);
  ans = Mul(ans, ans);
  if (b & 1) ans = Mul(ans, a);
  return ans;
}

Long ModularInverse(Long n) {
  return FastPow(n, MOD - 2);
}

Long nCk(Long n, Long k) {
  Long num = fact[n];
  Long den = Mul(fact[k], fact[n - k]);
  return Mul(num, ModularInverse(den));
}

vector<Pair> Factorize(Long n) {
  vector<Pair> ans;
  while (n > 1) {
    Long p = factor[n];
    Long cnt = 0;
    while (n % p == 0) {
      cnt++;
      n /= p;
    }
    ans.push_back({p, cnt});
  }
  return ans;
}

void Solve(void) {
  Long x, y;
  cin >> x >> y;
  Long ans = 1LL;
  if (x == 1) {
    ans = FastPow(2LL, y - 1);
  } else {
    auto primes = Factorize(x);
    for (auto p : primes) {
      ans = Mul(ans, nCk(p.second + y - 1, y - 1));
    }
    ans = Mul(ans, FastPow(2LL, y - 1));
  }
  cout << ans << '\n';
}

int main(void) {
  FAST_IO;
  Precalculate();
  Sieve();
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}

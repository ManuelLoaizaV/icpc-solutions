// https://cses.fi/problemset/task/1636/
#include <bits/stdc++.h>
#include <cassert>
using namespace std;

// Modular integer for automatic mod operations.
// This version of inv() requires the modulus M to be prime.
template<long long M>
struct Mint {
  long long v;
  Mint() { v = 0LL; }
  // Normalizes any value into range [0, M).
  Mint(long long _v) {
    v = (-M < _v && _v < M) ? _v : _v % M;
    if (v < 0) v += M; // Ensure non-negative value
  }
  explicit operator long long() const { return v; }
  friend bool operator==(const Mint &a, const Mint &b) { return a.v == b.v; }
  friend bool operator!=(const Mint &a, const Mint &b) { return !(a == b); }
  friend bool operator<(const Mint &a, const Mint &b) { return a.v < b.v; }
  Mint &operator+=(const Mint &m) { if ((v += m.v) >= M) v -= M; return *this; }
  Mint &operator-=(const Mint &m) { if ((v -= m.v) < 0) v += M; return *this; }
  Mint &operator*=(const Mint &m) { v = v * m.v % M; return *this; }
  Mint &operator/=(const Mint &m) { return (*this) *= inv(m); }
  Mint operator-() const { return Mint(-v); }
  Mint &operator++() { return *this += 1; }
  Mint &operator--() { return *this -= 1; }
  Mint operator++(int) { Mint old = *this; ++*this; return old; }
  Mint operator--(int) { Mint old = *this; --*this; return old; }
  friend Mint operator+(Mint a, const Mint &b) { return a += b; }
  friend Mint operator-(Mint a, const Mint &b) { return a -= b; }
  friend Mint operator*(Mint a, const Mint &b) { return a *= b; }
  friend Mint operator/(Mint a, const Mint &b) { return a /= b; }
  // Returns a^n % M. Time complexity: O(lg n).
  friend Mint pow(Mint a, long long n) { Mint p = 1LL; for (; n > 0LL; n >>= 1LL, a *= a) if (n & 1LL) p *= a; return p; }
  // Returns modular inverse via Fermat's little theorem. Time complexity: O(lg M).
  // If M is composite, gcd(a.v,M)==1 and replace this with extended Euclidean algorithm.
  friend Mint inv(const Mint &a) { assert(a.v != 0LL); return pow(a, M - 2LL); }
  friend ostream &operator<<(ostream &os, const Mint &m) { return os << m.v; }
  friend istream &operator>>(istream &is, Mint &m) { long long x; is >> x; m = Mint(x); return is; }
};
using mint = Mint<1000000007LL>;
// using mint = Mint<998244353LL>;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, x;
  cin >> n >> x;
  vector<int> coins(n);
  for (int i = 0; i < n; i++) {
    cin >> coins[i];
  }
  sort(coins.begin(), coins.end());
  vector<vector<mint>> dp(2, vector<mint>(x + 1, 0LL));
  dp[0][0] = dp[1][0] = 1LL;
  for (int i = n - 1; i >= 0; i--) {
    for (int j = coins[i]; j <= x; j++) {
      dp[0][j] = dp[1][j] + dp[0][j - coins[i]];
    }
    dp[1] = dp[0];
  }
  cout << dp[1][x] << endl;
  return 0;
}
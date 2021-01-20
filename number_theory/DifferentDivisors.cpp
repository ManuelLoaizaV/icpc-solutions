//https://codeforces.com/contest/1474/problem/B
#include <bits/stdc++.h>
#include <unistd.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define all(v) (v).begin(),(v).end()
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 1e6;
const Long INF = 1e18;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

bool is_prime[N + 1];

void Sieve(void) {
  for (int i = 0; i <= N; i++) is_prime[i] = true;
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i * i <= N; i++) {
    if (is_prime[i]) {
      for (int j = i * i; j <= N; j += i) is_prime[j] = false;
    }
  }
}

void Solve(void) {
  Long d;
  cin >> d;
  Long a, b;
  Long cur = 1 + d;
  while (true) {
    if (is_prime[cur]) {
      a = cur;
      break;
    }
    cur++;
  }
  cur = a + d;
  while (true) {
    if (is_prime[cur]) {
      b = cur;
      break;
    }
    cur++;
  }
  Long ans = a * b;
  cout << ans << '\n';
}

int main(void) {
  FAST_IO;
  Sieve();
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}


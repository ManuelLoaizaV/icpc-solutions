//https://codeforces.com/problemset/problem/510/D
//#pragma GCC optimize ("Ofast,unroll-loops")
//#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include <unistd.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 300;
const int M = 1 << 10;
const Long INF = 1e18;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

int n;
vector<Long> a;
vector<Long> cost;

vector<Long> GetPrimes(Long num) {
  vector<Long> result;
  if (num % 2 == 0) {
    result.push_back(2);
    while (num % 2 == 0) num /= 2;
  }
  for (Long i = 3; i * i <= num; i += 2) {
    if (num % i == 0) {
      result.push_back(i);
      while (num % i == 0) num /= i;
    }
  }
  if (num > 1) result.push_back(num);
  return result;
}

Long current_pos, full_mask;
vector<set<Long>> primes;
Long dp[N][M];
bool done[N][M];

// DP(pos, mask) = minimo costo para obtener gcd igual a 1 con los numeros del
// intervalo [pos .. n - 1] con una mascara mask, donde un bit prendido en mask
// significa que existe un numero que no tiene dicho factor

void TurnOn(int& mask, int bit) {
  mask = mask | (1 << bit);
}

Long DP(int pos, int mask) {
  if (mask == full_mask) return 0;
  if (pos == n) return INF;
  if (done[pos][mask]) return dp[pos][mask];
  dp[pos][mask] = DP(pos + 1, mask);
  if (pos != current_pos) {
    int new_mask = mask;
    int bit = 0;
    for (int prime : primes[current_pos]) {
      if (primes[pos].count(prime) == 0) TurnOn(new_mask, bit);
      bit++;
    }
    dp[pos][mask] = min(dp[pos][mask], cost[pos] + DP(pos + 1, new_mask));
  }
  done[pos][mask] = true;
  return dp[pos][mask];
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  a = vector<Long>(n);
  cost = vector<Long>(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> cost[i];
  // Hallo los factores primos de cada numero
  for (int i = 0; i < n; i++) {
    set<Long> new_primes;
    if (a[i] != 1) {
      vector<Long> current_primes = GetPrimes(a[i]);
      for (Long prime : current_primes) new_primes.insert(prime);
    }
    primes.push_back(new_primes);
  }
  Long result = INF;
  for (int i = 0; i < n; i++) {
    if (a[i] == 1) {
      result = min(result, cost[i]);
    } else {
      current_pos = i;
      full_mask = (1 << ((int) primes[i].size())) - 1;
      // Limpio el DP
      for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < full_mask; mask++) {
          done[i][mask] = false;
        }
      }
      result = min(result, cost[i] + DP(0, 0));
    }
  }
  if (result < INF) {
    cout << result << '\n';
  } else {
    cout << -1 << '\n';
  }
  return 0;
}

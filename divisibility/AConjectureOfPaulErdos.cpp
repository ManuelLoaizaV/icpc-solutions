// https://www.spoj.com/problems/HS08PAUL/
#include <bits/stdc++.h>
#include <cassert>
using namespace std;

const int N = 10000000;
bool erdos[N + 1];
int cnt[N + 1];

vector<int> smallest_factor;
vector<bool> prime;
vector<int> primes;

// Computes primes, smallest prime factors and prime flags up to N.
// Time complexity: O(N lg lg N).
void Sieve(int maximum) {
  maximum = std::max(maximum, 1);
  smallest_factor.assign(maximum + 1, 0);
  prime.assign(maximum + 1, true);
  prime[0] = prime[1] = false;
  primes = {};
  for (int p = 2; p <= maximum; p++) {
    if (prime[p]) {
      smallest_factor[p] = p;
      primes.push_back(p);
      for (int64_t m = int64_t(p) * p; m <= maximum; m += p) {
        if (prime[m]) {
          prime[m] = false;
          smallest_factor[m] = p;
        }
      }
    }
  }
}

// Returns true if n is prime, false otherwise.
// Time complexity: O(1) if n <= N, O(sqrt n) otherwise.
bool IsPrime(int64_t n) {
  int64_t sieve_max = int64_t(smallest_factor.size()) - 1;
  assert(1 <= n && n <= sieve_max * sieve_max);
  if (n <= sieve_max)
    return prime[n];
  for (int64_t p : primes) {
    if (p * p > n)
      break;
    if (n % p == 0)
      return false;
  }
  return true;
}

// Returns the prime factorization of n as a vector of (prime, exponent) pairs.
// Time complexity: O(lg n) if n <= N, O(sqrt n) otherwise.
template <typename T> vector<pair<T, int>> PrimeFactorize(T n) {
  int64_t sieve_max = int64_t(smallest_factor.size()) - 1;
  assert(1 <= n && n <= sieve_max * sieve_max);
  vector<pair<T, int>> factors;
  if (n <= sieve_max) {
    while (n != 1) {
      int p = smallest_factor[n];
      int exponent = 0;
      do {
        n /= p;
        exponent++;
      } while (n % p == 0);
      factors.emplace_back(p, exponent);
    }
    return factors;
  }
  for (int64_t p : primes) {
    if (p * p > n)
      break;
    if (n % p != 0)
      continue;
    int exponent = 0;
    do {
      n /= p;
      exponent++;
    } while (n % p == 0);
    factors.emplace_back(p, exponent);
  }
  if (n > 1)
    factors.emplace_back(n, 1);
  return factors;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;

    Sieve(N);

    for (int i = 0; i <= N; i++) {
        erdos[i] = false;
    }

    int i = 1;
    while (true) {
        int y4 = i * i * i * i;
        if (y4 > N) break;
        int j = 1;
        while (true) {
            int x2 = j * j;
            int p = y4 + x2;
            if (p > N) break;
            if (prime[p]) erdos[p] = true;
            j++;
        }
        i++;
    }

    cnt[0] = 0;
    for (int i = 1; i <= N; i++) {
        cnt[i] = cnt[i - 1] + erdos[i];
    }

    while (t--) {
        int n;
        cin >> n;
        cout << cnt[n] << endl;
    }
    return 0;
}
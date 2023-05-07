// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1252
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

const int N = 1e8;
bool is_prime[N + 1];
vector<int> primes;

void Sieve(int n) {
  for (int i = 0; i <= n; i++) is_prime[i] = true;
  is_prime[0] = is_prime[1] = false;
  for (int p = 2; p * p <= n; p++) {
    for (int c = p * p; c <= n; c += p) {
      is_prime[c] = false;
    }
  }
  for (int i = 0; i <= n; i++) {
    if (is_prime[i]) primes.push_back(i);
  }
}

int FindLastPrimeIndex(int n) {
  int l = 0;
  int r = (int)primes.size() - 1;
  // FFFF
  if (primes[l] > n) return -1;
  // TTTT
  if (primes[r] <= n) return r;
  // TTTFFF
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (primes[m] <= n) {
      l = m;
    } else {
      r = m;
    }
  }
  return l;
}

void Solve(int n) {
  pair<int, int> solution;
  bool possible = false;
  if (n > 3) {
    if (n & 1) {
      if (is_prime[n - 2]) {
        solution = make_pair(2, n - 2);
        possible = true;
      }
    } else {
      int last_prime_index = FindLastPrimeIndex(n / 2);
      for (int i = last_prime_index; i >= 0; i--) {
        int p = primes[i];
        int q = n - p;
        if (p == q) continue;
        if (is_prime[q]) {
          solution = make_pair(p, q);
          possible = true;
          break;
        }
      }
    }
  }
  if (possible) {
    cout << n << " is the sum of " << solution.first << " and "
         << solution.second << "." << endl;
  } else {
    cout << n << " is not the sum of two primes!" << endl;
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Sieve(N);
  int n;
  while (cin >> n) Solve(n);
  return 0;
}
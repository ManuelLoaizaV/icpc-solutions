// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1793
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 1e4;

bool is_prime[MAX_N + 1];
vector<int> primes;

void Sieve(int n) {
  for (int i = 0; i <= n; i++) is_prime[i] = true;
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i * i <= n; i++) {
    if (is_prime[i]) {
      for (int j = i * i; j <= n; j += i) {
        is_prime[j] = false;
      }
    }
  }
  for (int i = 0; i <= n; i++) {
    if (is_prime[i]) {
      primes.push_back(i);
    }
  }
}

void Solve(void) {
  int n;
  cin >> n;
  int from = upper_bound(primes.begin(), primes.end(), n / 2) - primes.begin();
  cout << primes[from] << endl;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Sieve(MAX_N);
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
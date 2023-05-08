// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1889
#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 1e6;
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

void Solve(int n) {
    cout << n << ":" << endl;
    pair<int, int> result = make_pair(-1, -1);
    for (int prime : primes) {
        if (2 * prime > n) {
            break;
        }
        int missing = n - prime;
        if (is_prime[missing]) {
            result = make_pair(prime, missing);
            break;
        }
    }
    if (result.first == -1) {
        cout << "NO WAY!" << endl;
        return;
    }
    cout << result.first << "+" << result.second << endl;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Sieve(MAX_N);
  int n;
  while (cin >> n) {
    if (n == 0) break;
    Solve(n);
  }
  return 0;
}
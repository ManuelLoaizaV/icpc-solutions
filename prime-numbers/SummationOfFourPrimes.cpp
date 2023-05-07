// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1109
#include <iostream>
#include <vector>
using namespace std;

const int N = 1e7;
bool is_prime[N + 1];
vector<int> primes;

void Sieve(int n) {
  for (int i = 0; i <= n; i++) is_prime[i] = true;
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i * i <= n; i++) {
    for (int j = i * i; j <= n; j += i) {
      is_prime[j] = false;
    }
  }
  for (int i = 0; i <= n; i++) {
    if (is_prime[i]) primes.push_back(i);
  }
}

void SumOfTwoPrimes(int n) {
  for (int p : primes) {
    if (2 * p > n) break;
    int q = n - p;
    if (is_prime[q]) {
      cout << p << " " << q << endl;
      break;
    }
  }
}

void SumOfFourPrimes(int n) {
  if (n < 8) {
    cout << "Impossible." << endl;
    return;
  }
  if (n & 1) {
    cout << "2 3 ";
    n -= 5;
  } else {
    cout << "2 2 ";
    n -= 4;
  }
  SumOfTwoPrimes(n);
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Sieve(N);
  int n;
  while (cin >> n) SumOfFourPrimes(n);
  return 0;
}
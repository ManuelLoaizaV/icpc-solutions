// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1335
#include <iostream>
#include <vector>
using namespace std;

const int N = 2e7;

bool is_prime[N + 1];
vector<int> primes;
vector<int> twin_indexes;

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

void FindTwinIndexes(void) {
  int n_primes = (int)primes.size();
  for (int i = 0; i < n_primes - 1; i++) {
    if (primes[i + 1] == primes[i] + 2) {
      twin_indexes.push_back(i);
    }
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Sieve(N);
  FindTwinIndexes();
  int index;
  while (cin >> index) {
    int prime = primes[twin_indexes[index - 1]];
    cout << "(" << prime << ", " << prime + 2 << ")" << endl;
  }
  return 0;
}

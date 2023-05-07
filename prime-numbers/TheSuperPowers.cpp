// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2852
#include <cmath>
#include <iostream>
#include <set>

using namespace std;

typedef unsigned long long Long;
typedef long double Double;

const Long MAX_BASE = 1LL << 16;
const int MAX_EXPONENT = 64;
bool is_prime[MAX_EXPONENT + 1];

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
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Sieve(MAX_EXPONENT);

  set<Long> powers;
  powers.insert(1LL);

  for (Long base = 2LL; base < MAX_BASE; base++) {
    const Double upper_bound = 64.0L * log(2) / log(base);
    Long power = 1LL;
    Long previous_exponent = 0;
    for (Long exponent = 4LL; exponent < upper_bound; exponent++) {
      while (previous_exponent < exponent) {
        power *= base;
        previous_exponent++;
      }
      if (is_prime[exponent]) continue;
      powers.insert(power);
    }
  }

  for (auto power : powers) {
    cout << power << endl;
  }
  return 0;
}
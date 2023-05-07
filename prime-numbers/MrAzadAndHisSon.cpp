// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1431
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

typedef long long Long;

const Long N = 46341;
const Long MAX_EXPONENT = 31;

Long powers_of_two[MAX_EXPONENT + 1];
bool is_prime[N + 1];
unordered_set<Long> mersenne_primes;
vector<Long> primes;
vector<Long> perfects;

void Sieve(Long n) {
  for (Long i = 0; i <= n; i++) is_prime[i] = true;
  is_prime[0] = is_prime[1] = false;
  for (Long i = 2; i * i <= n; i++) {
    for (Long j = i * i; j <= n; j += i) {
      is_prime[j] = false;
    }
  }
  for (Long i = 0; i <= n; i++) {
    if (is_prime[i]) primes.push_back(i);
  }
}

bool IsPrime(Long n) {
  if (n <= N) return is_prime[n];
  for (Long prime : primes) {
    if (prime * prime > n) break;
    if (n % prime == 0) return false;
  }
  return true;
}

void Perfects(Long max_exponent) {
  perfects.push_back(-1);
  powers_of_two[0] = 1LL;
  for (Long exponent = 1; exponent <= max_exponent; exponent++) {
    powers_of_two[exponent] = 2LL * powers_of_two[exponent - 1];
    perfects.push_back(powers_of_two[exponent - 1] *
                       (powers_of_two[exponent] - 1LL));
  }
}

void MersennePrimes(Long max_exponent) {
  for (Long exponent = 1; exponent <= max_exponent; exponent++) {
    Long possible_mersenne_prime = powers_of_two[exponent] - 1;
    if (IsPrime(possible_mersenne_prime)) {
      mersenne_primes.insert(possible_mersenne_prime);
    }
  }
}

void Solve(Long n) {
  Long possible_mersenne_prime = powers_of_two[n] - 1;
  if (mersenne_primes.count(possible_mersenne_prime) > 0) {
    cout << "Perfect: " << perfects[n] << "!" << endl;
  } else {
    if (IsPrime(n)) {
      cout << "Given number is prime. But, NO perfect number is available."
           << endl;
    } else {
      cout << "Given number is NOT prime! NO perfect number is available."
           << endl;
    }
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Sieve(N);
  Perfects(MAX_EXPONENT);
  MersennePrimes(MAX_EXPONENT);
  int n;
  while (cin >> n) {
    if (n == 0) break;
    Solve(n);
  }
  return 0;
}
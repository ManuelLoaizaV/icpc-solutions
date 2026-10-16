// https://leetcode.com/problems/count-primes/description/
#include <bits/stdc++.h>
#include <cassert>
using namespace std;

class Solution {
public:
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

    int countPrimes(int n) {
        Sieve(n);
        int cnt{0};
        for (int i = 2; i < n; i++) {
            if (IsPrime(i)) {
                cnt++;
            }
        }
        return cnt;
    }
};
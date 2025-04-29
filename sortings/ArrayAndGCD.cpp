// https://codeforces.com/contest/2104/problem/D
#include <algorithm>
#include <iostream>
#include <vector>

const int N = 6000000;
bool is_prime[N + 1];
std::vector<long long> primes;

void Sieve(void) {
    for (int i = 2; i <= N; ++i) {
        is_prime[i] = true;
    }
    for (int i = 2; i * i <= N; ++i) {
        for (int j = i * i; j <= N; j += i) {
            is_prime[j] = false;
        }
    }
    for (int i = 2; i <= N; ++i) {
        if (is_prime[i]) {
            primes.push_back((long long)i);
        }
    }
}

void Solve(void) {
    int n;
    std::cin >> n;
    std::vector<long long> a(n);
    for (auto& e : a) std::cin >> e;
    std::sort(a.begin(), a.end());
    int cnt{0};
    long long a_suffix{0LL};
    long long primes_prefix{0LL};
    for (int i = 0; i < n; ++i) {
        a_suffix += a[n - 1 - i];
        primes_prefix += primes[i];
        if (a_suffix >= primes_prefix) {
            ++cnt;
        } else {
            break;
        }
    }
    std::cout << n - cnt << std::endl;
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    Sieve();
    int t;
    std::cin >> t;
    while (t--) Solve();
    return 0;
}
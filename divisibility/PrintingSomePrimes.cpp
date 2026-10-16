// https://www.spoj.com/problems/TDPRIMES/
#include <bits/stdc++.h>
#include <cassert>
using namespace std;

const int N = 100000000;

bool prime[N + 1];

void Sieve() {
  memset(prime, true, N);
  prime[0] = prime[1] = false;
  for (int p = 2; p * p <= N; p++) {
    if (prime[p]) {
      for (int64_t m = int64_t(p) * p; m <= N; m += p) {
        prime[m] = false;
      }
    }
  }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Sieve();
    int cnt = 0;
    for (int i = 2; i <= N; i++) {
        if (prime[i]) {
            cnt++;
            if (cnt >= 100) {
                cnt -= 100;
            }
            if (cnt == 1) {
                cout << i << endl;
            }
        }
    }
    return 0;
}
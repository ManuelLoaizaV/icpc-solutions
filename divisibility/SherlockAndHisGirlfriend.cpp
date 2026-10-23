// https://codeforces.com/problemset/problem/776/B
#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

bool prime[N + 1];

void Sieve() {
  memset(prime, true, N + 1);
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
    int n;
    cin >> n;
    if (n <= 2) {
        cout << 1 << endl;
        for (int i = 0; i < n; i++) {
            if (i > 0) cout << " ";
            cout << 1;
        }
        cout << endl;
        return 0;
    }
    cout << 2 << endl;
    for (int i = 2; i <= n + 1; i++) {
        if (i > 2) {
            cout << " ";
        }
        if (prime[i]) {
            cout << 1;
        } else {
            cout << 2;
        }
    }
    cout << endl;
    return 0;
}
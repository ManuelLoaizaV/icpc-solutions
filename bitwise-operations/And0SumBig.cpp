// https://codeforces.com/problemset/problem/1514/B
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long Long;

const Long MOD = 1000000007;

void Solve(void) {
    Long n, k;
    cin >> n >> k;
    Long cnt = 1;
    while (k--) {
        cnt = (cnt * n) % MOD;
    }
    cout << cnt << '\n';
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) Solve();
    return 0;
}
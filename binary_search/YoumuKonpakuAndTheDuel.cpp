// https://codeforces.com/contest/2288/problem/A
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

Long Check(Long x, Long n, Long s) {
    Long attack = n * (n + 1LL) / 2LL - (n - s) * (n - s + 1LL) / 2LL;
    return attack >= x;
}

void Solve(void) {
    Long x;
    cin >> x;
    Long best = (Long)INT_MAX;
    for (Long extra = 0; extra <= x; extra++) {
        Long steps = extra;
        Long max_attack = 1LL + extra;

        Long L = 1LL;
        Long R = max_attack;
        if (Check(x, max_attack, 1LL)) {
            best = min(best, 1 + extra);
        } else if (!Check(x, max_attack, R)) {
            continue;
        } else {
            while (R - L > 1) {
                Long M = (L + R) / 2LL;
                if (Check(x, max_attack, M)) {
                    R = M;
                } else {
                    L = M;
                }
            }
            best = min(best, R + extra);
        }
    }
    cout << best << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while (t--) Solve();
    return 0;
}
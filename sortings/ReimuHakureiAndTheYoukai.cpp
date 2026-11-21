// https://codeforces.com/contest/2288/problem/B2
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

void Solve(void) {
    Long n, x;
    cin >> n >> x;
    vector<Long> b(n);
    for (int i = 0; i < n; i++) {
        Long a;
        cin >> a;
        b[i] = (a + x - 1LL) / x;
    }
    sort(b.begin(), b.end());
    b.pop_back();
    Long done = 0;
    Long free = 0;
    Long cost = 0;
    for (int i = 0; i < n - 1; i++) {
        Long needed = b[i] - 1;
        if (done < needed) {
            Long to_do = needed - done;
            Long free_consumed = min(to_do, free);
            free -= free_consumed;
            done += to_do;
            cost += to_do - free_consumed;
        }
        free++;
    }
    cout << cost << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while (t--) Solve();
    return 0;
}
// https://codeforces.com/contest/2272/problem/C
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef long double Double;

bool Check(vector<int> a, int max_gap, int extra) {
    int needed = 0;
    if (a.back() > a[a.size() - 2] + max_gap) {
        needed++;
        a[a.size() - 1] -= max_gap;
    }
    for (int i = (int)a.size() - 2; i >= 0; i--) {
        if (a[i + 1] - a[i] <= max_gap) continue;
        if (i > 0 && a[i] - a[i - 1] <= max_gap) continue;
        needed++;
        a[i] -= max_gap;
    }
    return needed <= extra;
}

void Solve(void) {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    int L = 0;
    int R = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (i > 0) {
            R = max(R, a[i] - a[i - 1]);
        }
    }

    // FFFTTT
    while (R - L > 1) {
        int M = (L + R) / 2;
        if (Check(a, M, x)) {
            R = M;
        } else {
            L = M;
        }
    }
    cout << R << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) Solve();
    return 0;
}
// https://codeforces.com/problemset/problem/231/C
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long Long;

const Long N = 100000;

Long v[N];
Long prefixes[N + 1];

int Check(int n, Long target, Long k) {
    for (int i = target; i <= n; i++) {
        Long segment_sum = prefixes[i] - prefixes[i - target];
        Long needed = target * v[i - 1] - segment_sum;
        if (needed <= k) return v[i - 1];
    }
    return INT_MAX;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Long n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> v[i];
    sort(v, v + n);
    prefixes[0] = 0;
    for (int i = 1; i <= n; i++) {
        prefixes[i] = prefixes[i - 1] + v[i - 1];
    }
    Long l = 1;
    Long r = n;
    Long mn = Check(n, r, k);
    if (mn != INT_MAX) {
        cout << r << " " << mn << '\n';
        return 0;
    }
    while (r - l > 1) {
        Long m = (l + r) / 2;
        mn = Check(n, m, k);
        if (mn != INT_MAX) {
            l = m;
        } else {
            r = m;
        }
    }
    mn = Check(n, l, k);
    cout << l << " " << mn << '\n';
    return 0;
}
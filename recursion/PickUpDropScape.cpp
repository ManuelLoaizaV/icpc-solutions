// https://www.spoj.com/problems/CODEIT02/en/
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long Long;

const char ENDL = '\n';

Long MaxXor(Long i, Long k, const Long prev, const vector<Long>& v) {
    int n = (int)v.size() - i;
    if (k == 0) return prev;
    Long mx;
    if (k <= n) {
        mx = MaxXor(i + 1, k - 1, prev ^ v[i], v);
    }
    if (k <= n - 1) {
        mx = max(mx, MaxXor(i + 1, k, prev, v));
    }
    return mx;
}

void Solve(void) {
    Long n, k;
    cin >> n >> k;
    vector<Long> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    cout << MaxXor(0, k, 0, v) << ENDL;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) Solve();
    return 0;
}
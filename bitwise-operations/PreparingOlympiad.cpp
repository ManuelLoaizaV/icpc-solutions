// https://codeforces.com/problemset/problem/550/B
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int GetBit(int n, int i) {
    return ((n >> i) & 1);
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, l, r, x;
    cin >> n >> l >> r >> x;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    int n_masks = 1 << n;
    int cnt = 0;
    for (int mask = 1; mask < n_masks; mask++) {
        int mn = INT_MAX;
        int mx = INT_MIN;
        int difficulty = 0;
        for (int bit = 0; bit < n; bit++) {
            if (GetBit(mask, bit)) {
                difficulty += v[bit];
                mx = max(mx, v[bit]);
                mn = min(mn, v[bit]);
            }
        }
        if (l <= difficulty && difficulty <= r && mx - mn >= x) {
            cnt++;
        }
    }
    cout << cnt << '\n';
    return 0;
}
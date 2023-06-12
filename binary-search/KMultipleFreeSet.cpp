// https://codeforces.com/problemset/problem/275/C
#include <iostream>
#include <vector>
using namespace std;

typedef long long Long;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Long n, k;
    cin >> n >> k;
    vector<Long> v(n);
    vector<bool> banned(n, false);
    for (int i = 0; i < n; i++) cin >> v[i];
    sort(v.begin(), v.end());
    Long cnt = 0;
    for (int i = 0; i < n; i++) {
        if (banned[i]) continue;
        cnt++;
        Long target = k * v[i];
        if (binary_search(v.begin(), v.end(), target)) {
            Long target_index = lower_bound(v.begin(), v.end(), target) - v.begin();
            banned[target_index] = true;
        }
    }
    cout << cnt << '\n';
    return 0;
}
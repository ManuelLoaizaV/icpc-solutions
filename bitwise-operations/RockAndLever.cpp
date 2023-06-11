// https://codeforces.com/problemset/problem/1420/B
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

typedef long long Long;

void Solve(void) {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    Long cnt = 0;
    unordered_map<int, Long> frequencies;
    for (int i = n - 1; i >= 0; i--) {
        int leading_zeroes = __builtin_clz(v[i]);
        cnt += frequencies[leading_zeroes];
        frequencies[leading_zeroes]++;
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
// https://www.hackerrank.com/contests/launchpad-1-winter-challenge/challenges/binary-search-basic
#include <iostream>
#include <vector>
using namespace std;

int FindIndex(int l, int r, int target, const vector<int>& v) {
    if (l > r) return -1;
    int m = (l + r) / 2;
    if (v[m] == target) return m;
    if (target < v[m]) return FindIndex(l, m - 1, target, v);
    return FindIndex(m + 1, r, target, v);
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    int target;
    cin >> target;
    cout << FindIndex(0, n - 1, target, v) << '\n';
    return 0;
}
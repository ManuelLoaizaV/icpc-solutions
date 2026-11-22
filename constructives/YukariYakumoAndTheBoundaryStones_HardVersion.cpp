// https://codeforces.com/contest/2288/problem/B2
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

string query;

void Solve(void) {
    int n;
    cin >> n;
    cout << query << endl;
    int min_size, x, y;
    cin >> min_size;
    if (min_size == 0) {
        x = n;
        y = 0;
    } else {
        y = (min_size + 2) / 3;
        x = n - y;
    }
    int sum = x + 2 * y;
    cout << sum << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for (int i = 0; i < 300; i++) {
        query += "+--";
    }
    int t = 1;
    cin >> t;
    while (t--) Solve();
    return 0;
}
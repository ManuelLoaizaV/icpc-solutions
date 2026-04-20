// https://codeforces.com/problemset/problem/1971/C
#include <bits/stdc++.h>
using namespace std;

void Solve(void) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    int x = std::min(a, b);
    int y = std::max(a, b);

    int z = std::min(c, d);
    int w = std::max(c, d);

    if (x < z && z < y && y < w || z < x && x < w && w < y) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main(void) {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        Solve();
    }
    return 0;
}
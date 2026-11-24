// https://codeforces.com/problemset/problem/1858/A
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

void Solve(void) {
    Long a, b, c;
    cin >> a >> b >> c;
    a += (c + 1LL) / 2LL;
    b += c / 2LL;
    if (a > b) {
        cout << "First" << endl;
    } else {
        cout << "Second" << endl;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) Solve();
    return 0;
}
// https://codeforces.com/problemset/problem/1559/A
#include <iostream>
using namespace std;

void Solve(void) {
    int n;
    cin >> n;
    int all;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (i == 0) {
            all = x;
        } else {
            all &= x;
        }
    }
    cout << all << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) Solve();
    return 0;
}
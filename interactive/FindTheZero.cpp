// https://codeforces.com/contest/2209/problem/C
#include <bits/stdc++.h>
using namespace std;

int Equal(int i, int j) {
    cout << "? " << i + 1 << " " << j + 1 << endl;
    int response;
    cin >> response;
    return response == 1;
}

void Answer(int k) {
    cout << "! " << k + 1 << endl;
}

void Solve(void) {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        if (Equal(2 * i, 2 * i + 1)) {
            Answer(2 * i);
            return;
        }
    }
    if (Equal(2 * n - 2, 2 * n - 3) || Equal(2 * n - 2, 2 * n - 4)) {
        Answer(2 * n - 2);
    } else {
        Answer(2 * n - 1);
    }
}

int main(void) {
    int t;
    cin >> t;
    while (t--) Solve();
    return 0;
}
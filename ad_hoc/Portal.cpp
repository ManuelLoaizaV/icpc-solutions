// https://codeforces.com/contest/2200/problem/D
#include <bits/stdc++.h>
using namespace std;

void Solve(void) {
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> p(n);
    for (auto& e: p) cin >> e;

    int mid_min_index = x;
    for (int i = x + 1; i < y; i++) {
        if (p[i] < p[mid_min_index]) {
            mid_min_index = i;
        }
    }

    vector<int> not_mid;
    for (int i = 0; i < x; i++) {
        not_mid.push_back(p[i]);
    }
    for (int i = y; i < n; i++) {
        not_mid.push_back(p[i]);
    }

    int less_than_mid_min = 0;
    for (int i = 0; i < x; i++) {
        if (p[i] < p[mid_min_index]) {
            less_than_mid_min++;
        } else {
            break;
        }
    }
    if (less_than_mid_min == x) {
        for (int i = y; i < n; i++) {
            if (p[i] < p[mid_min_index]) {
                less_than_mid_min++;
            } else {
                break;
            }
        }
    }

    for (int i = 0; i < less_than_mid_min; i++) {
        cout << not_mid[i] << ' ';
    }
    int steps = y - x;
    for (int step = 0; step < steps; step++) {
        int i = x + (mid_min_index - x + step) % steps;
        cout << p[i] << ' ';
    }
    for (int i = less_than_mid_min; i < not_mid.size(); i++) {
        cout << not_mid[i] << ' ';
    }
    cout << endl;
}

int main(void) {
    int T;
    cin >> T;
    while (T--) Solve();
    return 0;
}
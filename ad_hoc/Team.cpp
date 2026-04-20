// https://codeforces.com/problemset/problem/231/A
#include <bits/stdc++.h>
using namespace std;

int main(void) {
    int n;
    cin >> n;
    int solved_problems = 0;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < 3; j++) {
            int x;
            cin >> x;
            if (x == 1) {
                cnt++;
            }
        }
        if (cnt >= 2) {
            solved_problems++;
        }
    }
    cout << solved_problems << endl;
    return 0;
}
// https://atcoder.jp/contests/abs/tasks/abc086_a
#include <bits/stdc++.h>

using namespace std;

int main(void) {
    int a, b;
    cin >> a >> b;
    if (a % 2 == 0 || b % 2 == 0) {
        cout << "Even" << endl;
    } else {
        cout << "Odd" << endl;
    }
    return 0;
}
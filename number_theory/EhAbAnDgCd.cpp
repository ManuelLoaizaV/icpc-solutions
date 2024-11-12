// https://codeforces.com/problemset/problem/1325/A
#include <iostream>
using namespace std;

int main(void) {
    int t;
    cin >> t;
    while (t--) {
        int x;
        cin >> x;
        int a = 0;
        int b = 0;
        if (x & 1) {
            a = 1;
            b = x - 1;
        } else {
            a = b = x / 2;
        }
        cout << a << ' ' << b << endl;
    }
    return 0;
}
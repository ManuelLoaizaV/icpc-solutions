// https://codeforces.com/problemset/problem/486/A
#include <bits/stdc++.h>

using namespace std;

int main(void) {
    long long n;
    cin >> n;
    long long f{n / 2LL};
    if (n % 2 == 1) {
        f -= n;
    }
    cout << f << endl;
    return 0;
}
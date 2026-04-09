// https://codeforces.com/problemset/problem/479/A
#include <bits/stdc++.h>

using namespace std;

int main(void) {
    long long a, b, c;
    cin >> a >> b >> c;
    long long mx = a * b * c;
    mx = std::max(mx, a + b + c);
    mx = std::max(mx, a * b + c);
    mx = std::max(mx, a + b * c);
    mx = std::max(mx, (a + b) * c);
    mx = std::max(mx, a * (b + c));
    cout << mx << endl;
    return 0;
}
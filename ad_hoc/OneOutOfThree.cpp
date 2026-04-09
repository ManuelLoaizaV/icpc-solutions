// https://atcoder.jp/contests/abc075/tasks/abc075_a
#include <bits/stdc++.h>

using namespace std;

int main(void) {
    long long a, b, c;
    cin >> a >> b >> c;
    long long d = a ^ b ^ c;
    cout << d << endl;
    return 0;
}
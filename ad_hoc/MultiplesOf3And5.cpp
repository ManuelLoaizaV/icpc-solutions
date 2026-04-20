// https://www.hackerrank.com/contests/projecteuler/challenges/euler001/problem
#include <bits/stdc++.h>
using namespace std;

void Solve(void) {
    long long n;
    cin >> n;
    n--;
    long long x = n / 3;
    long long y = n / 5;
    long long z = n / 15;
    long long sum = 3 * x * (x + 1) / 2 + 5 * y * (y + 1) / 2 - 15 * z * (z + 1) / 2;
    cout << sum << endl;
}

int main(void) {
    int t = 1;
    cin >> t;
    while (t--) Solve();
    return 0;
}
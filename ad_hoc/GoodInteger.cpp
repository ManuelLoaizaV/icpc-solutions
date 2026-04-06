#include <bits/stdc++.h>

using namespace std;

bool IsGood(int n) {
    int x = n % 10;
    n /= 10;
    int y = n % 10;
    n /= 10;
    int z = n % 10;
    return x == y && y == z;
}

int main(void) {
    int n;
    cin >> n;

    int prefix = n / 10;
    int suffix = n % 1000;

    if (IsGood(prefix) || IsGood((suffix))) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}
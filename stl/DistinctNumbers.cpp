// https://cses.fi/problemset/task/1621/
#include <bits/stdc++.h>
using namespace std;

int main(void) {
    int n;
    cin >> n;
    set<int> numbers;
    for (int i = 0; i < n; i++) {
        int number;
        cin >> number;
        numbers.insert(number);
    }
    cout << numbers.size() << endl;
    return 0;
}
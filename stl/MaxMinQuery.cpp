// https://atcoder.jp/contests/abc253/tasks/abc253_c
#include <bits/stdc++.h>
using namespace std;

int main(void) {
    int Q;
    cin >> Q;

    multiset<int> numbers;

    while (Q--) {
        int t;
        cin >> t;

        if (t == 1) {
            int x;
            cin >> x;
            numbers.insert(x);
            continue;
        }

        if (t == 2) {
            int x, c;
            cin >> x >> c;
            while (c--) {
                auto it = numbers.find(x);
                if (it == numbers.end()) {
                    break;
                }
                numbers.erase(it);
            }
            continue;
        }

        int mx = *numbers.rbegin();
        int mn = *numbers.begin();
        int diff = mx - mn;
        cout << diff << endl;
    }
    return 0;
}
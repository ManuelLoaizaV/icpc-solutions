// https://cses.fi/problemset/task/3175/
#include <bits/stdc++.h>
using namespace std;

vector<int> permutation;
set<int> values;

void Backtrack(int i) {
    if (values.empty()) {
        for (int e : permutation) {
            cout << e << ' ';
        }
        cout << endl;
        exit(0);
    }

    for (auto it = values.begin(); it != values.end(); it++) {
        int value = *it;
        if (permutation.empty() || abs(permutation.back() - value) > 1) {
            permutation.push_back(value);
            values.erase(value);
            Backtrack(i + 1);
            values.insert(value);
            permutation.pop_back();
            it = values.find(value);
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }

    if (n <= 3) {
        cout << "NO SOLUTION" << endl;
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        values.insert(i);
    }

    Backtrack(0);
    return 0;
}
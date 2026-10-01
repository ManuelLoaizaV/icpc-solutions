// https://atcoder.jp/contests/abc235/tasks/abc235_c
#include <bits/stdc++.h>
using namespace std;

int main(void) {
    int N, Q;
    cin >> N >> Q;

    map<int, vector<int>> indices;
    for (int i = 1; i <= N; i++) {
        int a;
        cin >> a;
        if (indices.count(a)) {
            indices[a].push_back(i);
        } else {
            indices[a] = {i};
        }
    }
    while (Q--) {
        int x, k;
        cin >> x >> k;
        if (indices.count(x) == 0) {
            cout << -1 << endl;
            continue;
        }

        if (k > indices[x].size()) {
            cout << -1 << endl;
            continue;
        }

        cout << indices[x][k - 1] << endl;
    }
    return 0;
}
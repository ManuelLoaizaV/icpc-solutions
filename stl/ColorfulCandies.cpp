// https://atcoder.jp/contests/abc210/tasks/abc210_c
#include <bits/stdc++.h>
using namespace std;

int main(void) {
    int N, K;
    cin >> N >> K;
    vector<int> c(N);
    map<int, int> frequencies;
    int mx = 0;

    for (int i = 0; i < N; i++) {
        cin >> c[i];
        if (frequencies.count(c[i])) {
            frequencies[c[i]]++;
        } else {
            frequencies[c[i]] = 1;
        }

        if (i >= K) {
            frequencies[c[i - K]]--;
            if (frequencies[c[i - K]] == 0) {
                frequencies.erase(c[i - K]);
            }
        }

        mx = max(mx, (int)frequencies.size());
    }
    cout << mx << endl;
    return 0;
}
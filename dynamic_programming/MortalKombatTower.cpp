// https://codeforces.com/problemset/problem/1418/C
#include <bits/stdc++.h>
using namespace std;

void Solve(void) {
    int n;
    cin >> n;
    vector<bool> hard(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        hard[i] = x == 1;
    }

    vector<vector<int>> dp(2, vector<int>(n + 1));
    dp[0][n] = dp[1][n] = 0;
    for (int i = n - 1; i >= 0; i--) {
        dp[0][i] = dp[1][i + 1];
        if (i + 1 < n) {
            dp[0][i] = min(dp[0][i], dp[1][i + 2]);
        }
        int skips = hard[i];
        dp[1][i] = skips + dp[0][i + 1];
        if (i + 1 < n) {
            if (hard[i + 1]) skips++;
            dp[1][i] = min(dp[1][i], skips + dp[0][i + 2]);
        }
    }
    cout << dp[1][0] << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) Solve();
    return 0;
}
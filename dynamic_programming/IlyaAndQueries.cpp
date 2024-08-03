// https://codeforces.com/problemset/problem/313/B
#include <iostream>
#include <vector>
using namespace std;

int main(void) {
    string s;
    cin >> s;
    int n = (int)s.size();
    vector<int> dp(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        if (i < n && s[i - 1] == s[i]) {
            dp[i]++;
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        int cnt = dp[r - 1] - dp[l - 1];
        cout << cnt << endl;
    }
    return 0;
}
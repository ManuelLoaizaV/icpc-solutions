// https://codeforces.com/problemset/problem/1082/E
#include <bits/stdc++.h>
using namespace std;

const int N = 500000;
int remaining[N + 1];
int dp[N + 1];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, c;
    cin >> n >> c;
    vector<int> a(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> c_in_prefix(n + 2);
    c_in_prefix[0] = 0;
    for (int i = 1; i <= n; i++) {
        c_in_prefix[i] = c_in_prefix[i - 1];
        if (a[i] == c) {
            c_in_prefix[i]++;
        }
    }

    vector<int> c_in_suffix(n + 2);
    c_in_suffix[n + 1] = 0;
    for (int i = n; i >= 1; i--) {
        c_in_suffix[i] = c_in_suffix[i + 1];
        if (a[i] == c) {
            c_in_suffix[i]++;
        }
    }

    for (int i = 1; i <= n; i++) {
        remaining[a[i]]++;
    }

    int max_equal_elements = 0;
    for (int R = 1; R <= n; R++) {
        dp[a[R]] = max(dp[a[R]], c_in_prefix[R - 1] + remaining[a[R]]);
        int max_L_R = dp[a[R]] - (remaining[a[R]] - 1) + c_in_suffix[R + 1];
        max_equal_elements = max(max_equal_elements, max_L_R);
        remaining[a[R]]--;
    }

    cout << max_equal_elements << endl;
    return 0;
}
// https://www.hackerrank.com/challenges/maxsubarray/problem
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long Long;

struct Subproblem {
    Long max_sum;
    Long max_suffix;
    Long max_prefix;

    Subproblem() {
        max_sum = max_suffix = max_prefix = 0;
    }
};

const Subproblem EMPTY;

Subproblem MaxSubarraySum(int l, int r, const vector<Long>& v) {
    if (l > r) return EMPTY;
    Subproblem result;
    if (l == r) {
        result.max_sum = max(v[l], 0LL);
        result.max_prefix = max(v[l], 0LL);
        result.max_suffix = max(v[l], 0LL);
        return result;
    }
    int m = (l + r) / 2;
    Subproblem left_subproblem = MaxSubarraySum(l, m, v);
    Subproblem right_subproblem = MaxSubarraySum(m + 1, r, v);

    Long sum = 0;
    // Find new max prefix
    for (int i = l; i <= r; i++) {
        sum += v[i];
        result.max_prefix = max(result.max_prefix, sum);
    }

    sum = 0;
    // Find new max suffix
    for (int i = r; i >= l; i--) {
        sum += v[i];
        result.max_suffix = max(result.max_suffix, sum);
    }

    result.max_sum = max({
        left_subproblem.max_sum,
        right_subproblem.max_sum,
        left_subproblem.max_suffix + right_subproblem.max_prefix
    });

    return result;
}

void Solve(void) {
    int n;
    cin >> n;
    vector<Long> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    Subproblem result = MaxSubarraySum(0, n - 1, v);
    Long mx = v[0];
    for (int i = 1; i < n; i++) {
        mx = max(mx, v[i]);
    }
    if (mx < 0) {
        cout << mx << " " << mx << '\n';
        return;
    }
    Long max_subset_sum = 0;
    for (int i = 0; i < n; i++) {
        if (v[i] >= 0) max_subset_sum += v[i];
    }
    cout << result.max_sum << " " << max_subset_sum << '\n';
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) Solve();
    return 0;
}
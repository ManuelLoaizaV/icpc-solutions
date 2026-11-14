// https://cses.fi/problemset/task/1623/
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 20;
Long p[N];
int n;
Long total_sum = 0;
Long subset_sum = 0;
Long min_diff = LLONG_MAX;

void Backtrack(int i) {
    if (i == n) {
        Long diff = abs(subset_sum - (total_sum - subset_sum));
        min_diff = min(min_diff, diff);
        return;
    }

    subset_sum += p[i];
    Backtrack(i + 1);
    subset_sum -= p[i];
    Backtrack(i + 1);
}

int main(void) {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        total_sum += p[i];
    }
    Backtrack(0);
    cout << min_diff << endl;
    return 0;
}

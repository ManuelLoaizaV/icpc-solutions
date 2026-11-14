// https://usaco.org/index.php?page=viewproblem2&cpid=1276&lang=en
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 20;
int N, M;
long long s[MAX_N], t[MAX_N], c[MAX_N];
const int MAX_M = 10;
long long a[MAX_M], b[MAX_M], p[MAX_M], m[MAX_M];

const int MAX_T = 100;
long long temperatures[MAX_T + 1];
long long min_cost = LLONG_MAX;
long long cost = 0LL;

void Backtrack(int i) {
    if (i == M) {
        for (int cow = 0; cow < N; cow++) {
            for (int k = s[cow]; k <= t[cow]; k++) {
                if (temperatures[k] < c[cow]) {
                    return;
                }
            }
        }
        min_cost = min(min_cost, cost);
        return;
    }

    for (int j = a[i]; j <= b[i]; j++) {
        temperatures[j] += p[i];
    }
    cost += m[i];
    Backtrack(i + 1);
    for (int j = a[i]; j <= b[i]; j++) {
        temperatures[j] -= p[i];
    }
    cost -= m[i];
    Backtrack(i + 1);
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> s[i] >> t[i] >> c[i];
    }
    for (int i = 0; i < M; i++) {
        cin >> a[i] >> b[i] >> p[i] >> m[i];
    }
    Backtrack(0);
    cout << min_cost << endl;
    return 0;
}

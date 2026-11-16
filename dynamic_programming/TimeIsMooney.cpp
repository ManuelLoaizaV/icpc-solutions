// https://usaco.org/index.php?page=viewproblem2&cpid=993
#include <bits/stdc++.h>
using namespace std;

const int S = 1000;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);
    int N, M, C;
    cin >> N >> M >> C;
    vector<int> weights(N);
    for (int u = 0; u < N; u++) {
        cin >> weights[u];
    }
    vector<pair<int, int>> edges;

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        edges.emplace_back(u, v);
    }

    vector<vector<int>> dp(N, vector<int>(S + 1, -1));
    dp[0][0] = 0;
    for (int s = 1; s <= S; s++) {
        for (auto [from, to] : edges) {
            if (dp[from][s - 1] == -1) continue;
            dp[to][s] = max(dp[to][s], dp[from][s - 1] + weights[to]);
        }
    }
    int max_mooney = 0;
    for (int s = 2; s <= S; s++) {
        int mooney = dp[0][s] - C * s * s;
        max_mooney = max(max_mooney, mooney);
    }
    cout << max_mooney << endl;
    return 0;
}
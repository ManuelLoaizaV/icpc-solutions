// https://codeforces.com/contest/600/problem/E
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 100000;
Long colors[N + 5];
Long answer[N + 5];
map<Long, Long> color_freq[N + 5];
map<Long, Long> freq_sum[N + 5];
vector<int> adj[N + 5];

void Add(int u, Long color, Long freq) {
    int old_freq = color_freq[u][color];
    if (freq_sum[u].count(old_freq)) {
        freq_sum[u][old_freq] -= color;
    }
    if (color_freq[u].count(color)) {
        color_freq[u][color] += freq;
    } else {
        color_freq[u][color] = freq;
    }
    if (freq_sum[u].count(color_freq[u][color])) {
        freq_sum[u][color_freq[u][color]] += color;
    } else {
        freq_sum[u][color_freq[u][color]] = color;
    }
}

void DFS(int u, int p = -1) {
    for (int v : adj[u]) {
        if (v == p) continue;
        DFS(v, u);
        if (color_freq[v].size() > color_freq[u].size()) {
            color_freq[u].swap(color_freq[v]);
            freq_sum[u].swap(freq_sum[v]);
        }
        for (auto [color, freq] : color_freq[v]) {
            Add(u, color, freq);
        }
        color_freq[v].clear();
        freq_sum[v].clear();
    }
    Add(u, colors[u], 1);
    answer[u] = (*freq_sum[u].rbegin()).second;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        Long c;
        cin >> c;
        colors[i] = c;
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    DFS(1);

    for (int i = 1; i <= n; i++) {
        if (i > 1) cout << " ";
        cout << answer[i];
    }
    cout << endl;
    return 0;
}
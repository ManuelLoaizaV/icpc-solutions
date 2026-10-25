// https://cses.fi/problemset/task/1139/
#include <bits/stdc++.h>
using namespace std;

const int N = 200000;
vector<int> adj[N + 1];
set<int> subtrees[N + 1];
int colors[N + 1];
int distinct[N + 1];

void DFS(int u, int p = -1) {
    subtrees[u].insert(colors[u]);
    for (int v : adj[u]) {
        if (v != p) {
            DFS(v, u);
            if (subtrees[v].size() > subtrees[u].size()) {
                swap(subtrees[u], subtrees[v]);
            }
            subtrees[u].insert(subtrees[v].begin(), subtrees[v].end());
            subtrees[v].clear();
        }
    }
    distinct[u] = subtrees[u].size();
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> colors[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    DFS(0);

    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << distinct[i];
    }
    cout << endl;
    return 0;
}
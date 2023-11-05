// https://www.spoj.com/problems/PT07Z/en/
#include <iomanip>
#include <iostream>
#include <cassert>
#include <utility>
#include <vector>
using namespace std;

typedef long long Long;

const char ENDL = '\n';

int n_vertices;
int n_edges;

vector<vector<int>> adj;
vector<int> depths;

void Init() {
    adj.resize(n_vertices);
    depths.resize(n_vertices, 0);
    n_edges = n_vertices - 1;
}

void Add(int from, int to) {
    adj[from].push_back(to);
    adj[to].push_back(from);
}

void DFS(int u, int p = -1) {
    if (p == -1) {
        depths[u] = 0;
    } else {
        depths[u] = depths[p] + 1;
    }
    for (int v : adj[u]) {
        if (v == p) continue;
        DFS(v, u);
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n_vertices;
    Init();
    for (int i = 0; i < n_edges; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        Add(u, v);
    }
    DFS(0);
    int max_depth = -1;
    int new_root = -1;
    for (int i = 0; i < n_vertices; i++) {
        if (depths[i] > max_depth) {
            max_depth = depths[i];
            new_root = i;
        }
    }
    DFS(new_root);
    max_depth = -1;
    for (int i = 0; i < n_vertices; i++) {
        max_depth = max(max_depth, depths[i]);
    }
    cout << max_depth << ENDL;
    return 0;
}
// https://codeforces.com/problemset/problem/104/C
#include <iomanip>
#include <iostream>
#include <cassert>
#include <utility>
#include <vector>
#define debug(x) cout << #x << " = " << x << ENDL
using namespace std;

typedef long long Long;

const char ENDL = '\n';

int n_vertices;
int n_edges;

vector<vector<int>> adj;
vector<bool> used;

void Init() {
    adj.resize(n_vertices);
    used.resize(n_vertices, false);
}

void Add(int from, int to) {
    adj[from].push_back(to);
    adj[to].push_back(from);
}

void DFS(int u) {
    used[u] = true;
    for (int v : adj[u]) {
        if (used[v]) continue;
        DFS(v);
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n_vertices >> n_edges;
    Init();
    for (int i = 0; i < n_edges; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        Add(u, v);
    }
    DFS(0);
    int reached_vertices = 0;
    for (int i = 0; i < n_vertices; i++) {
        if (used[i]) {
            reached_vertices++;
        }
    }
    if (
        reached_vertices >= 3 &&
        reached_vertices == n_vertices &&
        n_vertices == n_edges
    ) {
        cout << "FHTAGN!" << ENDL;
    } else {
        cout << "NO" << ENDL;
    }
    return 0;
}
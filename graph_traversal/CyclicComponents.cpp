// https://codeforces.com/problemset/problem/977/E
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
vector<int> degrees;
vector<bool> used;

void Init() {
    adj.resize(n_vertices);
    degrees.resize(n_vertices, 0);
    used.resize(n_vertices, false);
}

void Add(int from, int to) {
    adj[from].push_back(to);
    adj[to].push_back(from);
    degrees[from]++;
    degrees[to]++;
}

bool DFS(int u) {
    used[u] = true;
    bool all_degree_2 = degrees[u] == 2;
    for (int v : adj[u]) {
        if (used[v]) continue;
        all_degree_2 &= DFS(v);
    }
    return all_degree_2;
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
    int cnt = 0;
    for (int i = 0; i < n_vertices; i++) {
        if (used[i]) continue;
        bool all_degree_2 = DFS(i);
        if (all_degree_2) cnt++;
    }
    cout << cnt << ENDL;
    return 0;
}
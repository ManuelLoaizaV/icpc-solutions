// https://codeforces.com/contest/1187/problem/E
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
vector<Long> subtree_sizes;
vector<Long> subtree_sums;

void Init() {
    adj.resize(n_vertices);
    subtree_sizes.resize(n_vertices, 0LL);
    subtree_sums.resize(n_vertices, 0LL);
    n_edges = n_vertices - 1;
}

void Add(int from, int to) {
    adj[from].push_back(to);
    adj[to].push_back(from);
}

void DFS(int u, int p = -1) {
    subtree_sizes[u] = 1LL;
    subtree_sums[u] = 0LL;
    for (int v : adj[u]) {
        if (v == p) continue;
        DFS(v, u);
        subtree_sizes[u] += subtree_sizes[v];
        subtree_sums[u] += subtree_sums[v];
    }
    subtree_sums[u] += subtree_sizes[u];
}

Long max_sum = 0;

void Go(int u, int p = -1, Long p_sum = -1) {
    Long sum = n_vertices;
    for (int v : adj[u]) {
        if (v == p) continue;
        sum += subtree_sums[v];
    }
    if (p_sum != -1) {
        sum += p_sum - subtree_sums[u] - subtree_sizes[u];
    }
    max_sum = max(max_sum, sum);
    for (int v : adj[u]) {
        if (v == p) continue;
        Go(v, u, sum);
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
    Go(0);
    cout << max_sum << ENDL;
    return 0;
}
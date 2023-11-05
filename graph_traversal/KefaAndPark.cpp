// https://codeforces.com/problemset/problem/580/C
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
int max_n_cats;
int n_reachable_leaves;

vector<vector<int>> adj;
vector<bool> cats;

void Init() {
    adj.resize(n_vertices);
    cats.resize(n_vertices, false);
    n_edges = n_vertices - 1;
    n_reachable_leaves = 0;
}

void Add(int from, int to) {
    adj[from].push_back(to);
    adj[to].push_back(from);
}

void DFS(int u, int p = -1, int n_cats = 0) {
    if (cats[u]) {
        n_cats++;
    } else {
        n_cats = 0;
    }

    if (n_cats > max_n_cats) {
        return;
    }

    if ((int)adj[u].size() == 1 && p != -1) {
        n_reachable_leaves++;
    }

    for (int v : adj[u]) {
        if (v == p) continue;
        DFS(v, u, n_cats);
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n_vertices >> max_n_cats;
    Init();
    for (int i = 0; i < n_vertices; i++) {
        int has_cat;
        cin >> has_cat;
        cats[i] = has_cat;
    }
    for (int i = 0; i < n_edges; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        Add(u, v);
    }
    DFS(0);
    cout << n_reachable_leaves << ENDL;
    return 0;
}
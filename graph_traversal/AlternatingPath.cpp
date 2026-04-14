// https://codeforces.com/contest/2204/problem/D
#include <bits/stdc++.h>
using namespace std;
struct CheckBipartite {
    struct Neighbor {
        int node, index;
        Neighbor() {}
        Neighbor(int _node, int _index) : node(_node), index(_index) {}
    };
    struct Edge {
        int from, to;
        Edge() {}
        Edge(int _from, int _to) : from(_from), to(_to) {}
    };
    int V, E;  // |V| and |E| in G(V, E)
    vector<vector<Neighbor>> adj;
    vector<Edge> edge_list;
    vector<bool> visited;
    vector<int> depth;
    CheckBipartite(int _V = -1) {
        if (_V >= 0) Init(_V);
    }
    void Init(int _V) {
        V = _V;
        E = 0;
        adj.assign(V, {});
        edge_list.clear();
    }
    void AddEdge(int from, int to) {
        adj[from].emplace_back(to, E);
        adj[to].emplace_back(from, E);
        edge_list.emplace_back(from, to);
        E++;
    }
    vector<array<vector<int>, 2>> components;
    bool DFS(int node, int parent) {
        assert(!visited[node]);
        visited[node] = true;
        depth[node] = parent < 0 ? 0 : depth[parent] + 1;
        components.back()[depth[node] % 2].push_back(node);
        bool is_bipartite = true;
        for (Neighbor& neighbor: adj[node]) {
            if (neighbor.node == parent) continue;
            if (!visited[neighbor.node] && !DFS(neighbor.node, node)) is_bipartite = false;
            if (depth[node] % 2 == depth[neighbor.node] % 2) is_bipartite = false;
        }
        return is_bipartite;
    }
    int Solve(void) {
        depth.assign(V, -1);
        visited.assign(V, false);
        components.clear();
        int max_beauty{0};
        for (int node = 0; node < V; node++) {
            if (!visited[node]) {
                components.emplace_back();
                if (DFS(node, -1)) {
                    max_beauty += std::max(components.back()[0].size(), components.back()[1].size());
                }
            }
        }
        return max_beauty;
    }
};

void Solve(void) {
    int V, E;
    cin >> V >> E;
    CheckBipartite graph(V);
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        graph.AddEdge(u - 1, v - 1);
    }    
    int max_beauty = graph.Solve();
    cout << max_beauty << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) Solve();
    return 0;
}
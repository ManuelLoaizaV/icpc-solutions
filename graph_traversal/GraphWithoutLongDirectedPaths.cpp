// https://codeforces.com/contest/1144/problem/F
#include <bits/stdc++.h>
using namespace std;

struct CheckBipartite {
    struct Neighbor {
        int node, index, direction;
        Neighbor() {}
        Neighbor(int _node, int _index, int _direction) : node(_node), index(_index), direction(_direction) {}
    };
    struct Edge {
        int from, to, direction;
        Edge() {}
        Edge(int _from, int _to, int _dir) : from(_from), to(_to), direction(_dir) {}
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
        adj[from].emplace_back(to, E, 1);
        adj[to].emplace_back(from, E, 0);
        edge_list.emplace_back(from, to, -1);
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
            if (edge_list[neighbor.index].direction == -1) {
                int target_direction = depth[neighbor.node] % 2;
                int original_direction = neighbor.node == edge_list[neighbor.index].to;
                edge_list[neighbor.index].direction = target_direction == original_direction;
            }
        }
        return is_bipartite;
    }
    bool Solve(void) {
        depth.assign(V, -1);
        visited.assign(V, false);
        components.clear();
        bool is_bipartite{true};
        for (int node = 0; node < V; node++) {
            if (!visited[node]) {
                components.emplace_back();
                if (!DFS(node, -1)) is_bipartite = false;
            }
        }
        return is_bipartite;
    }
};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int V, E;
    cin >> V >> E;
    CheckBipartite graph(V);
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        graph.AddEdge(u - 1, v - 1);
    }
    bool is_bipartite = graph.Solve();
    if (!is_bipartite) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
    for (auto& edge: graph.edge_list) {
        cout << edge.direction;
    }
    cout << endl;
    return 0;
}
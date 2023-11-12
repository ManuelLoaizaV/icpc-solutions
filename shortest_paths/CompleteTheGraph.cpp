// https://codeforces.com/problemset/problem/715/B
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

typedef long long Long;
typedef pair<Long, int> Pair;

const char ENDL = '\n';
const Long INF = 1e10;
const string YES = "YES";
const string NO = "NO";

struct Edge {
    int from, to;
    Long weight;

    Edge(int _from, int _to, Long _weight) : from(_from), to(_to), weight(_weight) {}
};

struct Graph {
    int n_vertices, n_edges;
    vector<vector<int>> adj;
    vector<Long> d;
    vector<Edge> edges;
    vector<int> erased_edge_ids;

    Graph(int n, int m) : n_vertices(n), n_edges(m) {
        adj.resize(n_vertices);
        d.resize(n_vertices, INF);
    }

    void AddEdge(int u, int v, Long w) {
        int edge_id = (int)edges.size();
        assert(edge_id < n_edges);
        adj[u].push_back(edge_id);
        adj[v].push_back(edge_id);
        edges.emplace_back(u, v, w);
        if (w == 0) {
            erased_edge_ids.push_back(edge_id);
        }
    }

    void Dijkstra(int s) {
        for (int i = 0; i < n_vertices; i++) d[i] = INF;
        d[s] = 0LL;
        priority_queue<Pair, vector<Pair>, greater<Pair>> q;
        q.push({0LL, s});
        while (!q.empty()) {
            Pair path = q.top();
            int u = path.second;
            q.pop();
            if (d[u] != path.first) continue;
            for (int edge_id: adj[u]) {
                int v = edges[edge_id].from ^ edges[edge_id].to ^ u;
                Long w = edges[edge_id].weight;
                if (d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    q.push({d[v], v});
                }
            }
        }
    }

    void SetErasedEdgeWeights(Long w) {
        for (int erased_edge_id : erased_edge_ids) {
            edges[erased_edge_id].weight = w;
        }
    }

    void Print(void) {
        cout << YES << ENDL;
        for (int i = 0; i < n_edges; i++) {
            cout << edges[i].from << " " << edges[i].to << " " << edges[i].weight << ENDL;
        }
    }
};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n_vertices, n_edges, source, target;
    Long target_shortest_path;
    cin >> n_vertices >> n_edges >> target_shortest_path >> source >> target;

    Graph graph(n_vertices, n_edges);
    for (int i = 0; i < n_edges; i++) {
        int u, v;
        Long w;
        cin >> u >> v >> w;
        graph.AddEdge(u, v, w);
    }

    Long l = 1LL;
    Long r = target_shortest_path;

    graph.SetErasedEdgeWeights(l);
    graph.Dijkstra(source);
    if (graph.d[target] >= target_shortest_path) {
        if (graph.d[target] > target_shortest_path) {
            cout << NO << ENDL;
        } else {
            graph.Print();
        }
        return 0;
    }

    graph.SetErasedEdgeWeights(r);
    graph.Dijkstra(source);
    if (graph.d[target] <= target_shortest_path) {
        if (graph.d[target] < target_shortest_path) {
            cout << NO << ENDL;
        } else {
            graph.Print();
        }
        return 0;
    }

    while (r - l > 1LL) {
        Long m = (l + r) / 2;
        graph.SetErasedEdgeWeights(m);
        graph.Dijkstra(source);
        if (graph.d[target] > target_shortest_path) {
            r = m;
        } else if (graph.d[target] == target_shortest_path) {
            graph.Print();
            return 0;
        } else {
            l = m;
        }
    }

    graph.SetErasedEdgeWeights(l);

    for (int erased_edge_id : graph.erased_edge_ids) {
        graph.edges[erased_edge_id].weight++;
        graph.Dijkstra(source);
        if (graph.d[target] == target_shortest_path) {
            graph.Print();
            return 0;
        }
    }

    cout << NO << ENDL;

    return 0;
}
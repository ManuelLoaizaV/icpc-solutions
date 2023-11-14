// https://codeforces.com/gym/100589/problem/K
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

typedef long long Long;
typedef pair<Long, int> Pair;

const Long INF = 1e15;
const char ENDL = '\n';

struct Graph {
    int n_vertices, n_edges;
    vector<vector<Pair>> adj;
    vector<Long> d;

    Graph(int n, int m) : n_vertices(n), n_edges(m) {
        adj.resize(n);
        d.resize(n, INF);
    }

    void AddEdge(int u, int v, Long w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
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
            for (Pair e : adj[u]) {
                int v = e.first; Long w = e.second;
                if (d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    q.push({d[v], v});
                }
            }
        }
    }
};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n_vertices, n_edges;
    cin >> n_vertices >> n_edges;

    Graph graph(n_vertices + 1, n_edges);

    for (int i = 0; i < n_edges; i++) {
        int u, v;
        Long w;
        cin >> u >> v >> w;
        graph.AddEdge(u, v, w);
    }

    int n_policemen;
    cin >> n_policemen;
    vector<int> policemen(n_policemen);
    for (int& p : policemen) {
        cin >> p;
        graph.AddEdge(n_vertices, p, 0LL);
    }

    int n_boosters;
    cin >> n_boosters;
    vector<int> boosters(n_boosters);
    for (int& b : boosters) cin >> b;

    int source, target;
    cin >> source >> target;

    graph.Dijkstra(target);

    vector<Long> shortest_paths = graph.d;

    if (shortest_paths[source] == INF) {
        cout << -1 << ENDL;
        return 0;
    }


    graph.Dijkstra(n_vertices);

    Long twice_shortest_path_from_police = INF;
    for (int b : boosters) {
        twice_shortest_path_from_police = min(twice_shortest_path_from_police, 2LL * graph.d[b] + shortest_paths[b]);
    }
    for (int p : policemen) {
        twice_shortest_path_from_police = min(twice_shortest_path_from_police, 2LL * shortest_paths[p]);
    }
    twice_shortest_path_from_police = min(INF, twice_shortest_path_from_police);

    if (2LL * shortest_paths[source] < twice_shortest_path_from_police) {
        cout << shortest_paths[source] << ENDL;
    } else {
        cout << -1 << ENDL;
    }

    return 0;
}
// https://codeforces.com/gym/104736/problem/M
#include <iomanip>
#include <iostream>
#include <cassert>
#include <queue>
#include <unordered_set>
#include <utility>
#include <vector>
#define debug(x) cout << #x << " = " << x << ENDL
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

const char ENDL = '\n';
const Long INF = 1e14 + 1;

int n_vertices, n_edges, odd_source, even_source;

vector<vector<Pair>> adj;
vector<Long> distances;

void Init() {
    adj.resize(n_vertices);
    distances.resize(n_vertices, INF);
}

void Add(int from, int to, Long weight) {
    adj[from].push_back({to, weight});
    adj[to].push_back({from, weight});
}

void Dijkstra(Long source, Long ignored = -1) {
    for (int i = 0; i < n_vertices; i++) {
        distances[i] = INF;
    }

    distances[source] = 0LL;
    priority_queue<Pair, vector<Pair>, greater<Pair>> tour;
    tour.push({0LL, source});

    while (!tour.empty()) {
        Pair path = tour.top();
        tour.pop();
        int u = path.second;
        if (distances[u] != path.first) continue;
        for (Pair edge : adj[u]) {
            Long v = edge.first;
            if (v == ignored) continue;
            Long w = edge.second;
            int d = distances[u] + w;
            if (d < distances[v]) {
                distances[v] = d;
                tour.push({distances[v], v});
            }
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n_vertices >> n_edges;
    int source, target;
    cin >> source >> target;
    source--;
    target--;
    Init();
    for (int i = 0; i < n_edges; i++) {
        int u, v;
        Long w;
        cin >> u >> v >> w;
        u--;
        v--;
        Add(u, v, w);
    }

    Dijkstra(source);

    if (distances[target] == INF) {
        cout << "*" << ENDL;
        return 0;
    }

    vector<Long> original_distances = distances;

    Dijkstra(source, target);

    int cnt = 0;

    for (int i = 0; i < n_vertices; i++) {
        if (
            original_distances[i] == 2LL * original_distances[target] &&
            original_distances[i] < distances[i]
        ) {
            if (cnt > 0) cout << " ";
            cnt++;
            cout << i + 1;
        }
    }

    if (cnt == 0) {
        cout << "*" << ENDL;
    } else {
        cout << ENDL;
    }

    return 0;
}
// https://www.spoj.com/problems/AKBAR/
#include <iomanip>
#include <iostream>
#include <cassert>
#include <queue>
#include <utility>
#include <vector>
#define debug(x) cout << #x << " = " << x << ENDL
using namespace std;

typedef long long Long;

const char ENDL = '\n';
const int MAX_N = 1000000;
const Long INF = 1000005;

int n_vertices, n_edges;

vector<int> adj[MAX_N];
bool used[MAX_N];
Long distances[MAX_N];

void Init(void) {
    for (int i = 0; i < n_vertices; i++) {
        adj[i].clear();
        used[i] = false;
        distances[i] = INF;
    }
}

void Add(int from, int to) {
    adj[from].push_back(to);
    adj[to].push_back(from);
}

bool BFS(int source, Long strength) {
    distances[source] = 0;
    queue<int> tour;
    tour.push(source);

    vector<int> visited;
    while (!tour.empty()) {
        int u = tour.front();
        tour.pop();
        visited.push_back(u);
        if (used[u]) return false;
        if (distances[u] == strength) continue;
        for (int v : adj[u]) {
            if (used[v]) return false;
            int d = distances[u] + 1;
            if (d < distances[v]) {
                distances[v] = d;
                tour.push(v);
            }
        }
    }
    for (int v : visited) {
        used[v] = true;
    }
    return true;
}

void Solve(void) {
    int n_sources;
    cin >> n_vertices >> n_edges >> n_sources;
    Init();
    for (int i = 0; i < n_edges; i++) {
        int u, v;
        cin >> u >> v;
        Add(u - 1, v - 1);
    }
    vector<pair<int, Long>> soldiers(n_sources);
    for (int i = 0; i < n_sources; i++) {
        cin >> soldiers[i].first >> soldiers[i].second;
        soldiers[i].first--;
    }
    bool ok = true;
    for (int i = 0; i < n_sources; i++) {
        if (!BFS(soldiers[i].first, soldiers[i].second)) {
            ok = false;
            break;
        }
    }

    if (ok) {
        int cnt = 0;
        for (int i = 0; i < n_vertices; i++) {
            if (!used[i]) {
                ok = false;
                break;
            }
        }
    }

    if (ok) {
        cout << "Yes" << ENDL;
    } else {
        cout << "No" << ENDL;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n_test_cases;
    cin >> n_test_cases;
    while (n_test_cases--) Solve();
    return 0;
}
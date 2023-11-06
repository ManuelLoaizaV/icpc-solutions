// https://codeforces.com/problemset/problem/1272/E
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
const int INF = 1000000;

int n_vertices, odd_source, even_source;

vector<vector<int>> adj;
vector<int> distances;

// Node n_vertices: Odd artifical node
// Node n_vertices + 1: Even artificial node
void Init() {
    n_vertices += 2;
    adj.resize(n_vertices);
    distances.resize(n_vertices, INF);
    odd_source = n_vertices - 2;
    even_source = n_vertices - 1;
}

void Add(int from, int to) {
    adj[from].push_back(to);
}

void BFS(int source) {
    for (int i = 0; i < n_vertices; i++) {
        distances[i] = INF;
    }

    distances[source] = -1;
    queue<int> tour;
    tour.push(source);

    while (!tour.empty()) {
        int u = tour.front();
        tour.pop();
        for (int v : adj[u]) {
            int d = distances[u] + 1;
            if (d < distances[v]) {
                distances[v] = d;
                tour.push(v);
            }
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n_vertices;
    int n = n_vertices;

    Init();

    vector<int> a(n_vertices);

    for (int i = 0; i < n; i++) {
        cin >> a[i];

        int left = i - a[i];
        if (0 <= left && left < n) {
            Add(left, i);
        }

        int right = i + a[i];
        if (0 <= right && right < n) {
            Add(right, i);
        }

        if (a[i] & 1) {
            Add(odd_source, i);
        } else {
            Add(even_source, i);
        }
    }

    BFS(odd_source);
    vector<int> odd_minimum_distances = distances;

    BFS(even_source);
    vector<int> even_minimum_distances = distances;

    for (int i = 0; i < n; i++) {
        if (odd_minimum_distances[i] == INF) {
            odd_minimum_distances[i] = -1;
        }
        if (even_minimum_distances[i] == INF) {
            even_minimum_distances[i] = -1;
        }
    }

    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        if (a[i] & 1) {
            cout << even_minimum_distances[i];
        } else {
            cout << odd_minimum_distances[i];
        }
    }
    return 0;
}
// https://codeforces.com/problemset/problem/1307/D
#include <algorithm>
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
const Long INF = 200005;

int n_vertices, n_edges;

vector<vector<int>> adj;
vector<Long> distances;

void Init(void) {
    adj.resize(n_vertices);
    distances.resize(n_vertices, INF);
}

void Add(int from, int to) {
    adj[from].push_back(to);
    adj[to].push_back(from);
}

void BFS(int source) {
    for (int i = 0; i < n_vertices; i++) {
        distances[i] = INF;
    }
    distances[source] = 0;
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

struct SpecialField {
    int id;
    Long source_distance;
    Long target_distance;

    bool operator < (const SpecialField& other) const {
        return this->source_distance - this->target_distance < other.source_distance - other.target_distance;
    }
};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n_vertices >> n_edges;

    int n_special_fields;
    cin >> n_special_fields;
    
    vector<SpecialField> special_fields;

    for (int i = 0; i < n_special_fields; i++) {
        SpecialField field;
        cin >> field.id;
        field.id--;
        special_fields.push_back(field);
    }

    Init();

    for (int i = 0; i < n_edges; i++) {
        int u, v;
        cin >> u >> v;
        Add(u - 1, v - 1);
    }

    BFS(0);
    vector<Long> source_distances = distances;

    BFS(n_vertices - 1);
    vector<Long> target_distances = distances;

    for (int i = 0; i < n_special_fields; i++) {
        int id = special_fields[i].id;
        special_fields[i].source_distance = source_distances[id];
        special_fields[i].target_distance = target_distances[id];
    }
    
    sort(special_fields.begin(), special_fields.end());

    Long max_min_distance = 0;
    Long max_target_distance = special_fields.back().target_distance;
    for (int i = n_special_fields - 2; i >= 0; i--) {
        max_min_distance = max(max_min_distance, 1 + special_fields[i].source_distance + max_target_distance);
        max_target_distance = max(max_target_distance, special_fields[i].target_distance);
    }
    // It is guaranteed that source and target are connected
    max_min_distance = min(max_min_distance, source_distances[n_vertices - 1]);
    cout << max_min_distance << ENDL;
    return 0;
}
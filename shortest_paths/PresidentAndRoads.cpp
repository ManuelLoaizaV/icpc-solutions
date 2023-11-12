// https://codeforces.com/problemset/problem/567/E
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

typedef long long Long;
typedef pair<Long, int> Pair;

const char ENDL = '\n';
const Long INF = 1e12;
const string CAN = "CAN";
const string NO = "NO";
const string YES = "YES";

struct Edge {
    int from;
    int to;
    Long weight;
    Edge(int _from, int _to, Long _weight) : from(_from), to(_to), weight(_weight) {}
};

struct Graph {
    int n_vertices, n_edges;
    vector<vector<Pair>> adj;
    vector<Long> d;

    Graph(int _n_vertices, int _n_edges) {
        n_vertices = _n_vertices;
        n_edges = _n_edges;
        adj.resize(n_vertices);
        d.resize(n_vertices, INF);
    }

    void AddEdge(int u, int v, Long w) {
        adj[u].push_back({v, w});
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
                int v = e.first;
                Long w = e.second;
                if (d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    q.push({d[v], v});
                }
            }
        }
    }
};

struct Interval {
    Long l;
    Long r;
    int id;

    Interval(Long _l, Long _r, int _id) : l(_l), r(_r), id(_id) {}

    bool operator < (const Interval& other) const {
        if (l == other.l) return r < other.r;
        return l < other.l;
    }
};

void Compress(vector<Long>& a) {
    int n = a.size();
    vector<pair<Long, int>> pairs(n);
    for (int i = 0; i < n; i++) pairs[i] = {a[i], i};
    sort(pairs.begin(), pairs.end());
    int nxt = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0 && pairs[i - 1].first != pairs[i].first) nxt++;
        a[pairs[i].second] = nxt;
    }
}

vector<bool> FindRequiredIntervals(vector<Interval>& intervals, const int n_edges) {
    int n_intervals = (int)intervals.size();
    
    vector<Long> points;
    for (int i = 0; i < n_intervals; i++) {
        points.push_back(intervals[i].l);
        points.push_back(intervals[i].r);
    }

    vector<Long> compressed_points = points;
    Compress(compressed_points);

    unordered_map<Long, int> h;
    int n_points = (int)points.size();
    for (int i = 0; i < n_points; i++) {
        h[points[i]] = compressed_points[i];
    }

    int n_compressed_points = (int)h.size();
    vector<vector<int>> openings(n_compressed_points);
    vector<vector<int>> closings(n_compressed_points);
    for (int i = 0; i < n_intervals; i++) {
        int l = h[intervals[i].l];
        int r = h[intervals[i].r];
        int id = intervals[i].id;
        openings[l].push_back(id);
        closings[r].push_back(id);
    }

    vector<bool> required(n_edges, true);
    unordered_set<int> required_active_intervals;
    int n_active_intervals = 0;
    for (int i = 0; i < n_compressed_points; i++) {
        int n_openings = (int)openings[i].size();
        int n_closings = (int)closings[i].size();
        if (
            n_openings > 1 ||
            n_active_intervals > n_closings
        ) {
            for (int id : openings[i]) {
                required[id] = false;
            }
        }
        if (n_closings > 1) {
            for (int id : closings[i]) {
                required[id] = false;
            }
        }

        for (int id : closings[i]) {
            if (required_active_intervals.count(id) > 0) {
                required_active_intervals.erase(id);
            }
        }
        n_active_intervals -= n_closings;

        if (n_openings > 0 && n_active_intervals > 0) {
            for (int id : required_active_intervals) {
                required[id] = false;
            }
            required_active_intervals.clear();
            for (int id : openings[i]) {
                required[id] = false;
            }
        }

        for (int id : openings[i]) {
            if (required[id]) {
                required_active_intervals.insert(id);
            }
        }
        n_active_intervals += n_openings;
    }
    return required;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n_vertices, n_edges, source, target;
    cin >> n_vertices >> n_edges >> source >> target;
    source--;
    target--;

    // `graph` will contain shortests paths from source to any node
    Graph graph(n_vertices, n_edges);

    // `reversed_graph` will have the same nodes of `graph` but with reversed edges,
    // so the distances stored represent the shortest path from any node to the target
    Graph reversed_graph(n_vertices, n_edges);

    vector<Edge> edges;
    for (int i = 0; i < n_edges; i++) {
        Long from, to;
        Long weight;
        cin >> from >> to >> weight;
        from--;
        to--;
        graph.AddEdge(from, to, weight);
        reversed_graph.AddEdge(to, from, weight);
        edges.emplace_back(from, to, weight);
    }

    graph.Dijkstra(source);
    reversed_graph.Dijkstra(target);

    Long shortest_path = graph.d[target];
    bool target_reachable = shortest_path < INF;

    if (!target_reachable) {
        for (int i = 0; i < n_edges; i++) {
            cout << NO << ENDL;
        }
        return 0;
    }

    vector<Interval> intervals;
    for (int i = 0; i < n_edges; i++) {
        int from = edges[i].from;
        int to = edges[i].to;
        Long weight = edges[i].weight;
        Long shortest_path_including_edge = graph.d[from] + weight + reversed_graph.d[to];
        if (shortest_path_including_edge == shortest_path) {
            intervals.emplace_back(graph.d[from], graph.d[from] + weight, i);
        }
    }
    vector<bool> required = FindRequiredIntervals(intervals, n_edges);

    for (int i = 0; i < n_edges; i++) {
        int from = edges[i].from;
        int to = edges[i].to;
        Long weight = edges[i].weight;
        Long shortest_path_including_edge = graph.d[from] + weight + reversed_graph.d[to];
        Long take = shortest_path_including_edge - shortest_path + 1LL;
        if (shortest_path_including_edge > shortest_path) {
            if (shortest_path == 1LL || take >= weight) {
                cout << NO << ENDL;
            } else {
                cout << CAN << " " << take << ENDL;
            }
        } else {
            if (required[i]) {
                cout << YES << ENDL;
            } else if (weight > 1LL) {
                cout << CAN << " 1" << ENDL;
            } else {
                cout << NO << ENDL;
            }
        }
    }
    return 0;
}
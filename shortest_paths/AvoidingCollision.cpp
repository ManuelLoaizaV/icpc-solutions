// https://atcoder.jp/contests/arc090/tasks/arc090_c
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

typedef long long Long;
typedef pair<Long, int> Pair;

const char ENDL = '\n';
const Long INF = 1e15;
const Long MOD = 1e9 + 7LL;

struct Mint {
    Long v; // Holds the value of the modular integer
    explicit operator Long() const { return v; }
    // Constructors
    Mint() { v = 0; } // Default constructor initializes to 0
    Mint(Long _v) {
        // Modulo operation to keep value in range [-MOD, MOD)
        v = (-MOD < _v && _v < MOD) ? _v : _v % MOD;
        if (v < 0) v += MOD; // Ensure non-negative value
    }
    // Comparison operators
    friend bool operator==(const Mint& a, const Mint& b) { return a.v == b.v; }
    friend bool operator!=(const Mint& a, const Mint& b) { return !(a == b); }
    friend bool operator<(const Mint& a, const Mint& b) { return a.v < b.v; }
    // Arithmetic operators
    Mint& operator+=(const Mint& m) {
        if ((v += m.v) >= MOD) v -= MOD;
        return *this;
    }
    Mint& operator-=(const Mint& m) {
        if ((v -= m.v) < 0) v += MOD;
        return *this;
    }
    Mint& operator*=(const Mint& m) {
        v = v * m.v % MOD;
        return *this;
    }
    Mint& operator/=(const Mint& m) { return (*this) *= inv(m); }
    // Utility functions
    friend Mint pow(Mint a, Long p) {
        Mint ans = 1; assert(p >= 0);
        for (; p; p /= 2, a *= a) if (p & 1) ans *= a;
        return ans;
    }
    friend Mint inv(const Mint& a) { assert(a.v != 0); return pow(a, MOD - 2); }
    Mint operator-() const { return Mint(-v); }
    Mint& operator++() { return *this += 1; }
    Mint& operator--() { return *this -= 1; }
    Mint operator++(int) { v++; if (v == MOD) v = 0; return Mint(v); }
    Mint operator--(int) { v--; if (v < 0) v = MOD - 1; return Mint(v); }
    // Binary arithmetic operators
    friend Mint operator+(Mint a, const Mint& b) { return a += b; }
    friend Mint operator-(Mint a, const Mint& b) { return a -= b; }
    friend Mint operator*(Mint a, const Mint& b) { return a *= b; }
    friend Mint operator/(Mint a, const Mint& b) { return a /= b; }
    // Stream insertion and extraction operators
    friend ostream& operator<<(ostream& os, const Mint& m) { os << m.v; return os; }
    friend istream& operator>>(istream& is, Mint& m) { Long x; is >> x; m.v = x; return is; }
};


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
};

struct DP {
    Graph& graph;
    vector<Mint> dp;
    vector<bool> done;

    DP(Graph& g): graph(g) {
        dp.resize(graph.n_vertices, 0LL);
        done.resize(graph.n_vertices, false);
    }

    void Clear(void) {
        for (int i = 0; i < graph.n_vertices; i++) {
            dp[i] = 0LL;
            done[i] = false;
        }
    }

    Mint Go(int u, int s) {
        if (u == s) return 1LL;
        if (done[u]) return dp[u];
        for (int i : graph.adj[u]) {
            Edge e = graph.edges[i];
            int v = u ^ e.from ^ e.to;
            Long w = e.weight;
            if (graph.d[v] + w == graph.d[u]) {
                dp[u] += Go(v, s);
            }
        }
        done[u] = true;
        return dp[u];
    }
};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n_vertices, n_edges, source, target;
    cin >> n_vertices >> n_edges >> source >> target;
    source--;
    target--;
    Graph graph(n_vertices, n_edges);
    for (int i = 0; i < n_edges; i++) {
        int u, v;
        Long w;
        cin >> u >> v >> w;
        graph.AddEdge(u - 1, v - 1, w);
    }

    graph.Dijkstra(source);
    vector<Long> shortest_paths_from_source = graph.d;

    DP dp(graph);
    vector<Mint> cnt_from_source;
    for (int i = 0; i < n_vertices; i++) {
        cnt_from_source.push_back(dp.Go(i, source));
    }

    graph.Dijkstra(target);
    vector<Long> shortest_paths_from_target = graph.d;

    dp.Clear();
    vector<Mint> cnt_from_target;
    for (int i = 0; i < n_vertices; i++) {
        cnt_from_target.push_back(dp.Go(i, target));
    }

    Mint cnt = pow(cnt_from_source[target], 2LL);

    // If the midpoint is a vertex
    for (int i = 0; i < n_vertices; i++) {
        if (
            2LL * shortest_paths_from_source[i] == shortest_paths_from_source[target] &&
            2LL * shortest_paths_from_target[i] == shortest_paths_from_source[target]
        ) {
            cnt -= pow(cnt_from_source[i] * cnt_from_target[i], 2LL);
        }
    }

    // If the midpoint is in an edge
    for (int i = 0; i < n_edges; i++) {
        Long w = graph.edges[i].weight;
        vector<int> endpoints = {graph.edges[i].from, graph.edges[i].to};
        for (int j = 0; j < 2; j++) {
            int u = endpoints[0];
            int v = endpoints[1];
            if (
                2LL * shortest_paths_from_source[u] < shortest_paths_from_source[target] &&
                2LL * shortest_paths_from_target[v] < shortest_paths_from_source[target] &&
                shortest_paths_from_source[u] + w + shortest_paths_from_target[v] == shortest_paths_from_source[target]
            ) {
                cnt -= pow(cnt_from_source[u] * cnt_from_target[v], 2LL);
            }
            reverse(endpoints.begin(), endpoints.end());
        }
    }

    cout << cnt << ENDL;
    return 0;
}
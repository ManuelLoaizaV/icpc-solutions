// https://codeforces.com/contest/1900/problem/E
#include <bits/stdc++.h>

#define debug(x) cout << #x << " = " << x << endl

using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

const int N = 1e6;
const Long INF = 1e18;
const char ENDL = '\n';
const Pair WORST = {-1, INF};

Pair Best(const Pair& a, const Pair& b) {
  if (a.first > b.first) return a;
  if (a.first < b.first) return b;
  if (a.second < b.second) return a;
  return b;
}

struct Graph {
  int n_vertices, n_components;
  bool is_condensation;
  vector<vector<int>> adj, rev;
  vector<bool> visited;
  vector<int> order, scc;
  vector<Long> nodes;
  vector<Long> weights;
  vector<bool> done;
  vector<Pair> dp;
  Graph(int n, bool c): n_vertices(n), is_condensation(c) {
    adj.resize(n_vertices);
    if (is_condensation) {
      nodes.resize(n_vertices, 0LL);
      weights.resize(n_vertices, 0LL);
      done.resize(n_vertices, false);
      dp.resize(n_vertices);
    } else {
      rev.resize(n_vertices);
      visited.resize(n_vertices, false);
      scc.resize(n_vertices, -1);
      n_components = 0;
    }
  }
  void AddEdge(int u, int v) {
    adj[u].push_back(v);
    if (!is_condensation) rev[v].push_back(u);
  }
  void ToposortDFS(int u) {
    visited[u] = true;
    for (int v : adj[u])
      if (!visited[v])
        ToposortDFS(v);
    order.push_back(u);
  }
  void SCCsDFS(int u) {
    scc[u] = n_components;
    for (int v : rev[u])
      if (scc[v] == -1)
        SCCsDFS(v);
  }
  void FindSCCs(void) {
    for (int u = 0; u < n_vertices; u++)
      if (!visited[u])
        ToposortDFS(u);
    reverse(order.begin(), order.end());
    for (int u : order) {
      if (scc[u] != -1) continue;
      SCCsDFS(u);
      n_components++;
    }
  }
  Graph BuildCondensation(void) {
    FindSCCs();
    Graph condensation(n_components, true);
    for (int u = 0; u < n_vertices; u++) {
      for (int v : adj[u]) {
        if (scc[u] == scc[v]) continue;
        condensation.AddEdge(scc[u], scc[v]);
      }
    }
    return condensation;
  }
  Pair DP(int u) {
    if (done[u]) return dp[u];
    dp[u] = {nodes[u], weights[u]};
    Pair best = WORST;
    for (int v : adj[u]) {
      best = Best(best, DP(v));
    }
    if (best != WORST) {
      dp[u].first += best.first;
      dp[u].second += best.second;
    }
    done[u] = true;
    return dp[u];
  }
};

void Solve(void) {
  int n_vertices, n_edges;
  cin >> n_vertices >> n_edges;

  vector<Long> a(n_vertices);
  for (int i = 0; i < n_vertices; i++) cin >> a[i];

  Graph graph(n_vertices, false);

  for (int i = 0; i < n_edges; i++) {
    int u, v;
    cin >> u >> v;
    graph.AddEdge(u - 1, v - 1);
  }

  Graph condensation = graph.BuildCondensation();

  for (int u = 0; u < n_vertices; u++) {
    condensation.weights[graph.scc[u]] += a[u];
    condensation.nodes[graph.scc[u]]++;
  }

  Pair best = WORST;
  for (int u = 0; u < n_vertices; u++) {
    best = Best(best, condensation.DP(graph.scc[u]));
  }

  cout << best.first << " " << best.second << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}
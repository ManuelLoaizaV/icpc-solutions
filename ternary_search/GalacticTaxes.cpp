// 2015-2016 ACM-ICPC Latin American Regional Programming Contest
// Problem G. Galactic Taxes

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << '\n'
using namespace std;

typedef long long Long;
typedef long double Double;
typedef pair<Double, int> Pair;

struct Edge {
  int to;
  Long a;
  Long b;
};

const int MAX_V = 1e3;
const Double EPS = 1e-9;
const Double INF = 1e18;

vector<Edge> adj[MAX_V];
Double d[MAX_V];

int Compare(Double a, Double b) {
  if (a <= b + EPS) {
    if (a + EPS < b) return -1;
    return 0;
  }
  return 1;
}

Double Dijkstra(Double t, int V) {
  vector<vector<pair<int, Double>>> nxt(V);
  for (int i = 0; i < V; i++) {
    d[i] = INF;
    for (Edge e : adj[i]) {
      nxt[i].push_back({e.to, e.a * t + e.b});
    }
  }
  d[0] = 0;
  priority_queue<Pair, vector<Pair>, greater<Pair>> q;
  q.push({0, 0});
  while (!q.empty()) {
    Pair path = q.top();
    int u = path.second;
    q.pop();
    if (Compare(d[u], path.first) != 0) continue;
    for (pair<int, Double> e : nxt[u]) {
      int v = e.first;
      Double w = e.second;
      if (Compare(d[u] + w, d[v]) == -1) {
        d[v] = d[u] + w;
        q.push({d[v], v});
      }
    }
  }
  return d[V - 1];
}

Double TernarySearch(Double l, Double r, int V) {
  // while (Compare(r - l, EPS) == 1) {
  for (int i = 0; i <= 100; i++) {
    Double delta = r - l;
    Double m1 = l + delta / 3;
    Double m2 = r - delta / 3;
    if (Compare(Dijkstra(m1, V), Dijkstra(m2, V)) == -1) {
      l = m1;
    } else {
      r = m2;
    }
  }
  Double m = (l + r) / 2;
  return Dijkstra(m, V);
}

void Solve(int V, int E) {
  for (int i = 0; i < E; i++) {
    int u, v;
    Long a, b;
    cin >> u >> v >> a >> b;
    u--;
    v--;
    adj[u].push_back({v, a, b});
    adj[v].push_back({u, a, b});
  }

  Double max_shortest_path = TernarySearch(0.0, 1440.0, V);
  cout << fixed << setprecision(5) << max_shortest_path << '\n';

  for (int i = 0; i < V; i++) {
    adj[i].clear();
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int V, E;
  while (cin >> V >> E) {
    Solve(V, E);
  }
  return 0;
}

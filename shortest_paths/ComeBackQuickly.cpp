//https://atcoder.jp/contests/abc191/tasks/abc191_e
#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const Long INF = 1e14;
const int N = 2e3;

struct Graph {
  vector<Pair> adj[N];
  Long d[N];
  void AddEdge(int u, int v, Long w) { adj[u].push_back({v, w}); }
  void Dijkstra(int s, int n) {
    for (int i = 0; i < n; i++) d[i] = INF;
    d[s] = 0;
    priority_queue<Pair, vector<Pair>, greater<Pair>> q;
    q.push({0, s});
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
} g;


void Solve(void) {
  int n, m, u, v;
  Long w;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    cin >> u >> v >> w;
    u--;
    v--;
    g.AddEdge(u, v, w);
  }
  for (int s = 0; s < n; s++) {
    g.Dijkstra(s, n);
    Long minimum = INF;
    for (int i = 0; i < n; i++) {
      for (auto e : g.adj[i]) {
        if (e.first == s) minimum = min(minimum, g.d[i] + e.second);
      }
    }
    if (minimum == INF) {
      cout << -1 << '\n';
    } else {
      cout << minimum << '\n';
    }
  }
}

int main(void) {
  FAST_IO;
  int t = 1;
  //cin >> t;
  while (t--) Solve();
  return 0;
}


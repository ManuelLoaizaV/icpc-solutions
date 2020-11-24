#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
#define debug(x) cout << #x << " = " << x << '\n'
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Edge;

const Long INF = 1e15;
const int N = 3e3;

struct Graph {
  vector<vector<Edge>> adj;
  vector<Long> d;

  Graph(void) {
    adj.resize(N + 1, vector<Edge>());
    d.resize(N + 1, INF);
  }

  void Initialize(int n) {
    for (int i = 0; i <= n; i++) {
      adj[i].clear();
      d[i] = INF;
    }
  }

  void AddEdge(int u, int v, Long w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  void Dijkstra(int s) {
    priority_queue<Edge, vector<Edge>, greater<Edge>> tour;
    d[s] = 0LL;
    tour.push({0LL, s});
    while (!tour.empty()) {
      Edge path = tour.top();
      tour.pop();
      int u = path.second;
      if (path.first != d[u]) continue;
      for (Edge edge : adj[u]) {
        int v = edge.first;
        Long w = edge.second;
        if (d[u] + w < d[v]) {
          d[v] = d[u] + w;
          tour.push({d[v], v});
        }
      }
    }
  }

  void PrintDistances(int s, int n) {
    bool first_time = true;
    for (int i = 1; i <= n; i++) {
      if (i == s) continue;
      if (first_time) {
        first_time = false;
      } else {
        cout << " ";
      }
      if (d[i] < INF) {
        cout << d[i];
      } else {
        cout << -1;
      }
    }
    cout << '\n';
  }
} graph;

void Solve(void) {
  int n, m;
  cin >> n >> m;
  graph.Initialize(n);
  while (m--) {
    int u, v;
    Long w;
    cin >> u >> v >> w;
    graph.AddEdge(u, v, w);
  }
  int s;
  cin >> s;
  graph.Dijkstra(s);
  graph.PrintDistances(s, n);
}

int main(void) {
  FAST_IO;
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}

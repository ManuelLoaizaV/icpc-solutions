#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Edge;

const Long INF = 1e15;

struct Graph {
  vector<vector<Edge>> adj;
  vector<Long> d;
  vector<int> parent;
  Graph(int n) {
    adj.resize(n + 1, vector<Edge>());
    d.resize(n + 1, INF);
    parent.resize(n + 1, -1);
  }

  void AddEdge(int u, int v, Long w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  bool Dijkstra(int s, int t) {
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
          parent[v] = u;
          tour.push({d[v], v});
        }
      }
    }
    return (d[t] < INF);
  }

  void PrintPath(int last) {
    vector<int> path;
    while (parent[last] != -1) {
      path.push_back(last);
      last = parent[last];
    }
    path.push_back(1);
    reverse(path.begin(), path.end());
    int len = path.size();
    for (int i = 0; i < len; i++) {
      if (i > 0) cout << " ";
      cout << path[i];
    }
    cout << '\n';
  }
};

int main(void) {
  FAST_IO;
  int n, m;
  cin >> n >> m;
  Graph graph(n);
  while (m--) {
    int u, v;
    Long w;
    cin >> u >> v >> w;
    graph.AddEdge(u, v, w);
  }
  if (graph.Dijkstra(1, n)) {
    graph.PrintPath(n);
  } else {
    cout << -1 << '\n';
  }
  return 0;
}

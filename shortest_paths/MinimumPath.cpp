//https://codeforces.com/contest/1473/problem/E
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

const int N = 2e5;
const Long INF = 1e15;

struct Graph {
  vector<Pair> adj[4 * N];
  Long d[4 * N];
  int n;

  void AddEdge(int u, int v, Long w) {
    for (int it = 0; it < 2; it++) {
      adj[u].push_back({v, w});
      adj[u].push_back({n + v, 0});
      adj[u].push_back({2 * n + v, 2 * w});
      adj[u].push_back({3 * n + v, w});
      adj[n + u].push_back({n + v, w});
      adj[n + u].push_back({3 * n + v, 2 * w});
      adj[2 * n + u].push_back({2 * n + v, w});
      adj[2 * n + u].push_back({3 * n + v, 0});
      adj[3 * n + u].push_back({3 * n + v, w});
      swap(u, v);
    }
  }

  void Dijkstra(int s) {
    for (int i = 0; i < 4 * n; i++) d[i] = INF;
    priority_queue<Pair, vector<Pair>, greater<Pair>> tour;
    d[s] = 0;
    tour.push({0, s});
    while (!tour.empty()) {
      Pair current = tour.top();
      tour.pop();
      int u = current.second;
      if (current.first != d[u]) continue;
      for (Pair e : adj[u]) {
        int v = e.first;
        Long w = e.second;
        if (d[u] + w < d[v]) {
          d[v] = d[u] + w;
          tour.push({d[v], v});
        }
      }
    }
  }
} g;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  g.n = n;
  for (int i = 0; i < m; i++) {
    int u, v;
    Long w;
    cin >> u >> v >> w;
    u--;
    v--;
    g.AddEdge(u, v, w);
  }
  g.Dijkstra(0);
  for (int i = 1; i < n; i++) {
    if (i > 1) cout << " ";
    cout << g.d[3 * n + i];
  }
  cout << '\n';
  return 0;
}

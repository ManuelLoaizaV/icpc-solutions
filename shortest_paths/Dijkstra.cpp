//https://codeforces.com/problemset/problem/20/C
#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

const Long INF = 1e18;
const int N = 1e5;

struct Graph {
  vector<Pair> adj[N];
  Long d[N], p[N];

  void AddEdge(Long u, Long v, Long w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  void Dijkstra(Long s, Long n) {
    for (int i = 0; i < n; i++) d[i] = INF;
    d[s] = 0;
    p[s] = -1;
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
          p[v] = u;
          q.push({d[v], v});
        }
      }
    }
  }
} graph;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  Long n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    Long u, v, w;
    cin >> u >> v >> w;
    graph.AddEdge(u - 1, v - 1, w);
  }
  graph.Dijkstra(0, n);
  if (graph.d[n - 1] == INF) {
    cout << -1 << '\n';
  } else {
    vector<int> ans;
    int current = n - 1;
    while (current != -1) {
      ans.push_back(current + 1);
      current = graph.p[current];
    }
    reverse(ans.begin(), ans.end());
    int len = ans.size();
    for (int i = 0; i < len; i++) {
      if (i > 0) cout << " ";
      cout << ans[i];
    }
    cout << '\n';
  }
  return 0;
}

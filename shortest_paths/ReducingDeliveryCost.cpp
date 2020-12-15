#include <iostream>
#include <queue>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

const int N = 1e3;
const int INF = 2e9;

vector<pair<int, int>> adj[N];
int d[N][N];

void Dijkstra(int n, int s) {
  for (int i = 0; i < N; i++) d[s][i] = INF;
  d[s][s] = 0;
  priority_queue<pair<int, int>,
    vector<pair<int, int>>,
    greater<pair<int, int>>> q;
  q.push({0, s});
  while (!q.empty()) {
    auto path = q.top();
    q.pop();
    int u = path.second;
    if (d[s][u] != path.first) continue;
    for (auto e : adj[u]) {
      int v = e.first, w = e.second;
      if (d[s][u] + w < d[s][v]) {
        d[s][v] = d[s][u] + w;
        q.push({d[s][v], v});
      }
    }
  }
}

int main(void) {
  FAST_IO;
  int n, m, k;
  cin >> n >> m >> k;
  vector<pair<int, int>> edges, routes;
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--;
    v--;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
    edges.push_back({u, v});
  }
  for (int i = 0; i < k; i++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    routes.push_back({a, b});
  }
  for (int i = 0; i < n; i++) Dijkstra(n, i);
  int ans = INF;
  for (auto e : edges) {
    int cur = 0;
    int a = e.first;
    int b = e.second;
    for (auto route : routes) {
      int from = route.first;
      int to = route.second;
      cur += min(d[from][to], min(d[from][a] + d[b][to], d[from][b] + d[a][to]));
    }
    ans = min(ans, cur);
  }
  cout << ans << '\n';
  return 0;
}

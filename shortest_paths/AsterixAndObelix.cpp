//https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=1187
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

typedef long long Long;

const int N = 80;
const Long INF = 1e16;

vector<pair<int, Long>> adj[N];
Long cost[N];
Long d[N][N];

void AddEdge(int u, int v, Long w) {
  adj[u].push_back({v, w});
  adj[v].push_back({u, w});
}

void Dijkstra(int s, int n) {
  for (int i = 0; i < n; i++) d[s][i] = INF;
  d[s][s] = cost[s];
  priority_queue<pair<Long, int>, vector<pair<Long, int>>, greater<pair<Long, int>>> q;
  q.push({d[s][s], s});
  while (!q.empty()) {
    auto p = q.top();
    q.pop();
    int u = p.second;
    if (d[s][u] != p.first) continue;
    for (auto e : adj[u]) {
      int v = e.first;
      Long w = e.second;
      if ((cost[v] <= cost[s]) && (d[s][u] + w < d[s][v])) {
        d[s][v] = d[s][u] + w;
        q.push({d[s][v], v});
      }
    }
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int c, r, q;
  int tt = 0;
  bool first_time = true;
  while (cin >> c >> r >> q) {
    if (c == 0 && r == 0 && q == 0) break;
    if (first_time) {
      first_time = false;
    } else {
      cout << '\n';
    }
    tt++;
    cout << "Case #" << tt << '\n';
    for (int i = 0; i < c; i++) adj[i].clear();
    for (int i = 0; i < c; i++) cin >> cost[i];
    for (int i = 0; i < r; i++) {
      int u, v;
      Long w;
      cin >> u >> v >> w;
      u--; v--;
      AddEdge(u, v, w);
    }
    for (int i = 0; i < c; i++) Dijkstra(i, c);
    while (q--) {
      int s, t;
      cin >> s >> t;
      s--; t--;
      Long mn = INF;
      for (int mid = 0; mid < c; mid++) {
        if (d[mid][s] >= INF || d[mid][t] >= INF) continue;
        Long tmp = d[mid][s] + d[mid][t] - cost[mid];
        mn = min(mn, tmp);
      }
      cout << ((mn < INF) ? mn : -1) << '\n';
    }
  }
  return 0;
}

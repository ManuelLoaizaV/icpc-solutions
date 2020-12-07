#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

const int N = 1e3;
const int INF = 1e9;

vector<pair<int, int>> adj[N];
int d[N];

void DFS(int u) {
  d[u] = -INF;
  for (auto e : adj[u]) if (d[e.first] != -INF) DFS(e.first);
}

bool BellmanFord(int s, int n) {
  for (int i = 0; i < n; i++) d[i] = INF;
  d[s] = 0;
  vector<bool> in_cycle(n, false);
  bool has_relaxed;
  for (int it = 0; it < n; it++) {
    has_relaxed = false;
    for (int u = 0; u < n; u++) {
      for (auto e : adj[u]) {
        int v = e.first, w = e.second;
        if (d[u] != INF && d[u] + w < d[v]) {
          d[v] = d[u] + w;
          has_relaxed = true;
          if (it == n - 1) in_cycle[v] = true;
        }
      }
    }
    if (!has_relaxed) break;
  }
  for (int u = 0; u < n; u++) if (in_cycle[u] && d[u] != -INF) DFS(u);
  return has_relaxed;
}

int main(void) {
  FAST_IO;
  int n, m, q, s;
  while (cin >> n >> m >> q >> s) {
    if (n == 0 && m == 0 && q == 0 && s == 0) break;
    for (int i = 0; i < n; i++) adj[i].clear();

    while (m--) {
      int u, v, w;
      cin >> u >> v >> w;
      adj[u].push_back({v, w});
    }
    BellmanFord(s, n);

    while (q--) {
      int to;
      cin >> to;
      if (d[to] != INF) {
        if (d[to] == -INF) {
          cout << "-Infinity" << '\n';
        } else {
          cout << d[to] << '\n';
        }
      } else {
        cout << "Impossible" << '\n';
      }
    }
    cout << '\n';
  }
  return 0;
}

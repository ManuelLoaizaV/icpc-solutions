#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9;
const int N = 2e5;

bool is_cycle;

struct Graph {
  vector<int> adj[N];
  int in[N], out[N], deg[N], timer;
  void Clear(int n) {
    for (int i = 0; i < n; i++) {
      adj[i].clear();
      in[i] = out[i] = 0;
      deg[i] = 0;
    }
    timer = 0;
  }
  void AddEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
    deg[u]++;
    deg[v]++;
  }
  void DFS(int u) {
    in[u] = ++timer;
    if (deg[u] != 2) is_cycle = false;
    for (int v : adj[u]) if (in[v] == 0) DFS(v);
    out[u] = ++timer;
  }
} g;


int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    g.AddEdge(u, v);
  }
  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (g.in[i] == 0) {
      is_cycle = true;
      g.DFS(i);
      if (is_cycle) ans++;
    }
  }
  cout << ans << '\n';
  return 0;
}

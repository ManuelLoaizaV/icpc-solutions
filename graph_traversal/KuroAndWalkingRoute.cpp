//https://codeforces.com/problemset/problem/979/C
#include <iostream>
#include <vector>
using namespace std;

typedef long long Long;

const int N = 3e5;

struct Graph {
  vector<int> adj[N];
  bool is_used[N], is_banned[N];
  int parent[N];

  void Clear(int n) {
    for (int i = 0; i < n; i++) is_used[i] = false;
  }

  void AddEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void DFS(int u, int p, int from, int to) {
    is_used[u] = true;
    parent[u] = p;
    if (u == to) {
      while (u != from) {
        is_banned[u] = true;
        u = parent[u];
      }
      return;
    }
    for (int v : adj[u]) if (!is_used[v]) DFS(v, u, from, to);
  }

  Long DFS(int u) {
    is_used[u] = true;
    Long sum = 1LL;
    for (int v : adj[u]) if (!is_used[v] && !is_banned[v]) sum += DFS(v);
    return sum;
  }
} graph;


int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  Long n, a, b;
  cin >> n >> a >> b;
  a--;
  b--;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    graph.AddEdge(u, v);
  }
  graph.DFS(a, -1, a, b);
  graph.Clear(n);
  Long ans = n * (n - 1) - graph.DFS(a) * graph.DFS(b);
  cout << ans << '\n';
  return 0;
}

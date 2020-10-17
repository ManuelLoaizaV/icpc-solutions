#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define debug(x) cout << #x << " = " << x << '\n'
using namespace std;

typedef long long Long;
typedef pair<Long, pair<int ,int>> Edge;

const int N = 5e4;
const Long INF = 1e18;

vector<pair<int, Long>> adj[N];
vector<Edge> edges;
int anc[N];
Long value[N];

struct DisjointSets {
  int parent[N], size[N];

  void make_set(int u) {
    parent[u] = u;
    size[u] = 1;
  }

  void build(int n) {
    for (int i = 0; i < n; i++) make_set(i);
  }

  int find(int u) {
    if (u == parent[u]) {
      return u;
    } else {
      return (parent[u] = find(parent[u]));
    }
  }

  void join(int u, int v) {
    u = find(u);
    v = find(v);
    if (u != v) {
      if (size[u] > size[v]) swap(u, v);
      parent[u] = v;
      size[v] += size[u];
    }
  }

  bool same_set(int u, int v) {
    return (find(u) == find(v));
  }
} dsu;

void MST(int n) {
  dsu.build(n);
  sort(edges.begin(), edges.end());
  for (Edge edge : edges) {
    Long w = edge.first;
    int u = edge.second.first;
    int v = edge.second.second;
    if (!dsu.same_set(u, v)) {
      adj[u].push_back({v, w});
      adj[v].push_back({u, w});
      dsu.join(u, v);
    }
  }
}

void DFS(int u, int p = -1) {
  for (auto edge : adj[u]) {
    int v = edge.first;
    Long w = edge.second;
    if (v != p) {
      anc[v] = u;
      value[v] = w;
      DFS(v, u);
    }
  }
} 

void Solve(void) {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) adj[i].clear();
  edges.clear();
  for (int i = 0; i < m; i++) {
    int u, v;
    Long w;
    cin >> u >> v >> w;
    u--;
    v--;
    edges.push_back({-w, {u, v}});
  }
  MST(n);
  if (dsu.same_set(0, n - 1)) {
    DFS(0);
    int current = n - 1;
    Long answer = -INF;
    while (current != 0) {
      answer = max(answer, value[current]);
      current = anc[current];
    }
    answer *= (-1);
    cout << answer << '\n';
  } else {
    cout << -1 << '\n';
  }
}

int main(void) {
  FAST_IO;
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}

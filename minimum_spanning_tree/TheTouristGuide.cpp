//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1040
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

typedef long long Long;

const int N = 100;
const Long INF = 1e18;

struct DisjointSets {
  int parent[N];
  int size[N];
  void MakeSet(int u) {
    parent[u] = u;
    size[u] = 1;
  }
  void Build(int n) { for (int i = 0; i < n; i++) MakeSet(i); }
  int Find(int u) {
    if (parent[u] == u) return u;
    return (parent[u] = Find(parent[u]));
  }
  void Join(int u, int v) {
    u = Find(u);
    v = Find(v);
    if (u != v) {
      if (size[u] > size[v]) swap(u, v);
      parent[u] = v;
      size[v] += size[u];
    }
  }
  bool SameSet(int u, int v) { return Find(u) == Find(v); }
  int GetSize(int u) { return size[Find(u)]; }
} dsu;

typedef pair<Long, pair<int, int>> Edge;

vector<Edge> edges, mst;

Long MST(int n) {
  Long cost = 0;
  dsu.Build(n);
  sort(edges.begin(), edges.end());
  for (Edge edge : edges) {
    Long w = edge.first;
    int u = edge.second.first;
    int v = edge.second.second;
    if (!dsu.SameSet(u, v)) {
      mst.push_back(edge);
      dsu.Join(u, v);
      cost += w;
    }
  }
  return cost;
}

vector<pair<int, Long>> adj[N];
pair<int, Long> parent[N];

void AddEdge(int u, int v, Long w) {
  adj[u].push_back({v, w});
  adj[v].push_back({u, w});
}

void DFS(int u, int p = -1, Long w = INF) {
  parent[u] = {p, w};
  for (auto e : adj[u]) if (e.first != p) DFS(e.first, u, e.second);
}

void Clear(int n) {
  edges.clear();
  mst.clear();
  for (int i = 0; i < n; i++) {
    adj[i].clear();
    parent[i] = {-1, INF};
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  int tt = 0;
  while (cin >> n >> m) {
    if (n == 0 && m == 0) break;
    tt++;
    cout << "Scenario #" << tt << '\n';
    Clear(n);
    for (int i = 0; i < m; i++) {
      int u, v;
      Long w;
      cin >> u >> v >> w;
      u--; v--;
      edges.push_back({-w, {u, v}});
    }
    MST(n);
    for (auto e : mst) AddEdge(e.second.first, e.second.second, -e.first);
    int s, d, t;
    cin >> s >> d >> t;
    s--; d--;
    DFS(s);
    cout << "Minimum Number of Trips = ";
    if (s == d) {
      cout << 0 << '\n';
    } else if (!dsu.SameSet(s, d)) {
      cout << -1 << '\n';
    } else {
      int cur = d;
      Long mn = INF;
      while (cur != s) {
        mn = min(mn, parent[cur].second);
        cur = parent[cur].first;
      }
      mn--;
      Long ans = (t + mn - 1) / mn;
      cout << ans << '\n';
    }
    cout << '\n';
  }
  return 0;
}

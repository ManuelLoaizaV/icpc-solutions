#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << '\n'
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

typedef pair<int, pair<int, int>> Edge;
typedef long long Long;

const int N = 2e5;

struct DisjointSets {
  int parent[N];
  Long size[N];

  void make_set(int u) {
    parent[u] = u;
    size[u] = 1LL;
  }

  void build(int n) {
    for (int i = 0; i < n; i++) {
      make_set(i);
    }
  }

  int find(int u) {
    if (parent[u] == u) {
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

  Long get_size(int u) {
    return size[find(u)];
  }
};

int main(void) {
  FAST_IO;
  int n, m;
  cin >> n >> m;
  vector<Edge> edges;
  for (int i = 0; i < n - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--;
    v--;
    edges.push_back({w, {u, v}});
  }
  vector<int> queries;
  for (int i = 0; i < m; i++) {
    int q;
    cin >> q;
    queries.push_back(q);
  }

  DisjointSets dsu;
  dsu.build(n);

  Long cnt[N];
  Long total = 0LL;
  int pos = 0;
  sort(edges.begin(), edges.end());
  for (int timer = 1; timer <= N; timer++) {
    while (pos < n - 1 && edges[pos].first <= timer) {
      int u = edges[pos].second.first;
      int v = edges[pos].second.second;
      if (!dsu.same_set(u, v)) {
        Long u_size = dsu.get_size(u);
        Long v_size = dsu.get_size(v);
        total -= (u_size * (u_size - 1) / 2);
        total -= (v_size * (v_size - 1) / 2);
        dsu.join(u, v);
        Long size = dsu.get_size(u);
        total += (size * (size - 1) / 2);
      }
      pos++;
    }
    cnt[timer - 1] = total;
  }

  for (int i = 0; i < m; i++) {
    if (i > 0) cout << " ";
    cout << cnt[queries[i] - 1];
  }
  cout << '\n';
  return 0;
}

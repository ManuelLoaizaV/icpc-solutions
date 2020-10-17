#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define debug(x) cout << #x << " = " << x << '\n'
#pragma GCC optimize ("Ofast,unroll-loops")
#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

typedef long long Long;
typedef pair<int, Long> Pair;
typedef pair<Long, pair<int, int>> Edge;

const int N = 1e5;

vector<Edge> edges;
vector<Pair> adj[N];
map<pair<int, int>, Long> on_tree, values;

struct DisjointSets {
  int size[N], parent[N];
  
  void make_set(int u) {
    parent[u] = u;
    size[u] = 1;
  }

  void build(int n) {
    for (int i = 0; i < n; i++) make_set(i);
  }

  int find(int u) {
    if (u == parent[u]) return u;
    return (parent[u] = find(parent[u]));
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

Long MST(int n) {
  Long cost = 0;
  for (Edge edge : edges) {
    Long w = edge.first;
    int u = edge.second.first;
    int v = edge.second.second;
    pair<int, int> p = {u, v};
    values[p] = w;
    if (!dsu.same_set(u, v)) {
      adj[u].push_back({v, w});
      adj[v].push_back({u, w});
      dsu.join(u, v);
      on_tree[p] = w;
      cost += w;
    }
  }
  return cost;
}

int depth[N], in[N], out[N];
int anc[N][32 - __builtin_clz(N)];
Long st[N][32 - __builtin_clz(N)];
int timer;

void DFS(int u) {
  in[u] = timer++;
  for (Pair edge : adj[u]) {
    int v = edge.first;
    Long w = edge.second;
    if (v != anc[u][0]) {
      anc[v][0] = u;
      depth[v] = depth[u] + 1;
      st[v][0] = w;
      DFS(v);
    }
  }
  out[u] = timer++;
}

Long f(int u, int v) {
  return max(u, v);
}

void Precalculate(int n, int root = 0) {
  anc[root][0] = -1;
  depth[root] = 0;
  timer = 0;
  DFS(root);
  for (int j = 1; (1 << j) < n; j++) {
    for (int i = 0; i < n; i++) {
      if (anc[i][j - 1] != -1) {
        anc[i][j] = anc[anc[i][j - 1]][j - 1];
        st[i][j] = f(st[i][j - 1], st[anc[i][j - 1]][j - 1]);
      } else {
        anc[i][j] = -1;
      }
    }
  }
}

bool IsAncestor(int u, int v) {
  return (in[u] <= in[v] && out[u] >= out[v]);
}

Long Lift(int u, int v) {
  Long answer = 0;
  int bits = 31 - __builtin_clz(depth[u]);
  if (!IsAncestor(u, v)) {
    for (int i = bits; i >= 0; i--) {
      if (anc[u][i] != -1 && !IsAncestor(anc[u][i], v)) {
        answer = f(answer, st[u][i]);
        u = anc[u][i];
      }
    }
    answer = f(answer, st[u][0]);
    u = anc[u][0];
  }
  return answer;
}

Long Query(int u, int v) {
  return f(Lift(u, v), Lift(v, u));
}

int main(void) {
  FAST_IO;
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v;
    Long w;
    cin >> u >> v >> w;
    u--;
    v--;
    edges.push_back({w, {u, v}});
  }
  dsu.build(n);
  sort(edges.begin(), edges.end());
  Long cost = MST(n);
  Precalculate(n);
  int queries;
  cin >> queries;
  while (queries--) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    pair<int, int> p = {u, v};
    if (on_tree.count(p)) {
      cout << cost << '\n';
    } else {
      Long current = cost + values[p] - Query(u, v);
      cout << current << '\n';
    }
  }
  return 0;
}

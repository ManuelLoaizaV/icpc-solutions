#include <iostream>
#include <vector>
#include <queue>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define x first
#define y second
using namespace std;

typedef pair<int, int> Pair;

const int N = 1e5;

struct DisjointSets {
  int parent[N];
  int size[N];

  void make_set(int u) {
    parent[u] = u;
    size[u] = 1;
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
};

int main(void) {
  FAST_IO;
  int n;
  cin >> n;
  vector<Pair> edges;
  queue<Pair> unused;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    edges.push_back({u, v});
  }
  DisjointSets dsu;
  dsu.build(n);
  for (int i = 0; i < n - 1; i++) {
    int u = edges[i].first;
    int v = edges[i].second;
    if (dsu.same_set(u, v)) {
      unused.push(edges[i]);
    } else {
      dsu.join(u, v);
    }
  }
  vector<pair<Pair, Pair>> ans;
  for (int i = 1; i < n; i++) {
    if (!dsu.same_set(0, i)) {
      dsu.join(0, i);
      ans.push_back({unused.front(), {0, i}});
      unused.pop();
    }
  }
  int len = ans.size();
  printf("%d\n", len);
  for (int i = 0; i < len; i++) {
    printf("%d %d %d %d\n", ans[i].x.x + 1, ans[i].x.y + 1, ans[i].y.x + 1, ans[i].y.y + 1);
  }
  return 0;
}

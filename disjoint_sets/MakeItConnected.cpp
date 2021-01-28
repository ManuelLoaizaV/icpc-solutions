//https://codeforces.com/problemset/problem/1095/F
#include <iostream>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;
typedef tree<Pair, null_type, less<Pair>, rb_tree_tag, tree_order_statistics_node_update> OST;

const int N = 2e5;

Long a[N];

struct Edge {
  int u, v;
  Long w;
  bool operator < (const Edge& other) const {
    return w < other.w;
  }
};

struct DisjointSets {
  int parent[N];
  int size[N];
  Long minimum[N];
  
  void MakeSet(int u) {
    parent[u] = u;
    size[u] = 1;
    minimum[u] = a[u];
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
      minimum[v] = min(minimum[v], minimum[u]);
    }
  }
  
  bool SameSet(int u, int v) { return Find(u) == Find(v); }
  
  int GetSize(int u) { return size[Find(u)]; }

  Long GetMinimum(int u) { return minimum[Find(u)]; }
} dsu;


int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];
  dsu.Build(n);
  vector<Edge> edges;
  for (int i = 0; i < m; i++) {
    int u, v;
    Long w;
    cin >> u >> v >> w;
    u--;
    v--;
    edges.push_back({u, v, w});
  }
  sort(edges.begin(), edges.end());
  reverse(edges.begin(), edges.end());
  OST components;
  for (int i = 0; i < n; i++) components.insert({a[i], i});
  Long ans = 0;
  for (int it = 0; it < n - 1; it++) {
    while (edges.size() > 0 && dsu.SameSet(edges.end()[-1].u, edges.end()[-1].v)) edges.pop_back();
    if (edges.size() == 0) {
      Pair component_1 = *components.find_by_order(0);
      Pair component_2 = *components.find_by_order(1);
      components.erase(component_1);
      components.erase(component_2);
      ans += (component_1.first + component_2.first);
      dsu.Join(component_1.second, component_2.second);
      Pair new_component = {dsu.GetMinimum(component_1.second), dsu.Find(component_1.second)};
      components.insert(new_component);
    } else {
      Pair component_1 = *components.find_by_order(0);
      Pair component_2 = *components.find_by_order(1);
      Long cost = component_1.first + component_2.first;
      Edge edge = edges.end()[-1];
      if (cost < edge.w) {
        components.erase(component_1);
        components.erase(component_2);
        ans += cost;
        dsu.Join(component_1.second, component_2.second);
        Pair new_component = {dsu.GetMinimum(component_1.second), dsu.Find(component_1.second)};
        components.insert(new_component);
      } else {
        edges.pop_back();
        int u = dsu.Find(edge.u);
        int v = dsu.Find(edge.v);
        components.erase({dsu.GetMinimum(u), u});
        components.erase({dsu.GetMinimum(v), v});
        ans += edge.w;
        dsu.Join(u, v);
        Pair new_component = {dsu.GetMinimum(u), dsu.Find(u)};
        components.insert(new_component);
      }
    }
  }
  cout << ans << '\n';
  return 0;
}

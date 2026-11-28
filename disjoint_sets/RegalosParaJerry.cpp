// https://coj.157-180-26-18.sslip.io/24h/problems/2756
// 2756 - Regalos para Jerry
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef long double Double;

// DS using union by size and path compression.
// alpha is the inverse Ackermann function.
struct DisjointSets {
  int elements_n;
  int components_n;
  vector<int> parent;  // Set representatives satisfy parent[u] == u.
  vector<int> size;  // Component size at representatives.

  // Creates n singleton sets.
  // Time complexity: O(n).
  DisjointSets(int n = -1) { if (n >= 0) Init(n); };
  void Init(int n) {
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);
    size.assign(n, 1);
    elements_n = n;
    components_n = n;
  }

  // Unites the dynamic sets that contain u and v.
  // Returns true if they were in differente sets.
  // Time complexity: O(alpha(n)) amortized.
  bool Union(int u, int v) {
    u = FindSet(u);
    v = FindSet(v);
    if (u == v) return false;
    if (size[u] > size[v]) swap(u, v);
    parent[u] = v;
    size[v] += size[u];
    components_n--;
    return true;
  }

  // Returns the representative of the set containing u.
  // Applies path compression.
  // Time complexity: O(alpha(n)) amortized.
  int FindSet(int u) {
    if (u != parent[u]) parent[u] = FindSet(parent[u]);
    return parent[u];
  }

  // Returns the number of elements in the set containing u.
  // Time complexity: O(alpha(n)) amortized.
  int SetSize(int u) {
    return size[FindSet(u)];
  }

  // Returns whether u and v belong to the same set.
  // Time complexity: O(alpha(n)) amortized.
  bool Connected(int u, int v) {
    return FindSet(u) == FindSet(v);
  }

  int ComponentsCount(void) const {
    return components_n;
  }
};

void Solve(int n) {
    vector<pair<int, pair<int, int>>> edges(n);
    for (int i = 0; i < n; i++) {
        cin >> edges[i].second.first >> edges[i].second.second >> edges[i].first;
        edges[i].second.first--;
        edges[i].second.second--;
    }
    sort(edges.begin(), edges.end());

    int q;
    cin >> q;
    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].first;
        queries[i].second = i;
    }
    sort(queries.begin(), queries.end());

    vector<Long> pairs(q);
    Long cnt = 0LL;
    int edge_index = 0;
    DisjointSets dsu(1 << 15);
    for (int i = 0; i < q; i++) {
        while (edge_index < n && edges[edge_index].first <= queries[i].first) {
            int u = edges[edge_index].second.first;
            Long u_size = dsu.SetSize(u);
            int v = edges[edge_index].second.second;
            Long v_size = dsu.SetSize(v);
            if (dsu.Union(u, v)) {
                cnt += u_size * v_size;
            }
            edge_index++;
        }
        pairs[queries[i].second] = cnt;
    }

    for (int i = 0; i < q; i++) {
        cout << pairs[i] << endl;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    while (cin >> n) Solve(n);
    return 0;
}
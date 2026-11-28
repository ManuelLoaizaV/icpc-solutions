#include <bits/stdc++.h>
#include <cassert>

#ifndef ONLINE_JUDGE
#define debug(x) cerr << "[" << #x << "]: " << x << endl
#else
#define debug(x) 69
#endif

using namespace std;

typedef long long Long;
typedef long double Double;

const Long MOD = 998244353LL;
const Long INF = 1000000000000000000LL;
const Double PI = acos(-1);
const Double EPS = 1e-9;

const char A = 'a';
const char ZERO = '0';
const char ENDL = '\n';

const string YES = "YES";
const string NO = "NO";

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

void Solve(void) {
    int n, m;
    cin >> n >> m;
    DisjointSets dsu(n);
    int max_set_size = 1;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        dsu.Union(u, v);
        max_set_size = max({max_set_size, dsu.SetSize(u), dsu.SetSize(v)});
        cout << dsu.ComponentsCount() << " " << max_set_size << endl;
    }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  // cin >> t;
  while (t--) Solve();
  return 0;
}
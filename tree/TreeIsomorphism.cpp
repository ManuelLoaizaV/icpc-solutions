#include <algorithm>
#include <chrono>
#include <climits>
#include <iostream>
#include <map>
#include <random>
#include <utility>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
#define debug(x) cout << #x << " = " << x << '\n'
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long>(a, b)(rng); }

map<Pair, Pair> h;

Pair Add(Pair a, Pair b) {
  return {a.first + b.first, a.second + b.second};
}

struct Graph {
  vector<vector<int>> adj;
  vector<int> sz;
  vector<int> centroid;
  int V;

  Graph(int n) {
    adj.resize(n, vector<int> ());
    sz.resize(n, 0);
    V = n;
  }

  void AddEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void DFS(int u, int p) {
    sz[u] = 1;
    bool is_centroid = true;
    for (int v : adj[u]) {
      if (v != p) {
        DFS(v, u);
        sz[u] += sz[v];
        if (sz[v] > V / 2) is_centroid = false;
      }
    }
    if (V - sz[u] > V / 2) is_centroid = false;
    if (is_centroid) centroid.push_back(u);
  } 
  
  Pair Hash(int u, int p) {
    Pair sum = {0, 0};
    for (int v : adj[u]) {
      if (v != p) sum = Add(sum, Hash(v, u));
    }
    if (h.count(sum) > 0) return h[sum];
    h[sum] = {random(1, LLONG_MAX), random(1, LLONG_MAX)};
    return h[sum];
  }
};

void Solve(void) {
  int n;
  cin >> n;
  Graph t1 = Graph(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    t1.AddEdge(u, v);
  }
  t1.DFS(0, -1);

  Graph t2 = Graph(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    t2.AddEdge(u, v);
  }
  t2.DFS(0, -1);

  vector<Pair> h1, h2;
  for (int c : t1.centroid) {
    h1.push_back(t1.Hash(c, -1));
  }
  for (int c : t2.centroid) {
    h2.push_back(t2.Hash(c, -1));
  }
  bool are_isomorphic = false;
  for (Pair p : h1) {
    for (Pair q : h2) {
      if (p == q) {
        are_isomorphic = true;
      }
    }
  }
  if (are_isomorphic) {
    cout << "YES" << '\n';
  } else {
    cout << "NO" << '\n';
  }
}

int main(void) {
  FAST_IO;
  h[{0, 0}] = {random(1, LLONG_MAX), random(1, LLONG_MAX)};
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}

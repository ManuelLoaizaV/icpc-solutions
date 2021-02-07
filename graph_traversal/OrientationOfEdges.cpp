//https://codeforces.com/problemset/problem/883/G
#include <bits/stdc++.h>
using namespace std;

const int N = 3e5;

struct Edge {
  int id;
  int t;
  int v;
  bool original;
};

vector<Edge> adj[N];
vector<int> new_adj[N];
bool is_used[N], is_banned[N];
char orientation[N];

void AddEdge(int id, int t, int u, int v) {
  adj[u].push_back({id, t, v, true});
  if (t == 2) adj[v].push_back({id, t, u, false});
}

void Print(int m) {
  for (int i = 0; i < m; i++) if (orientation[i] != '$') cout << orientation[i];
  cout << '\n';
}

void DFS(int u, bool maximize) {
  is_used[u] = true;
  for (Edge e : adj[u]) {
    int id = e.id;
    int t = e.t;
    int v = e.v;
    bool original = e.original;
    if (t == 2 && orientation[id] == '$') {
      if (maximize) {
        new_adj[u].push_back(v);
        orientation[id] = original ? '+' : '-';
      } else {
        new_adj[v].push_back(u);
        orientation[id] = original ? '-' : '+';
        is_banned[id] = true;
      }
    }
    if (t == 1) new_adj[u].push_back(v);
  }
  for (Edge e : adj[u]) if (!is_used[e.v] && !is_banned[e.id]) DFS(e.v, maximize);
}

int DFS(int u) {
  int ans = 1;
  is_used[u] = true;
  for (int v : new_adj[u]) if (!is_used[v]) ans += DFS(v);
  return ans;
}

void Clear(int n, int m, bool first) {
  for (int i = 0; i < n; i++) {
    is_used[i] = false;
    is_banned[i] = false;
  }
  if (first) {
    for (int i = 0; i < n; i++) new_adj[i].clear();
    for (int i = 0; i < m; i++) orientation[i] = '$';
  }
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n, m, s;
  cin >> n >> m >> s;
  s--;
  for (int i = 0; i < m; i++) {
    int t, u, v;
    cin >> t >> u >> v;
    u--;
    v--;
    AddEdge(i, t, u, v);
  }
  Clear(n, m, true);
  DFS(s, true);
  for (int i = 0; i < n; i++) if (!is_used[i]) DFS(i, true);
  Clear(n, m, false);
  cout << DFS(s) << '\n';
  Print(m);
  Clear(n, m, true);
  DFS(s, false);
  for (int i = 0; i < n; i++) if (!is_used[i]) DFS(i, false);
  Clear(n, m, false);
  cout << DFS(s) << '\n';
  Print(m);
  return 0;
}

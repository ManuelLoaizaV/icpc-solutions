#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(0)
using namespace std;

const int N = 1e5;
const int INF = 1e9;
const pair<int, int> E = {INF, 0};

vector<pair<int, int>> adj[N];
int depth[N];
int in[N];
int out[N];
int timer;
int anc[N][32 - __builtin_clz(N)];
pair<int, int> st[N][32 - __builtin_clz(N)];

void DFS(int u) {
  in[u] = timer++;
  for (pair<int, int> e : adj[u]) {
    int v = e.first;
    int w = e.second;
    if (v != anc[u][0]) {
      anc[v][0] = u;
      depth[v] = depth[u] + 1;
      st[v][0] = {w, w};
      DFS(v);
    }
  }
  out[u] = timer++;
}

pair<int, int> f(pair<int, int> u, pair<int, int> v) {
  return {min(u.first, v.first), max(u.second, v.second)};
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

pair<int, int> Lift(int u, int v) {
  pair<int, int> ans = E;
  int bits = 31 - __builtin_clz(depth[u]);
  if (!IsAncestor(u, v)) {
    for (int i = bits; i >= 0; i--) {
      if (anc[u][i] != -1 && !IsAncestor(anc[u][i], v)) {
        ans = f(ans, st[u][i]);
        u = anc[u][i];
      }
    }
    ans = f(ans, st[u][0]);
    u = anc[u][0];
  }
  return ans;
}

pair<int, int> Query(int u, int v) {
  return f(Lift(u, v), Lift(v, u));
}

int main() {
  FAST_IO;
  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--;
    v--;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }
  Precalculate(n);
  int q;
  cin >> q;
  while (q--) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    pair<int, int> ans = Query(u, v);
    cout << ans.first << " " << ans.second << '\n';
  }
  return 0;
}

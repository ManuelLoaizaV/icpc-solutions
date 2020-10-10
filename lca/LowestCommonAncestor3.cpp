#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(0)
using namespace std;

const int N = 2e5;

vector<int> adj[N];
int depth[N];
int in[N];
int out[N];
int timer;
int anc[N][32 - __builtin_clz(N)];

void DFS(int u) {
  in[u] = timer++;
  for (int v : adj[u]) {
    if (v != anc[u][0]) {
      anc[v][0] = u;
      depth[v] = depth[u] + 1;
      DFS(v);
    }
  }
  out[u] = timer++;
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
      } else {
        anc[i][j] = -1;
      }
    }
  }
}

bool IsAncestor(int u, int v) {
  return (in[u] <= in[v] && out[u] >= out[v]);
}

int LCA(int u, int v) {
  if (IsAncestor(u, v)) return u;
  int bits = 31 - __builtin_clz(depth[u]);
  for (int i = bits; i >= 0; i--)
    if (anc[u][i] != -1 && !IsAncestor(anc[u][i], v)) u = anc[u][i];
  return anc[u][0];
}

int main() {
  FAST_IO;
  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  Precalculate(n);
  int q;
  cin >> q;
  while (q--) {
    int r, u, v;
    cin >> r >> u >> v;
    r--;
    u--;
    v--;
    int lca_u_v = LCA(u, v);
    int lca_r_u = LCA(r, u);
    int lca_r_v = LCA(r, v);
    int ans;
    if (lca_u_v == u) {
      if (IsAncestor(v, r)) {
        ans = v;
      } else {
        if (IsAncestor(u, r)) {
          ans = lca_r_v;
        } else {
          ans = u;
        }
      }
    } else {
      if (lca_u_v == v) {
        if (IsAncestor(u, r)) {
          ans = u;
        } else {
          if (IsAncestor(v, r)) {
            ans = lca_r_u;
          } else {
            ans = v;
          }
        }
      } else {
        if (LCA(r, lca_u_v) != lca_u_v) {
          ans = lca_u_v;
        } else {
          if (IsAncestor(u, r)) {
            ans = u;
          } else {
            if (IsAncestor(v, r)) {
              ans = v;
            } else {
              if (lca_u_v == lca_r_v) {
                ans = lca_r_u;
              } else {
                ans = lca_r_v;
              }
            }
          }
        }
      }
    }
    ans++;
    cout << ans << '\n';
  }
  return 0;
}

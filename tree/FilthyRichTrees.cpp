//https://codeforces.com/problemset/gymProblem/102694/E
#include <bits/stdc++.h>
using namespace std;

typedef long double Double;

const int N = 3e5;
const int MAX_N = 1e9;
const Double MAX_LOG = log((Double)1e9);

vector<int> adj[N];
int in[N], out[N], timer;

void AddEdge(int u, int v) {
  adj[u].push_back(v);
  adj[v].push_back(u);
}

void DFS(int u, int p) {
  in[u] = ++timer;
  for (int v : adj[u]) if (v != p) DFS(v, u);
  out[u] = timer;
}

struct SegmentTree {
  Double tree[4 * N];
  int n;
  SegmentTree(int new_n) { n = new_n; }
  void Build(int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = 0;
    } else {
      int tm = (tl + tr) / 2;
      Build(2 * id, tl, tm);
      Build(2 * id, tm + 1, tr);
      tree[id] = tree[2 * id] + tree[2 * id + 1];
    }
  }
  void Update(int pos, Double val, int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = val;
    } else {
      int tm = (tl + tr) / 2;
      if (pos <= tm) {
        Update(pos, val, 2 * id, tl, tm);
      } else {
        Update(pos, val, 2 * id + 1, tm + 1, tr);
      }
      tree[id] = tree[2 * id] + tree[2 * id + 1];
    }
  }
  Double Query(int l, int r, int id, int tl, int tr) {
    if (l <= tl && tr <= r) return tree[id];
    int tm = (tl + tr) / 2;
    if (r <= tm) return Query(l, r, 2 * id, tl, tm);
    if (tm < l) return Query(l, r, 2 * id + 1, tm + 1, tr);
    return Query(l, r, 2 * id, tl, tm) + Query(l, r, 2 * id + 1, tm + 1, tr);
  }
  void Update(int pos, Double val) { Update(pos, val, 1, 0, n - 1); }
  Double Query(int l, int r) { return Query(l, r, 1, 0, n - 1); }
};

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    AddEdge(u, v);
  }
  // Aplano el arbol para poder utilizar el segment tree
  timer = -1;
  DFS(0, -1);
  // Construyo el segment tree
  SegmentTree st(n);
  int q;
  cin >> q;
  while (q--) {
    int t, x, y;
    cin >> t >> x >> y;
    if (t == 1) {
      st.Update(in[x - 1], log((Double)y));
    } else {
      x--;
      y--;
      Double log_division = st.Query(in[x], out[x]) - st.Query(in[y], out[y]);
      if (log_division >= MAX_LOG) {
        cout << MAX_N << '\n';
      } else {
        Double value = exp(log_division);
        cout << fixed << setprecision(12) << value << '\n';
      }
    }
  }
  return 0;
}

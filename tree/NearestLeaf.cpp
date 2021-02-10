//https://codeforces.com/problemset/problem/1110/F
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long Long;

const int N = 5e5 + 5;
const Long INF = 1e16;

struct Edge {
  int v;
  Long w;
  bool operator < (const Edge& other) const {
    return v < other.v;
  }
};

struct Consulta {
  int l, r, pos;
};

vector<Edge> adj[N];
vector<Consulta> queries[N];
Long depth[N];
int out[N], in[N];
int next_id = 1;
Long answer[N];

// Segment tree el cual retornara la maxima distancia de una hoja a la raiz
// actual, donde la hoja pertenece al rango consultado
struct SegmentTree {
  Long tree[4 * N], lazy[4 * N];
  int n;
  Long Merge(const Long& x, const Long& y) { return min(x, y); }
  void Build(int id, int tl, int tr) {
    lazy[id] = 0;
    if (tl == tr) {
      tree[id] = INF;
    } else {
      int tm = (tl + tr) / 2;
      Build(2 * id, tl, tm);
      Build(2 * id + 1, tm + 1, tr);
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
  void Push(int id) {
    if (lazy[id] != 0) {
      // Aplicar
      tree[2 * id] += lazy[id];
      tree[2 * id + 1] += lazy[id];
      // Acumular
      lazy[2 * id] += lazy[id];
      lazy[2 * id + 1] += lazy[id];
      // Reiniciar
      lazy[id] = 0;
    }
  }
  void Update(int l, int r, Long add, int id, int tl, int tr) {
    //debug(l, r, add, id, tl, tr);
    if (tr < l || tl > r) return;
    if (l <= tl && tr <= r) {
      //debug(tree[id], lazy[id]);
      tree[id] += add;
      lazy[id] += add;
      //debug(tree[id], lazy[id]);
    } else {
      int tm = (tl + tr) / 2;
      Push(id);
      Update(l, r, add, 2 * id, tl, tm);
      Update(l, r, add, 2 * id + 1, tm + 1, tr);
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
  Long Query(int l, int r, int id, int tl, int tr) {
    if (l <= tl && tr <= r) return tree[id];
    int tm = (tl + tr) / 2;
    Push(id);
    if (r <= tm) return Query(l, r, 2 * id, tl, tm);
    if (tm < l) return Query(l, r, 2 * id + 1, tm + 1, tr);
    return Merge(Query(l, r, 2 * id, tl, tm), Query(l, r, 2 * id + 1, tm + 1, tr));
  }
  void Update(int l, int r, Long add) { Update(l, r, add, 1, 1, n); }
  Long Query(int l, int r) { return Query(l, r, 1, 1, n); }
} st;

void AddEdge(int u, int v, Long w) {
  adj[u].push_back({v, w});
  adj[v].push_back({u, w});
}

void DFS(int u, int p, Long w) {
  in[u] = next_id++;
  for (Edge e : adj[u]) if (e.v != p) DFS(e.v, u, w + e.w);
  if (adj[u].size() == 1) {
    //debug(st.Query(in[u], in[u]), u, w);
    st.Update(in[u], in[u], w - INF);
    //debug(st.Query(in[u], in[u]), u, w);
  }
  out[u] = next_id - 1;
}

void Solve(int u, int p) {
  // Respondo las queries que estan pendientes en mi
  for (Consulta query : queries[in[u]]) {
    answer[query.pos] = st.Query(query.l, query.r);
    //debug(u, in[u], query.l, query.r, query.pos, answer[query.pos]);
  }
  for (Edge e : adj[u]) {
    if (e.v != p) {
      // Decremento en mi subarbol, aumento en el complemento
      st.Update(in[e.v], out[e.v], -e.w);
      if (in[e.v] > 1) st.Update(1, in[e.v] - 1, e.w);
      if (out[e.v] < st.n) st.Update(out[e.v] + 1, st.n, e.w);
      // Respondo las queries en dicho subarbol
      Solve(e.v, u);
      // Incremento el valor en mi subarbol
      st.Update(in[e.v], out[e.v], e.w);
      if (in[e.v] > 1) st.Update(1, in[e.v] - 1, -e.w);
      if (out[e.v] < st.n) st.Update(out[e.v] + 1, st.n, -e.w); 
    }
  }
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  // Construyo el arbol
  for (int i = 1; i < n; i++) {
    int p;
    Long w;
    cin >> p >> w;
    AddEdge(i, p - 1, w);
  }
  // Almaceno las queries en cada nodo
  for (int i = 0; i < q; i++) {
    int v, l, r;
    cin >> v >> l >> r;
    queries[v].push_back({l, r, i});
  }
  // Ordeno de acuerdo al enunciado
  for (int i = 0; i < n; i++) sort(adj[i].begin(), adj[i].end());
  // Hallo los nuevos valores de los nodos, las hojas y las profundidades
  st.n = n;
  st.Build(1, 1, n);
  DFS(0, -1, 0);
  // Recorro el grafo y voy actualizando conforme me muevo
  Solve(0, -1);
  for (int i = 0; i < q; i++) cout << answer[i] << '\n';
  return 0;
}

//#pragma GCC optimize ("Ofast,unroll-loops")
//#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<int, int> Pair;

const int N = 2e5;
const Long INF = INT_MAX;
const Double EPS = 1e-9;

struct Monster {
  int x, y, z;
  void Read(void) { scanf("%d %d %d", &x, &y, &z); }
  bool operator < (const Monster& other) const {
    return x < other.x;
  }
};

struct SegmentTree {
  int tree[4 * N], lazy[4 * N];
  int Merge(const int& x, const int& y) { return max(x, y); }
  void Build(const vector<Pair>& a, int id, int tl, int tr) {
    // Reiniciar
    lazy[id] = 0;
    if (tl == tr) {
      tree[id] = -a[tl].second;
    } else {
      int tm = (tl + tr) / 2;
      Build(a, 2 * id, tl, tm);
      Build(a, 2 * id + 1, tm + 1, tr);
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
  void Push(int id) {
    if (lazy[id] == 0) return;
    // Aplicar
    tree[2 * id] += lazy[id];
    tree[2 * id + 1] += lazy[id];
    // Acumular
    lazy[2 * id] += lazy[id];
    lazy[2 * id + 1] += lazy[id];
    // Reiniciar
    lazy[id] = 0;
  }
  void Update(int l, int r, int delta, int id, int tl, int tr) {
    if (tr < l || tl > r) return;
    if (l <= tl && tr <= r) {
      // Aplicar
      tree[id] += delta;
      // Acumular
      lazy[id] += delta;
    } else {
      int tm = (tl + tr) / 2;
      Push(id);
      Update(l, r, delta, 2 * id, tl, tm);
      Update(l, r, delta, 2 * id + 1, tm + 1, tr);
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
  int Query(int l, int r, int id, int tl, int tr) {
    if (l <= tl && tr <= r) return tree[id];
    int tm = (tl + tr) / 2;
    Push(id);
    if (r <= tm) return Query(l, r, 2 * id, tl, tm);
    if (tm < l) return Query(l, r, 2 * id + 1, tm + 1, tr);
    return Merge(Query(l, r, 2 * id, tl, tm), Query(l, r, 2 * id + 1, tm + 1, tr));
  }
} st;

//FFFFTTTT
int Find(const vector<Pair>& b, int target) {
  int l = 0;
  int r = b.size() - 1;
  if (b[l].first > target) return l;
  if (b[r].first <= target) return -1;
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (b[m].first > target) {
      r = m;
    } else {
      l = m;
    }
  }
  return r;
}

int main(void) {
  FAST_IO;
  int n, m, p;
  scanf("%d %d %d", &n, &m, &p);
  vector<Pair> a(n), b(m);
  for (int i = 0; i < n; i++) scanf("%d %d", &a[i].first, &a[i].second);
  for (int i = 0; i < m; i++) scanf("%d %d", &b[i].first, &b[i].second);
  vector<Monster> monsters(p);
  for (int i = 0; i < p; i++) monsters[i].Read();
  // Ordeno los elementos
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  sort(monsters.begin(), monsters.end());
  // Construyo el segment tree
  st.Build(b, 1, 0, m - 1);
  int ans = -INF;
  int j = 0;
  for (int i = 0; i < n; i++) {
    while (j < p && a[i].first > monsters[j].x) {
      int mn = Find(b, monsters[j].y);
      if (mn != -1) st.Update(mn, m - 1, monsters[j].z, 1, 0, m - 1);
      j++;
    }
    int tmp = -a[i].second + st.Query(0, m - 1, 1, 0, m - 1);
    ans = max(ans, tmp);
  }
  printf("%d\n", ans);
  return 0;
}

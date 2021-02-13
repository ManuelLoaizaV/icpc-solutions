//https://codeforces.com/problemset/problem/1311/F
#include <bits/stdc++.h>
#include <unistd.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define debug(x) cout << #x << " = " << x << endl
#define all(v) (v).begin(),(v).end()
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 3e5;
const Long INF = 1e18;
const Double EPS = 1e-9;

struct Data {
  Long x, v, st_id;
};

struct SegmentTree {
  Pair tree[4 * N];
  Pair Merge(const Data& p) { return {p.x, 1}; }
  Pair Merge(const Pair& x, const Pair& y) {
    return {x.first + y.first, x.second + y.second};
  }
  void Build(const vector<Data>& a, int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = Merge(a[tl]);
    } else {
      int tm = (tl + tr) / 2;
      Build(a, 2 * id, tl, tm);
      Build(a, 2 * id + 1, tm + 1, tr);
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
  void Update(int pos, int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = {0, 0};
    } else {
      int tm = (tl + tr) / 2;
     if (pos <= tm) {
       Update(pos, 2 * id, tl, tm);
     } else {
       Update(pos, 2 * id + 1, tm + 1, tr);
     }
     tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
  Pair Query(int l, int r, int id, int tl, int tr) {
    if (l <= tl && tr <= r) return tree[id];
    int tm = (tl + tr) / 2;
    if (r <= tm) return Query(l, r, 2 * id, tl, tm);
    if (tm < l) return Query(l, r, 2 * id + 1, tm + 1, tr);
    return Merge(Query(l, r, 2 * id, tl, tm), Query(l, r, 2 * id + 1, tm + 1, tr));
  }
} st;

bool velocity_increasing (const Data& d1, const Data& d2) {
  return d1.v < d2.v;
}

bool x_increasing (const Data& d1, const Data& d2) {
  return d1.x < d2.x;
}

int Find(const vector<Data>& points, Long target) {
  int l = 0;
  int r = points.size();
  if (points[l].v >= target) return l;
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (points[m].v >= target) {
      r = m;
    } else {
      l = m;
    }
  }
  return r;
}

int main(void) {
  FAST_IO;
  Long n;
  cin >> n;
  vector<Data> points(n);
  for (int i = 0; i < n; i++) cin >> points[i].x;
  for (int i = 0; i < n; i++) cin >> points[i].v;
  sort(points.begin(), points.end(), velocity_increasing);
  for (int i = 0; i < n; i++) points[i].st_id = i;
  st.Build(points, 1, 0, n - 1);
  // Copia respetando dicho orden de rapideces
  vector<Data> aux = points;
  // Ordeno respecto a x
  sort(points.begin(), points.end(), x_increasing);
  Long ans = 0;
  // Para cada x_i < x_{i + 1} < ... < x_n
  // Quiero \sum_{i < j, v_i <= v_j} x_j - x_i
  // = (\sum_{i < j, v_i <= v_j} x_j) - k * x_i
  for (int i = 0; i < n; i++) {
    // Hallo la posicion tal que v_j >= v_i
    int pos = Find(aux, points[i].v);
    // Hallo la sum de los x_j, j >= pos y la cantidad de eliminados
    Pair tmp = st.Query(pos, n - 1, 1, 0, n - 1);
    ans += tmp.first - tmp.second * points[i].x;
    // Elimino al sujeto actual
    st.Update(points[i].st_id, 1, 0, n - 1);
  }
  cout << ans << '\n';
  return 0;
}

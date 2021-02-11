//#pragma GCC optimize ("Ofast,unroll-loops")
//#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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

const int N = 1e4 + 5;
const int LG = 32 - __builtin_clz(N);

struct Node {
  Long max_left, max_right, total_sum, max_total;
};

struct SegmentTree {
  Node tree[4 * N];
  Node Merge(const Long& x) { return {x, x, x, x}; }
  Node Merge(const Node& left, const Node& right) {
    Node ans;
    ans.max_left = max(left.max_left, left.total_sum + right.max_left);
    ans.max_right = max(right.max_right, right.total_sum + left.max_right);
    ans.total_sum = left.total_sum + right.total_sum;
    ans.max_total = max(left.max_right + right.max_left, max(left.max_total, right.max_total));
    return ans;
  }
  void Build(const vector<Long>& a, int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = Merge(a[tl]);
    } else {
      int tm = (tl + tr) / 2;
      Build(a, 2 * id, tl, tm);
      Build(a, 2 * id + 1, tm + 1, tr);
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
  Node Query(int l, int r, int id, int tl, int tr) {
    if (l <= tl && tr <= r) return tree[id];
    int tm = (tl + tr) / 2;
    if (r <= tm) return Query(l, r, 2 * id, tl, tm);
    if (tm < l) return Query(l, r, 2 * id + 1, tm + 1, tr);
    return Merge(Query(l, r, 2 * id, tl, tm), Query(l, r, 2 * id + 1, tm + 1, tr));
  }
} segment_tree;


struct SparseTable {
  Pair st[N][LG];
  Pair Merge(Long x) { return {x, x}; }
  Pair Merge(Pair x, Pair y) { return {min(x.first, y.first), max(x.second, y.second)}; }
  void Build(vector<Long>& a, int n) {
    for (int i = 0; i < n; i++) st[i][0] = Merge(a[i]);
    for (int j = 1; j < LG; j++)
      for (int i = 0; i + (1 << j) <= n; i++)
        st[i][j] = Merge(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
  }
  // O(1). Solo funciona con operadores idempotentes.
  Pair Query(int l, int r) {
    int range = r - l + 1;
    int lg = 31 - __builtin_clz(range);
    return Merge(st[l][lg], st[r - (1 << lg) + 1][lg]);
  }
} sparse_table;

// Tengo tres posibilidades para los intervalos de consulta
// Caso 1:
// x1 <= y1 < x2 <= y2
// [      ]   [      ]
// Respuesta: max prefix sum [x2, y2] - min prefix sum [x1 - 1, y1 - 1]
// Caso 2:
// [      ]
//    [       ]
// Respuesta: El maximo de las tres siguientes consultas;
// 1. max prefix sum [y1 + 1, y2] - min prefix sum [x1 - 1, y1 - 1]
// 2. max sub array sum en [x2, y1]
// 3. max prefix sum [x2, y1] - min prefix sum [x1 - 1, x2 - 1]
// Respuesta:
// Caso 3:
// [      ]
//    [   ]
// Respuesta: El maximo de las siguientes dos consultas:
// 1. max sub array sum en [x2, y2]
// 2. max prefix sum [x2, y2] - min prefix sum [x1 - 1, x2 - 2]
void Solve(void) {
  int n;
  cin >> n;
  vector<Long> a(n + 1);
  a[0] = 0;
  for (int i = 1; i <= n; i++) cin >> a[i];
  segment_tree.Build(a, 1, 0, n);
  vector<Long> pref(n + 1);
  pref[0] = 0;
  for (int i = 1; i <= n; i++) pref[i] = pref[i - 1] + a[i];
  sparse_table.Build(pref, n + 1);
  int q;
  cin >> q;
  while (q--) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    Long answer;
    if (y1 < x2) {
      // Caso 1
      answer = sparse_table.Query(x2, y2).second - sparse_table.Query(x1 - 1, y1 - 1).first;
    } else if (y1 == y2){
      // Caso 3
      answer = segment_tree.Query(x2, y2, 1, 0, n).max_total;
      if (x2 > x1) answer = max(answer, sparse_table.Query(x2, y2).second - sparse_table.Query(x1 - 1, x2 - 2).first);
    } else {
      // Caso 2
      answer = segment_tree.Query(x2, y1, 1, 0, n).max_total;
      answer = max(answer, sparse_table.Query(y1 + 1, y2).second - sparse_table.Query(x1 - 1, y1 - 1).first);
      if (x2 > x1) answer = max(answer, sparse_table.Query(x2, y2).second - sparse_table.Query(x1 - 1, x2 - 2).first);
    }
    cout << answer << '\n';
  }
}

int main(void) {
  FAST_IO;
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}

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

const int N = 1e5;
const Long INF = 1e18;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

struct SegmentTree {
  vector<int> tree[4 * N];
  int lazy[4 * N];
  vector<int> Merge(const vector<int>& x, const vector<int>& y) {
    vector<int> ans(3);
    for (int i = 0; i < 3; i++) ans[i] = x[i] + y[i];
    return ans;
  }
  void Build(int id, int tl, int tr) {
    lazy[id] = 0;
    if (tl == tr) {
      tree[id] = {1, 0, 0};
    } else {
      int tm = (tl + tr) / 2;
      Build(2 * id, tl, tm);
      Build(2 * id + 1, tm + 1, tr);
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
  void Rotate(vector<int>& v, int steps) {
    if (steps == 0) return;
    if (steps == 1) {
      swap(v[0], v[1]);
      swap(v[0], v[2]);
      return;
    }
    swap(v[0], v[2]);
    swap(v[0], v[1]);
  }
  void Push(int id) {
    if (lazy[id] == 0) return;
    int left = 2 * id;
    int right = 2 * id + 1;
    // Aplicar
    Rotate(tree[left], lazy[id]);
    Rotate(tree[right], lazy[id]);
    // Propagar
    lazy[left] = (lazy[left] + lazy[id]) % 3;
    lazy[right] = (lazy[right] + lazy[id]) % 3;
    // Reiniciar
    lazy[id] = 0;
  }
  void Update(int l, int r, int id, int tl, int tr) {
    if (r < tl || l > tr) return;
    if (l <= tl && tr <= r) {
      Rotate(tree[id], 1);
      lazy[id] = (lazy[id] + 1) % 3;
    } else {
      int tm = (tl + tr) / 2;
      Push(id);
      Update(l, r, 2 * id, tl, tm);
      Update(l, r, 2 * id + 1, tm + 1, tr);
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
  int Query(int l, int r, int id, int tl, int tr) {
    if (l <= tl && tr <= r) return tree[id][0];
    int tm = (tl + tr) / 2;
    Push(id);
    if (r <= tm) return Query(l, r, 2 * id, tl, tm);
    if (tm < l) return Query(l, r, 2 * id + 1, tm + 1, tr);
    return Query(l, r, 2 * id, tl, tm) + Query(l, r, 2 * id + 1, tm + 1, tr);
  }
} st;

int main(void) {
  FAST_IO;
  int n, q;
  cin >> n >> q;
  st.Build(1, 0, n - 1);
  while (q--) {
    int t, l, r;
    cin >> t >> l >> r;
    if (t == 0) {
      st.Update(l, r, 1, 0, n - 1);
    } else {
      cout << st.Query(l, r, 1, 0, n - 1) << '\n';
    }
  }
  return 0;
}

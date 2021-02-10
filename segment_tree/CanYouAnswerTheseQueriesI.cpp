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

const Long INF = 1e18;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

const int N = 1e5;

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
} st;

int main(void) {
  FAST_IO;
  int n;
  cin >> n;
  vector<Long> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  st.Build(a, 1, 0, n - 1);
  int m;
  cin >> m;
  while (m--) {
    int l, r;
    cin >> l >> r;
    cout << st.Query(l - 1, r - 1, 1, 0, n - 1).max_total << '\n';
  }
  return 0;
}


//https://www.spoj.com/problems/KGSS/
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

struct Node {
  Pair max1, max2;
  Node(void) {}
  Node(Long val, Long pos) {
    max1.first = val;
    max1.second = pos;
    max2.first = 0;
    max2.second = -1;
  }
};

const int N = 1e5;

struct SegmentTree {
  Node tree[4 * N];
  Node Merge(const Node& x, const Node& y) {
    vector<Pair> aux;
    aux.push_back({x.max1});
    aux.push_back({x.max2});
    aux.push_back({y.max1});
    aux.push_back({y.max2});
    sort(aux.begin(), aux.end());
    Node ans;
    ans.max1 = aux[3];
    ans.max2 = aux[2];
    return ans;
  }
  void Build(const vector<Long>& a, int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = Node(a[tl], tl);
    } else {
      int tm = (tl + tr) / 2;
      Build(a, 2 * id, tl, tm);
      Build(a, 2 * id + 1, tm + 1, tr);
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
  void Update(int pos, Long val, int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = Node(val, tl);
    } else {
      int tm = (tl + tr) / 2;
     if (pos <= tm) {
       Update(pos, val, 2 * id, tl, tm);
     } else {
       Update(pos, val, 2 * id + 1, tm + 1, tr);
     }
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
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<Long> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  st.Build(a, 1, 0, n - 1);
  int q;
  cin >> q;
  while (q--) {
    char t;
    int l, r;
    cin >> t >> l >> r;
    if (t == 'U') {
      st.Update(l - 1, r, 1, 0, n - 1);
    } else {
      Node query = st.Query(l - 1, r - 1, 1, 0, n - 1);
      Long sum = query.max1.first + query.max2.first;
      cout << sum << '\n';
    }
  }
  return 0;
}

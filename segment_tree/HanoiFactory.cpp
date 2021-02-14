//https://codeforces.com/problemset/problem/777/E
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 2e5;

struct SegmentTree {
  Long tree[4 * N];
  Long Merge(const Long& x) { return x; }
  Long Merge(const Long& x, const Long& y) { return max(x, y); }
  void Build(int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = 0;
    } else {
      int tm = (tl + tr) / 2;
      Build(2 * id, tl, tm);
      Build(2 * id + 1, tm + 1, tr);
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
  void Update(int pos, Long val, int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = max(tree[id], val);
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
  Long Query(int l, int r, int id, int tl, int tr) {
    if (l <= tl && tr <= r) return tree[id];
    int tm = (tl + tr) / 2;
    if (r <= tm) return Query(l, r, 2 * id, tl, tm);
    if (tm < l) return Query(l, r, 2 * id + 1, tm + 1, tr);
    return Merge(Query(l, r, 2 * id, tl, tm), Query(l, r, 2 * id + 1, tm + 1, tr));
  }
} st;


struct Ring {
  Long a, b, h;
  void Read(void) {
    cin >> a >> b >> h;
  }
  bool operator < (const Ring& other) const {
    if (b != other.b) return b < other.b;
    return a < other.a;
  }
};

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<Ring> rings(n);
  for (int i = 0; i < n; i++) {
    rings[i].Read();
    rings[i].a++;
  }
  sort(rings.begin(), rings.end());
  reverse(rings.begin(), rings.end());
  set<Long> trans;
  for (int i = 0; i < n; i++) {
    trans.insert(rings[i].a);
    trans.insert(rings[i].b);
  }
  map<Long, Long> go;
  Long sz = 0;
  for (auto it : trans) go[it] = sz++;
  for (int i = 0; i < n; i++) {
    rings[i].a = go[rings[i].a];
    rings[i].b = go[rings[i].b];
  }
  // Comprimo los anillos para poder realizar el dp
  vector<Ring> rem;
  for (int i = 0; i < n; i++) {
    Long sum = 0;
    int j = i;
    while (j < n && rings[j].b == rings[i].b) sum += rings[j++].h;
    rem.push_back({rings[j - 1].a, rings[j - 1].b, sum});
    i = j - 1;
  }
  // Resuelvo el problema con dp
  st.Build(1, 0, sz - 1);
  Long ans = 0;
  for (int i = 0; i < rem.size(); i++) {
    Long current = rem[i].h + st.Query(0, rem[i].b, 1, 0, sz - 1);
    ans = max(ans, current);
    st.Update(rem[i].a, current, 1, 0, sz - 1);
  }
  cout << ans << '\n';
  return 0;
}

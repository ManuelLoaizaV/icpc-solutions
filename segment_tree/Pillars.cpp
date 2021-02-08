//https://codeforces.com/problemset/problem/474/E
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef pair<int, int> Pair;

const int N = 3e5;
struct SegmentTree {
  Pair tree[4 * N];
  int n;
  SegmentTree(int new_n) { n = new_n; }
  Pair Merge(const Pair& x, const Pair& y) {
    if (x.second > y.second) return x;
    return y;
  }
  void Build(int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = {-1, 0};
    } else {
      int tm = (tl + tr) / 2;
      Build(2 * id, tl, tm);
      Build(2 * id + 1, tm + 1, tr);
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
  void Update(int pos, Pair val, int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = val;
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
  Pair Query(int l, int r, int id, int tl, int tr) {
    if (l <= tl && tr <= r) return tree[id];
    int tm = (tl + tr) / 2;
    if (r <= tm) return Query(l, r, 2 * id, tl, tm);
    if (tm < l) return Query(l, r, 2 * id + 1, tm + 1, tr);
    return Merge(Query(l, r, 2 * id, tl, tm), Query(l, r, 2 * id + 1, tm + 1, tr));
  }
  void Update(int pos, Pair val) { Update(pos, val, 1, 0, n - 1); }
  Pair Query(int l, int r) { return Query(l, r, 1, 0, n - 1); }
};


int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n;
  Long d;
  cin >> n >> d;
  vector<Long> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  // Agrego a mis lugares y a todos los posibles
  set<Long> elements;
  for (int i = 0; i < n; i++) {
    elements.insert(a[i]);
    elements.insert(a[i] - d);
    elements.insert(a[i] + d);
  }
  int cnt = 0;
  map<Long, int> h;
  for (auto element : elements) h[element] = cnt++;
  // Construyo el segment tree
  SegmentTree st(cnt);
  st.Build(1, 0, cnt - 1);
  // dp[i] = {padre de i, longitud maxima de subsecuencia que terminar en a[i]}
  vector<Pair> dp(n);
  for (int i = 0; i < n; i++) {
    Long left = a[i] - d;
    Long right = a[i] + d;
    Pair maximum = st.Merge(st.Query(0, h[left]), st.Query(h[right], cnt -1));
    dp[i] = {maximum.first, 1 + maximum.second};
    st.Update(h[a[i]], {i, dp[i].second});
  }
  // Reconstruyo el dp
  Pair maximum = {-1, -1};
  int who = -1;
  for (int i = 0; i < n; i++) {
    if (dp[i].second > maximum.second) {
      maximum = dp[i];
      who = i;
    }
  }
  cout << maximum.second << '\n';
  vector<int> positions;
  while (who != -1) {
    positions.push_back(who + 1);
    who = dp[who].first;
  }
  reverse(positions.begin(), positions.end());
  for (int position : positions) cout << position << " ";
  cout << '\n';
  return 0;
}

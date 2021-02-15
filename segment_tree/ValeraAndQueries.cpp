//https://codeforces.com/problemset/problem/369/E
#include <bits/stdc++.h>
using namespace std;

const int N = 3e5;
const int INF = 2e6;

struct SegmentTree {
  int n;
  vector<int> tree[4 * N];
  vector<int> Merge(const vector<int>& left, const vector<int>& right) {
    int l = 0;
    int r = 0;
    vector<int> ans;
    int size = left.size() + right.size();
    for (int i = 0; i < size; i++) {
      if (l == left.size()) {
        ans.push_back(right[r++]);
      } else if (r == right.size()) {
        ans.push_back(left[l++]);
      } else if (left[l] < right[r]) {
        ans.push_back(left[l++]);
      } else {
        ans.push_back(right[r++]);
      }
    }
    return ans;
  }
  void Build(const vector<pair<int, int>>& a, int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = {a[tl].second};
    } else {
      int tm = (tl + tr) / 2;
      Build(a, 2 * id, tl, tm);
      Build(a, 2 * id + 1, tm + 1, tr);
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
  int Query(int l, int r, int x, int id, int tl, int tr) {
    if (l <= tl && tr <= r) {
      int cnt = upper_bound(tree[id].begin(), tree[id].end(), x) - tree[id].begin();
      return cnt;
    }
    int tm = (tl + tr) / 2;
    if (r <= tm) return Query(l, r, x, 2 * id, tl, tm);
    if (tm < l) return Query(l, r, x, 2 * id + 1, tm + 1, tr);
    return Query(l, r, x, 2 * id, tl, tm) + Query(l, r, x, 2 * id + 1, tm + 1, tr);
  }
  int Query(int l, int r, int x) { return Query(l, r, x, 1, 0, n - 1); }
} st;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<pair<int, int>> pairs(n);
  for (int i = 0; i < n; i++) cin >> pairs[i].first >> pairs[i].second;
  sort(pairs.begin(), pairs.end());
  st.Build(pairs, 1, 0, n - 1);
  st.n = n;
  while (m--) {
    int ans = 0;
    int cnt;
    cin >> cnt;
    vector<int> pos;
    pos.push_back(-1);
    for (int i = 0; i < cnt; i++) {
      int p;
      cin >> p;
      pos.push_back(p);
    }
    pos.push_back(INF);
    for (int i = 0; i < pos.size() - 1; i++) {
      if (pos[i + 1] - pos[i] > 1) {
        pair<int, int> inf = {pos[i] + 1, -INF};
        int l = lower_bound(pairs.begin(), pairs.end(), inf) - pairs.begin();
        if (l == n) continue;
        pair<int, int> sup = {pos[i + 1], -INF};
        int r = lower_bound(pairs.begin(), pairs.end(), sup) - pairs.begin();
        r--;
        if (l <= r) ans += st.Query(l, r, pos[i + 1] - 1);
      }
    }
    cout << n - ans << '\n';
  }
  return 0;
}

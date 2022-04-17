// https://codeforces.com/contest/1665/problem/E
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

const int N = 1e2;
const int B = 31;
const int INF = (1 << 30) - 1;

struct MergeSortTree {
  vector<vector<int>> tree;
  int n;
  MergeSortTree(int n) : n(n) {
    tree = vector<vector<int>>(4 * n);
  }
  vector<int> Merge(const vector<int>& left, const vector<int>& right) {
    int l = 0;
    int r = 0;
    vector<int> ans;
    int size = left.size() + right.size();
    for (int i = 0; i < B; i++) {
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
  // O(n lgn)
  void Build(int id, int tl, int tr, const vector<int>& v) {
    if (tl == tr) {
      tree[id] = vector<int>(B, INF);
      tree[id][0] = v[tl];
    } else {
      int tm = (tl + tr) / 2;
      Build(2 * id, tl, tm, v);
      Build(2 * id + 1, tm + 1, tr, v);
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
  // O(lg^2(n))
  vector<int> Query(int l, int r, int id, int tl, int tr) {
    if (l <= tl && tr <= r) return tree[id];
    int tm = (tl + tr) / 2;
    if (r <= tm) return Query(l, r, 2 * id, tl, tm);
    if (tm < l) return Query(l, r, 2 * id + 1, tm + 1, tr);
    return Merge(Query(l, r, 2 * id, tl, tm), Query(l, r, 2 * id + 1, tm + 1, tr));
  }
  void Build(const vector<int>& v) { Build(1, 0, n - 1, v); }
  vector<int> Query(int l, int r) { return Query(l, r, 1, 0, n - 1); }
};

void Solve(void) {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  MergeSortTree mt(n);
  mt.Build(a);
  int q;
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    l--;
    r--;
    vector<int> candidates = mt.Query(l, r);
    int mn = INF;
    for (int i = 0; i < B - 1; i++) {
      for (int j = i + 1; j < B; j++) {
        mn = min(mn, candidates[i] | candidates[j]);
      }
    }
    cout << mn << '\n';
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
//https://codeforces.com/problemset/problem/785/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> OST;
typedef long long Long;

const int N = 2e5;

struct SegmentTree {
  OST tree[2 * N];
  void Build(const vector<int>& a, int id, int tl, int tr) {
    if (tl == tr) {
      tree[id].insert(a[tl]);
    } else {
      int tm = (tl + tr) / 2;
      int left = id + 1;
      int right = id + 2 * (tm - tl + 1);
      Build(a, left, tl, tm);
      Build(a, right, tm + 1, tr);
      tree[id] = tree[left];
      for (auto i : tree[right]) tree[id].insert(i);
    }
  }
  void Add(int pos, int val, int id, int tl, int tr) {
    tree[id].insert(val);
    if (tl == tr) return;
    int tm = (tl + tr) / 2;
    int left = id + 1;
    int right = id + 2 * (tm - tl + 1);
    if (pos <= tm) {
      Add(pos, val, left, tl, tm);
    } else {
      Add(pos, val, right, tm + 1, tr);
    }
  }
  void Delete(int pos, int val, int id, int tl, int tr) {
    tree[id].erase(val);
    if (tl == tr) return;
    int tm = (tl + tr) / 2;
    int left = id + 1;
    int right= id + 2 * (tm - tl + 1);
    if (pos <= tm) {
      Delete(pos, val, left, tl, tm);
    } else {
      Delete(pos, val, right, tm + 1, tr);
    }
  }
  int Greater(int l, int r, int k, int id, int tl, int tr) {
    if (l <= tl && tr <= r) {
      return (int) tree[id].size() - tree[id].order_of_key(k);
    } else {
      int tm = (tl + tr) / 2;
      int left = id + 1;
      int right = id + 2 * (tm - tl + 1);
      if (r <= tm) return Greater(l, r, k, left, tl, tm);
      if (tm < l) return Greater(l, r, k, right, tm + 1, tr);
      return Greater(l, r, k, left, tl, tm) + Greater(l, r, k, right, tm + 1, tr);
    }
  }
} st;

int Count(int i, const vector<int>& p) {
  int cnt = 0;
  if (i > 0) cnt = st.Greater(0, i - 1, p[i], 1, 0, (int) p.size() - 1);
  cnt += ((p[i] - 1) - (i - cnt));
  return cnt;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, q;
  cin >> n >> q;
  vector<int> p(n);
  for (int i = 0; i < n; i++) p[i] = i + 1;
  st.Build(p, 1, 0, n - 1);
  Long ans = 0;
  while (q--) {
    int l, r;
    cin >> l >> r;
    l--; r--;
    if (l > r) swap(l, r);
    if (l != r) {
      ans -= (Long) Count(l, p);
      ans -= (Long) Count(r, p);
      if (p[l] > p[r]) ans++;
      st.Delete(l, p[l], 1, 0, n - 1);
      st.Delete(r, p[r], 1, 0, n - 1);
      swap(p[l], p[r]);
      st.Add(l, p[l], 1, 0, n - 1);
      st.Add(r, p[r], 1, 0, n - 1);
      ans += (Long) Count(l, p);
      ans += (Long) Count(r, p);
      if (p[l] > p[r]) ans--;
    }
    cout << ans << '\n';
  }
  return 0;
}
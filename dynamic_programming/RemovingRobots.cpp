//https://atcoder.jp/contests/abc158/tasks/abc158_f
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

const Long MOD = 998244353;
const int N = 2e5;

int n;
vector<Pair> points;

int GetLast(int i) {
  int l = i;
  int r = n - 1;
  int mx = points[i].first + points[i].second - 1;
  if (points[r].first <= mx) return r;
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (points[m].first <= mx) {
      l = m;
    } else {
      r = m;
    }
  }
  return l;
}

Long Add(Long a, Long b) {
  return (a + b) % MOD;
}

bool is_done[N];
Long dp[N];

Long DP(int i) {
  if (i == n) return 1;
  if (is_done[i]) return dp[i];
  dp[i] = Add(DP(i + 1), DP(points[i].second + 1));
  is_done[i] = true;
  return dp[i];
}

struct SegmentTree {
  int tree[4 * N];
  void Build(int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = points[tl].second;
    } else {
      int tm = (tl + tr) / 2;
      Build(2 * id, tl, tm);
      Build(2 * id + 1, tm + 1, tr);
      tree[id] = max(tree[2 * id], tree[2 * id + 1]);
    }
  }

  void Update(int pos, int val, int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = val;
    } else{
      int tm = (tl + tr) / 2;
      if (pos <= tm) {
        Update(pos, val, 2 * id, tl, tm);
      } else {
        Update(pos, val, 2 * id + 1, tm + 1, tr);
      }
      tree[id] = max(tree[2 * id], tree[2 * id + 1]);
    }
  }

  int Query(int l, int r, int id, int tl, int tr) {
    if (l <= tl && tr <= r) return tree[id];
    int tm = (tl + tr) / 2;
    if (r <= tm) return Query(l, r, 2 * id, tl, tm);
    if (tm < l) return Query(l, r, 2 * id + 1, tm + 1, tr);
    return max(Query(l, r, 2 * id, tl, tm), Query(l, r, 2 * id + 1, tm + 1, tr));
  }
} st;

int main(void) {
  FAST_IO;
  cin >> n;
  points.resize(n);
  for (int i = 0; i < n; i++) cin >> points[i].first >> points[i].second;
  sort(points.begin(), points.end());
  for (int i = 0; i < n; i++) points[i].second = GetLast(i);
  st.Build(1, 0, n - 1);
  for (int i = n - 1; i >= 0; i--) {
    points[i].second = st.Query(i, points[i].second, 1, 0, n - 1);
    st.Update(i, points[i].second, 1, 0, n - 1);
  }
  cout << DP(0) << '\n';
  return 0;
}

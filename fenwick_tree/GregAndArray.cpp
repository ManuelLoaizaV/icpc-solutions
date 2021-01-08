//https://codeforces.com/problemset/problem/296/C
#include <iostream>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;

const int N = 1e5;

struct Query {
  int l, r;
  Long delta;
};

struct FenwickTree {
  Long tree[N + 1];

  void Update(int i, Long delta) {
    while (i <= N) {
      tree[i] += delta;
      i += (i & -i);
    }
  }

  Long Query(int i) {
    Long ans = 0;
    while (i > 0) {
      ans += tree[i];
      i -= (i & -i);
    }
    return ans;
  }
} ft, ftq;

int main(void) {
  FAST_IO;
  Long n, m, k;
  cin >> n >> m >> k;
  vector<Long> a(n + 1);
  for (int i = 1; i <= n; i++) cin >> a[i];
  vector<Query> q(m + 1);
  for (int i = 1; i <= m; i++) {
    cin >> q[i].l >> q[i].r >> q[i].delta;
  }
  for (int i = 0; i < k; i++) {
    int x, y;
    cin >> x >> y;
    ftq.Update(x, 1);
    ftq.Update(y + 1, -1);
  }
  for (int i = 1; i <= m; i++) {
    Long delta = q[i].delta * ftq.Query(i);
    if (delta == 0) continue;
    ft.Update(q[i].l, delta);
    ft.Update(q[i].r + 1, -delta);
  }
  for (int i = 1; i <= n; i++) {
    if (i > 1) cout << " ";
    Long cur = a[i] + ft.Query(i);
    cout << cur;
  }
  cout << '\n';
  return 0;
}

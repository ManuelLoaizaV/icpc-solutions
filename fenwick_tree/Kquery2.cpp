//https://www.spoj.com/problems/KQUERY2/en/
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 3e4;
const int A = 1e4;

struct FenwickTree {
  int tree[N + 1][A + 1];
  void Clear(int n, int m) {
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= m; j++) {
        tree[i][j] = 0;
      }
    }
  }
  void Update(int i, int y, int delta) {
    while (i <= N) {
      int j = y;
      while (j <= A) {
        tree[i][j] += delta;
        j += (j & -j);
      }
      i += (i & -i);
    }
  }
  int Query(int i, int y) {
    int ans = 0;
    while (i > 0) {
      int j = y;
      while (j > 0) {
        ans += tree[i][j];
        j -= (j & -j);
      }
      i -= (i & -i);
    }
    return ans;
  }
} ft;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  scanf("%d", &n);
  vector<int> a(n);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  for (int i = 0; i < n; i++) ft.Update(i + 1, a[i], 1);
  int q;
  scanf("%d", &q);
  while (q--) {
    int t;
    scanf("%d", &t);
    if (t == 0) {
      int i, v;
      scanf("%d %d", &i, &v);
      ft.Update(i, a[i - 1], -1);
      ft.Update(i, v, 1);
      a[i - 1] = v;
    } else {
      int i, j, k;
      scanf("%d %d %d", &i, &j, &k);
      int invalid = ft.Query(j, k) - ft.Query(i - 1, k);
      int ans = j - i + 1 - invalid;
      printf("%d\n", ans);
    }
  }
  return 0;
}

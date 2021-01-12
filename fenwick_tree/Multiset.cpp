//https://codeforces.com/problemset/problem/1354/D
#include <iostream>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

const int N = 1e6;

struct FenwickTree {
  int tree[N + 1];

  void Update(int i, int delta) {
    while (i <= N) {
      tree[i] += delta;
      i += (i & -i);
    }
  }

  int Query(int i) {
    int ans = 0;
    while (i > 0) {
      ans += tree[i];
      i -= (i & -i);
    }
    return ans;
  }
} ft;

int Search(int l, int r, int k) {
  if (ft.Query(l) >= k) return l;
  if (ft.Query(r) < k) return -1;
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (ft.Query(m) >= k) {
      r = m;
    } else {
      l = m;
    }
  }
  return r;
}

int main(void) {
  FAST_IO;
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    ft.Update(x, 1);
  }
  while (q--) {
    int k;
    cin >> k;
    if (k > 0) {
      ft.Update(k, 1);
    } else {
      int who = Search(1, n, -k);
      ft.Update(who, -1);
    }
  }
  for (int i = 1; i <= n; i++) {
    if (ft.Query(i) > 0) {
      cout << i << '\n';
      return 0;
    }
  }
  cout << 0 << '\n';
  return 0;
}

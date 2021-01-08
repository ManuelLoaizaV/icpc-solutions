//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3977
#include <iostream>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

const int N = 1e5;

struct FenwickTree {
  int tree[N + 1];

  void Build(int n) {
    for (int i = 0; i <= n; i++) tree[i] = 0;
  }

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
} neg, zero;

int main(void) {
  FAST_IO;
  int n, q;
  while (cin >> n >> q) {
    neg.Build(n);
    zero.Build(n);
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      if (a[i] < 0) {
        neg.Update(i, 1);
      } else if (a[i] == 0) {
        zero.Update(i, 1);
      }
    }
    string ans = "";
    while (q--) {
      char c;
      int x, y;
      cin >> c >> x >> y;
      int cnt;
      if (c == 'C') {
        if (a[x] == 0) zero.Update(x, -1);
        if (a[x] < 0) neg.Update(x, -1);
        a[x] = y;
        if (a[x] == 0) zero.Update(x, 1);
        if (a[x] < 0) neg.Update(x, 1);
      } else {
        cnt = zero.Query(y) - zero.Query(x - 1);
        if (cnt > 0) {
          ans += '0';
        } else {
          cnt = neg.Query(y) - neg.Query(x - 1);
          if (cnt & 1) {
            ans += '-';
          } else {
            ans += '+';
          }
        }
      }
    }
    cout << ans << '\n';
  }
  return 0;
}

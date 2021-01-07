//https://codeforces.com/problemset/problem/276/C
#include <algorithm>
#include <iostream>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

const int N = 2e5;

typedef long long Long;

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

int main(void) {
  FAST_IO;
  Long n, q;
  cin >> n >> q;
  vector<Long> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a.begin(), a.end());
  while (q--) {
    int l, r;
    cin >> l >> r;
    ft.Update(l, 1);
    ft.Update(r + 1, -1);
  }
  vector<int> aux;
  for (int i = 1; i <= n; i++) aux.push_back(ft.Query(i));
  sort(aux.begin(), aux.end());
  Long ans = 0LL;
  for (int i = 0; i < n; i++) ans += a[i] * aux[i];
  cout << ans << '\n';
  return 0;
}

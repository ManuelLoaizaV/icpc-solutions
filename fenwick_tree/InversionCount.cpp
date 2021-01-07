//https://www.spoj.com/problems/INVCNT/en/
#include <algorithm>
#include <iostream>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;

const int N = 2e5;

struct FenwickTree {
  Long tree[N + 1];

  void Build(int n) {
    for (int i = 0; i <= n; i++) tree[i] = 0;
  }

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
} ft;

void CoordinateCompression(vector<int>& a) {
  int n = a.size();
  vector<pair<int, int>> pairs(n);
  for (int i = 0; i < n; i++) pairs[i] = {a[i], i};
  sort(pairs.begin(), pairs.end());
  int nxt = 1;
  for (int i = 0; i < n; i++) {
    if (i > 0 && pairs[i - 1].first != pairs[i].first) nxt++;
    a[pairs[i].second] = nxt;
  }
}

void Solve(void) {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  CoordinateCompression(a);

  ft.Build(n);
  Long ans = 0LL;
  for (int i = n - 1; i >= 0; i--) {
    ans += ft.Query(a[i]);
    ft.Update(a[i] + 1, 1LL);
  }
  cout << ans << '\n';
}

int main(void) {
  FAST_IO;
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}

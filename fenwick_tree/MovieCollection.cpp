//https://open.kattis.com/problems/moviecollection
#include <iostream>
using namespace std;

const int N = 1e5;
const int M = 2e5;

int positions[N + 1];
int ans[N];

struct FenwickTree {
  int tree[M + 1];

  void Build(int n) {
    for (int i = 0; i <= n; i++) tree[i] = 0;
  }

  void Update(int i, int delta) {
    while (i <= M) {
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

void Solve(void) {
  int m, r;
  cin >> m >> r;
  ft.Build(m + r);
  for (int i = 1; i <= m; i++) {
    positions[i] = m - i + 1;
  }
  for (int i = 0; i < r; i++) {
    int movie;
    cin >> movie;
    int current = positions[movie] + ft.Query(positions[movie]);
    ans[i] = m - current;
    ft.Update(positions[movie] + 1, -1);
    positions[movie] = m + i + 1;
  }
  for (int i = 0; i < r; i++) {
    if (i > 0) cout << " ";
    cout << ans[i];
  }
  cout << '\n';
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}

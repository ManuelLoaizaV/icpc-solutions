//https://www.spoj.com/problems/MSE06H/en/
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;
typedef pair<int, int> Pair;

const int N = 1e3;

struct FenwickTree {
  Long tree[N + 1];

  void Build(int n) {
    for (int i = 0; i <= n; i++) tree[i] = 0LL;
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

void Solve(int t) {
  Long n, m, k;
  cin >> n >> m >> k;
  vector<Pair> highways(k);
  for (int i = 0; i < k; i++) {
    cin >> highways[i].first >> highways[i].second;
  }
  sort(highways.begin(), highways.end());
  Long ans = 0;
  ft.Build(m);
  for (int i = k - 1; i >= 0; i--) {
    ans += ft.Query(highways[i].second);
    ft.Update(highways[i].second + 1, 1LL);
  }
  cout << "Test case " << t << ": " << ans << '\n';
}

int main(void) {
  FAST_IO;
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) Solve(i);
  return 0;
}

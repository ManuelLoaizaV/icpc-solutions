//https://www.spoj.com/problems/INCSEQ/en/
#include <iostream>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;

const int N = 1e5 + 5;
const Long MOD = 5e6;

Long Sum(Long a, Long b) {
  return (a + b) % MOD;
}

struct FenwickTree {
  Long tree[N + 1];
  void Build(void) {
    for (int i = 0; i <= N; i++) tree[i] = 0LL;
  }

  void Update(int i, Long delta) {
    while (i <= N) {
      tree[i] = Sum(tree[i], delta);
      i += (i & -i);
    }
  }

  Long Query(int i) {
    Long ans = 0;
    while (i > 0) {
      ans = Sum(ans, tree[i]);
      i -= (i & -i);
    }
    return ans;
  }
} ft;

int main(void) {
  FAST_IO;
  int n, k;
  cin >> n >> k;
  vector<Long> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i]++;
  }
  Long ans = 0LL;
  vector<vector<Long>> dp(n, vector<Long> (2, 0));
  for (int i = 0; i < n; i++) dp[i][0] = 1;
  for (int len = 0; len < k - 1; len++) {
    ft.Build();
    for (int i = 0; i < n; i++) {
      dp[i][1] = Sum(dp[i][1], ft.Query(a[i]));
      ft.Update(a[i] + 1, dp[i][0]);
    }
    for (int i = 0; i < n; i++) {
      dp[i][0] = dp[i][1];
      dp[i][1] = 0LL;
    }
  }
  for (int i = 0; i < n; i++) ans = Sum(ans, dp[i][0]);
  cout << ans << '\n';
  return 0;
}

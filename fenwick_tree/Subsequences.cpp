//https://codeforces.com/problemset/problem/597/C
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 1e5;

struct FenwickTree {
  Long tree[N + 1];
  void Clear(int n) {
    for (int i = 0; i <= n; i++) tree[i] = 0;
  }
  void Update(int i, Long delta) {
    while (i <= N) {
      tree[i] += delta;
      i += (i & -i);
    }
  }
  Long Query(int i) {
    Long answer = 0;
    while (i > 0) {
      answer += tree[i];
      i -= (i & -i);
    }
    return answer;
  }
} ft;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n, k;
  cin >> n >> k;
  k++;
  vector<Long> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  vector<Long> dp(n, 1LL), current(n);
  for (int len = 2; len <= k; len++) {
    ft.Clear(n);
    for (int i = 0; i < n; i++) {
      current[i] = ft.Query(a[i]);
      ft.Update(a[i] + 1, dp[i]);
    }
    dp = current;
  }
  Long cnt = 0;
  for (Long element : dp) cnt += element;
  cout << cnt << '\n';
  return 0;
}

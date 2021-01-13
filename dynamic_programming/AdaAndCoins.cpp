//https://www.spoj.com/problems/ADACOINS/
#include <bitset>
#include <iostream>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;
const int N = 1e5;

bitset<N + 1> dp;

int main(void) {
  FAST_IO;
  int n, q;
  cin >> n >> q;
  dp[0] = 1;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    dp = dp | (dp << a);
  }

  vector<int> cnt(N + 1);
  cnt[0] = 1;
  for (int i = 1; i <= N; i++) cnt[i] = cnt[i - 1] + dp[i];
  while (q--) {
    int l, r;
    cin >> l >> r;
    int ans = cnt[r] - cnt[l - 1];
    cout << ans << '\n';
  }
  return 0;
}

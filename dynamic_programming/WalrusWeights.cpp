//https://open.kattis.com/problems/walrusweights
#include <bitset>
#include <cstdlib>
#include <iostream>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

const int N = 2000;
bitset<N + 1> dp;

int main(void) {
  FAST_IO;
  int n;
  cin >> n;
  dp[0] = 1;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    dp = dp | (dp << x);
  }
  int ans = -10000;
  for (int i = 1; i <= N; i++) {
    if (dp[i]) {
      int mn = abs(1000 - ans);
      int cur = abs(1000 - i);
      if (cur < mn || cur == mn) ans = i;
    }
  }
  cout << ans << '\n';
  return 0;
}

//https://atcoder.jp/contests/abc159/tasks/abc159_f
#include <iostream>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;

const Long MOD = 998244353;
const int N = 3e3 + 5;

Long Add(Long a, Long b) {
  return (a + b) % MOD;
}

Long Mul(Long a, Long b) {
  return (a * b) % MOD;
}

Long A[N], dp[N][N];
bool is_done[N][N];

Long DP(Long pos, Long rem) {
  if (rem == 0) return pos + 2;
  if (rem < 0) return 0LL;
  if (pos < 0) return 0LL;
  if (is_done[pos][rem]) return dp[pos][rem];
  dp[pos][rem] = Add(DP(pos - 1, rem), DP(pos - 1, rem - A[pos]));
  is_done[pos][rem] = true;
  return dp[pos][rem];
}

int main(void) {
  FAST_IO;
  Long n, s;
  cin >> n >> s;
  for (int i = 0; i < n; i++) cin >> A[i];
  Long ans = 0;
  for (int i = n - 1; i >= 0; i--) {
    ans = Add(ans, Mul(DP(i - 1, s - A[i]), n - i));
  }
  cout << ans << '\n';
  return 0;
}

#include <iostream>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;

const int N = 1005;
const int K = 6;

Long nck[N][K];
bool done[N][K];

Long nCk(Long n, Long k) {
  if (n < k) return 0LL;
  if (n == k) return 1LL;
  if (k == 0) return 1LL;
  if (done[n][k]) return nck[n][k];
  nck[n][k] = nCk(n - 1, k) + nCk(n - 1, k - 1);
  done[n][k] = true;
  return nck[n][k];
}

Long dp[K];
bool is_done[K];

Long DP(Long n) {
  if (n == 0) return 1LL;
  if (n == 1) return 0LL;
  if (is_done[n]) return dp[n];
  dp[n] = (n - 1) * (DP(n - 1) + DP(n - 2));
  is_done[n] = true;
  return dp[n];
}

int main(void) {
  FAST_IO;
  Long n, k;
  cin >> n >> k;
  Long ans = 0LL;
  for (Long i = 0LL; i <= k; i++) {
    ans += (nCk(n, i) * DP(i));
  }
  cout << ans << '\n';
  return 0;
}

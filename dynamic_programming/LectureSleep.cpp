#include <iostream>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

const int N = 1e5;

int a[N], n, k;
bool t[N];

int dp[N][2];
int sum[N];
bool is_done[N][2];

int DP(int pos, bool has_secret) {
  if (pos == n) return 0;
  if (is_done[pos][has_secret]) return dp[pos][has_secret];
  dp[pos][has_secret] = t[pos] * a[pos] + DP(pos + 1, has_secret);
  if (has_secret) {
    int next_pos = min(pos + k, n);
    int add = sum[next_pos - 1] - ((pos == 0) ? 0 : sum[pos - 1]);
    dp[pos][has_secret] = max(dp[pos][has_secret], add + DP(next_pos, false));
  }
  is_done[pos][has_secret] = true;
  return dp[pos][has_secret];
}

int main(void) {
  FAST_IO;
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> t[i];
  sum[0] = a[0];
  for (int i = 1; i < n; i++) sum[i] = sum[i - 1] + a[i];
  cout << DP(0, true) << '\n';
  return 0;
}
